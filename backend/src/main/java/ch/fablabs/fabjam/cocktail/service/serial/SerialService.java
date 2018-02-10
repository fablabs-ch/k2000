package ch.fablabs.fabjam.cocktail.service.serial;

import ch.fablabs.fabjam.cocktail.data.serial.EndOfCommand;
import ch.fablabs.fabjam.cocktail.data.serial.SerialStatus;
import ch.fablabs.fabjam.cocktail.data.type.JmsTopic;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jms.annotation.JmsListener;
import org.springframework.stereotype.Service;
import org.springframework.web.servlet.mvc.method.annotation.SseEmitter;
import rx.subjects.BehaviorSubject;

import java.io.IOException;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;

@Slf4j
@Service
public class SerialService {

	private BehaviorSubject<Integer> weightSubject;
	private BehaviorSubject<Integer> distanceFromHomeInMm;
	private BehaviorSubject<SerialStatus> serialStatus;
	private BehaviorSubject<EndOfCommand> endOfCommand;

	private final List<SseEmitter> emitters = Collections.synchronizedList(new LinkedList<>());

	public SerialService() {
		this.weightSubject = BehaviorSubject.create(-1);
		this.distanceFromHomeInMm = BehaviorSubject.create(-1);
		this.serialStatus = BehaviorSubject.create((SerialStatus) null);
		this.serialStatus = BehaviorSubject.create((SerialStatus) null);
		this.endOfCommand = BehaviorSubject.create((EndOfCommand) null);
	}

	public BehaviorSubject<Integer> getWeightSubject() {
		return weightSubject;
	}

	public BehaviorSubject<Integer> getDistanceFromHomeInMm() {
		return distanceFromHomeInMm;
	}

	public BehaviorSubject<SerialStatus> getSerialStatus() {
		return serialStatus;
	}

	public BehaviorSubject<EndOfCommand> getEndOfCommand() {
		return endOfCommand;
	}

	@JmsListener(destination = JmsTopic.SERIAL_STATUS)
	private void serialStatus(SerialStatus status) {
		this.serialStatus.onNext(status);
		this.weightSubject.onNext(status.getPayloadWeightGr());
		this.distanceFromHomeInMm.onNext(status.getCarrierDistMm());

		// TOTO lock arround this
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

	@JmsListener(destination = JmsTopic.SERIAL_END_OF_COMMAND)
	private void serialEndOfCommand(String command) {
		this.endOfCommand.onNext(new EndOfCommand(command));
	}

	public SseEmitter getStatusSSE() {
		SseEmitter emmitter = new SseEmitter();
		emitters.add(emmitter);
		return emmitter;
	}
}
