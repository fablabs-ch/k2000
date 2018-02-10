package ch.fablabs.fabjam.cocktail.api;

import ch.fablabs.fabjam.cocktail.data.entities.RecipeItem;
import ch.fablabs.fabjam.cocktail.service.recipe.RecipeExecutorService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;
import java.util.List;


@RestController
@RequestMapping("/api/command")
public class CommandWS {

	@Autowired
	private RecipeExecutorService recipeExecutorService;

	@RequestMapping(value = "order", method = RequestMethod.POST)
	public String order(@RequestBody ArrayList<RecipeItem> items) {
		recipeExecutorService.execute(items);
		return "ok";
	}

	@RequestMapping(value = "stop", method = RequestMethod.POST)
	public String stop() {
		recipeExecutorService.cancel();
		return "ok";
	}

}
