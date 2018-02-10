package ch.fablabs.fabjam.cocktail.data.entities;

import lombok.Data;
import org.springframework.data.annotation.Id;

@Data
public class IngredientConfig implements ItfData {
	@Id
	private String id;
	private String ingredientId;
	private Long valveDistanceMm;
	private Long valveId;
}
