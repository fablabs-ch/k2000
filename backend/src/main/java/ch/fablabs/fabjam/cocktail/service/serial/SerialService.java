package ch.fablabs.fabjam.cocktail.service.serial;

import ch.fablabs.fabjam.cocktail.data.serial.ConnexionStatus;
import ch.fablabs.fabjam.cocktail.data.serial.EndOfCommand;
import ch.fablabs.fabjam.cocktail.data.serial.SerialStatus;
import lombok.Builder;
import lombok.Data;
import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.web.servlet.mvc.method.annotation.SseEmitter;
import rx.subjects.BehaviorSubject;

import java.time.Duration;
import java.time.Instant;
import java.util.*;

@Slf4j
@Service
public class SerialService {

	public static Duration CONNEXION_TIMEOUT = Duration.ofMillis(2000);

	private BehaviorSubject<SerialStatus> serialStatus;
	private BehaviorSubject<EndOfCommand> endOfCommand;
	private BehaviorSubject<ConnexionStatus> connexionStatus;
	private Instant lastCommand;

	private final List<SseEmitter> emitters = Collections.synchronizedList(new LinkedList<>());

	public SerialService() {
		this.serialStatus = BehaviorSubject.create((SerialStatus) null);
		this.endOfCommand = BehaviorSubject.create((EndOfCommand) null);
		this.connexionStatus = BehaviorSubject.create(ConnexionStatus.builder().connected(false).build());
	}

	public BehaviorSubject<SerialStatus> getSerialStatus() {
		return serialStatus;
	}

	public BehaviorSubject<EndOfCommand> getEndOfCommand() {
		return endOfCommand;
	}

	synchronized public void statusReceived(SerialStatus status) {
		this.serialStatus.onNext(status);
		this.lastCommand = Instant.now();

		broadCastToSSEListener();
	}

	public void checkConnexionStatus() {
		ConnexionStatus.ConnexionStatusBuilder builder = ConnexionStatus.builder();
		if (lastCommand == null) {
			LOG.trace("Serial was never connected");
			builder.connected(false);
		} else if (Duration.between(Instant.now(), lastCommand).abs().compareTo(CONNEXION_TIMEOUT) > 0) {
			LOG.trace("Serial timed out");
			builder.connected(false)
				.lastStatus(lastCommand.toEpochMilli());
		} else {
			LOG.trace("Serial is connected");
			builder.connected(true)
				.lastStatus(lastCommand.toEpochMilli());
		}
		connexionStatus.onNext(builder.build());
		broadCastToSSEListener();
	}

	public void endOfCommandReceived(String command) {
		this.endOfCommand.onNext(new EndOfCommand(command));
	}

	public SseEmitter getStatusSSE() {
		SseEmitter emmitter = new SseEmitter();
		emitters.add(emmitter);
		return emmitter;
	}

	protected void broadCastToSSEListener() {
		SseStatus sseStatus = SseStatus.builder()
			.connexion(connexionStatus.getValue())
			.status(serialStatus.getValue())
			.build();

		Iterator<SseEmitter> iterator = emitters.iterator();
		while (iterator.hasNext()) {
			SseEmitter emitter = iterator.next();
			try {
				emitter.send(sseStatus);
			} catch (Exception e) {
				LOG.warn("Unable to emit SSE {}", e.getMessage());
				iterator.remove();
			}
		}
	}

	@Builder
	@Data
	public static class SseStatus {
		ConnexionStatus connexion;
		SerialStatus status;
	}
}
