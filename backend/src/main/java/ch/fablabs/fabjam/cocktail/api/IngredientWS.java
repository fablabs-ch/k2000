package ch.fablabs.fabjam.cocktail.api;

import ch.fablabs.fabjam.cocktail.data.entities.Ingredient;
import ch.fablabs.fabjam.cocktail.repository.IngredientRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.PostConstruct;

@RestController
@RequestMapping("/api/ingredients")
public class IngredientWS extends AbstractCrudWS<Ingredient> {

	@Autowired
	private IngredientRepository ingredientRepository;

	@PostConstruct
	public void postConstruct() {
		this.setRepository(ingredientRepository);
	}

}
