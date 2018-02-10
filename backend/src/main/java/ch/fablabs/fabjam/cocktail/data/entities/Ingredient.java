package ch.fablabs.fabjam.cocktail.data.entities;

import ch.fablabs.fabjam.cocktail.data.type.IngredientType;
import lombok.Data;
import org.springframework.data.annotation.Id;

@Data
public class Ingredient implements ItfData {
	@Id
	private String id;

	private String name;
	private IngredientType type;
	private boolean manual;
}
