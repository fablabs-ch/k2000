package ch.fablabs.fabjam.cocktail.service.recipe.actions;

import ch.fablabs.fabjam.cocktail.data.entities.Ingredient;
import ch.fablabs.fabjam.cocktail.data.recipe.RecipeItemFull;
import ch.fablabs.fabjam.cocktail.data.serial.SerialStatus;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@RequiredArgsConstructor
public class FillAction extends AbstractAction {

	private final RecipeItemFull recipeItemFull;

	@Override
	public void run() {
setFinished(true);
	}
}
