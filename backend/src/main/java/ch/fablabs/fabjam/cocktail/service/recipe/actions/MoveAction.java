package ch.fablabs.fabjam.cocktail.service.recipe.actions;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

@RequiredArgsConstructor
@Slf4j
public class MoveAction extends AbstractAction {

	private final int distanceMm;

	@Override
	protected void initialRun() {
		commandService.move(distanceMm);
	}

	@Override
	public void run() {
		setFinished(endOfCommandReceived("m"));
	}
}
