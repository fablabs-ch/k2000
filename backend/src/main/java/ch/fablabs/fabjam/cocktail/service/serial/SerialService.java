package ch.fablabs.fabjam.cocktail.service.serial;

import ch.fablabs.fabjam.cocktail.data.serial.EndOfCommand;
import ch.fablabs.fabjam.cocktail.data.serial.SerialStatus;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.web.servlet.mvc.method.annotation.SseEmitter;
import rx.subjects.BehaviorSubject;

import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

@Slf4j
@Service
public class SerialService {

	private BehaviorSubject<SerialStatus> serialStatus;
	private BehaviorSubject<EndOfCommand> endOfCommand;

	private final List<SseEmitter> emitters = Collections.synchronizedList(new LinkedList<>());

	public SerialService() {
		this.serialStatus = BehaviorSubject.create((SerialStatus) null);
		this.endOfCommand = BehaviorSubject.create((EndOfCommand) null);
	}


	public BehaviorSubject<SerialStatus> getSerialStatus() {
		return serialStatus;
	}

	public BehaviorSubject<EndOfCommand> getEndOfCommand() {
		return endOfCommand;
	}

	synchronized public void statusReceived(SerialStatus status) {
		this.serialStatus.onNext(status);

		// TODO lock arround this
		Iterator<SseEmitter> iterator = emitters.iterator();
		while (iterator.hasNext()) {
			SseEmitter emitter = iterator.next();
			try {
				emitter.send(status);
			} catch (Exception e) {
				LOG.warn("Unable to emit SSE {}", e.getMessage());
				iterator.remove();
			}
		}

	}

	public void endOfCommandReceived(String command) {
		this.endOfCommand.onNext(new EndOfCommand(command));
	}

	public SseEmitter getStatusSSE() {
		SseEmitter emmitter = new SseEmitter();
		emitters.add(emmitter);
		return emmitter;
	}
}
