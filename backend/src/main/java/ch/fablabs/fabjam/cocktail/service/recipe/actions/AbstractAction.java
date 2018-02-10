package ch.fablabs.fabjam.cocktail.service.recipe.actions;

import ch.fablabs.fabjam.cocktail.service.serial.SerialService;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.Setter;

abstract public class AbstractAction {

	@Setter
	protected SerialService serialService;

	@Setter(AccessLevel.PROTECTED)
	@Getter
	private boolean finished = false;

	public void initialRun() {

	}

	abstract public void run();

	public long getTimeoutMs(){
		return 5000;
	}

}
