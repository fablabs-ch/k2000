package ch.fablabs.fabjam.cocktail.api;

import ch.fablabs.fabjam.cocktail.data.entities.IngredientConfig;
import ch.fablabs.fabjam.cocktail.repository.IngredientConfigRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.PostConstruct;

@RestController
@RequestMapping("/api/config")
public class ConfigWS extends AbstractCrudWS<IngredientConfig> {

	@Autowired
	private IngredientConfigRepository ingredientConfigRepository;

	@PostConstruct
	public void postConstruct() {
		this.setRepository(ingredientConfigRepository);
	}


}
