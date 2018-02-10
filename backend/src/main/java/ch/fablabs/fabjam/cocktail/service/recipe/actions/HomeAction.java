package ch.fablabs.fabjam.cocktail.service.recipe.actions;

import ch.fablabs.fabjam.cocktail.data.serial.SerialStatus;
import ch.fablabs.fabjam.cocktail.service.serial.command.HomeCommand;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class HomeAction extends AbstractAction {

	@Override
	public void initialRun() {
		serialService.sendCommand(new HomeCommand());
	}

	@Override
	public void run() {
		int dist = serialService.getDistanceFromHomeInMm().getValue();
		LOG.debug("dist={}", dist);
		setFinished(dist==0);
	}
}
