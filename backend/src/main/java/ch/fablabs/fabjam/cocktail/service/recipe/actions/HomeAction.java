package ch.fablabs.fabjam.cocktail.service.recipe.actions;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class HomeAction extends AbstractAction {

	@Override
	public void initialRun() {
		commandService.home();
	}

	@Override
	public void run() {
		int dist = serialService.getDistanceFromHomeInMm().getValue();
		LOG.debug("dist={}", dist);
		setFinished(dist<10);
	}
}
