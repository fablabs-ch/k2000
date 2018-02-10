package ch.fablabs.fabjam.cocktail.data.recipe;

import ch.fablabs.fabjam.cocktail.data.entities.Ingredient;
import ch.fablabs.fabjam.cocktail.data.entities.IngredientConfig;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class RecipeItemFull {
	private Ingredient ingredient;
	private IngredientConfig config;
	private int ml;
}
