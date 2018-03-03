package ch.fablabs.fabjam.cocktail.service.recipe.actions;

import ch.fablabs.fabjam.cocktail.data.recipe.RecipeItemFull;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@RequiredArgsConstructor
public class FillAction extends AbstractAction {

	private final RecipeItemFull recipeItemFull;

	@Override
	protected void initialRun() {
		commandService.fill(recipeItemFull.getConfig().getValveDistanceMm(), recipeItemFull.getConfig().getValveId(), recipeItemFull.getMl());
	}

	@Override
	public long getTimeoutMs() {
		return 60000;
	}

	@Override
	public void run() {
		setFinished(endOfCommandReceived("f"));
	}

	@Override
	public void cancelling() {
		commandService.servoAperture(recipeItemFull.getConfig().getValveId(), 0);
	}
}
