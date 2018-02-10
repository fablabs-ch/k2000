package ch.fablabs.fabjam.cocktail.service.recipe.actions;

import ch.fablabs.fabjam.cocktail.service.CommandService;
import ch.fablabs.fabjam.cocktail.service.serial.SerialService;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.Setter;
import rx.subjects.BehaviorSubject;

import java.time.Instant;
import java.util.Optional;

abstract public class AbstractAction {

	@Setter
	protected SerialService serialService;

	@Setter
	protected CommandService commandService;

	@Setter(AccessLevel.PROTECTED)
	@Getter
	private boolean finished = false;

	private Instant actionStarted;

	public final void start() {
		actionStarted = Instant.now();
		initialRun();
	}

	protected void initialRun() {

	}

	public void cancelling(){

	}

	abstract public void run();

	public long getTimeoutMs() {
		return 10000;
	}

	protected boolean endOfCommandReceived(String command) {
		return Optional.ofNullable(serialService.getEndOfCommand())
			.map(BehaviorSubject::getValue)
			.filter(end -> end.getCommand().equalsIgnoreCase(command))
			.filter(end -> end.getTime().isAfter(actionStarted))
			.isPresent();
	}

}
