package ch.fablabs.fabjam.cocktail.api;

import ch.fablabs.fabjam.cocktail.data.entities.Recipe;
import ch.fablabs.fabjam.cocktail.repository.RecipeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.PostConstruct;

@RestController
@RequestMapping("/api/recipies")
public class RecipiesWS extends AbstractCrudWS<Recipe> {

	@Autowired
	private RecipeRepository recipeRepository;

	@PostConstruct
	public void postConstruct() {
		this.setRepository(recipeRepository);
	}
}
