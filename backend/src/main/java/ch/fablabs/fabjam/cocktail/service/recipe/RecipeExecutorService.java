package ch.fablabs.fabjam.cocktail.service.recipe;

import ch.fablabs.fabjam.cocktail.data.entities.Ingredient;
import ch.fablabs.fabjam.cocktail.data.entities.IngredientConfig;
import ch.fablabs.fabjam.cocktail.data.entities.RecipeItem;
import ch.fablabs.fabjam.cocktail.data.recipe.RecipeItemFull;
import ch.fablabs.fabjam.cocktail.exception.BusyException;
import ch.fablabs.fabjam.cocktail.exception.NotFoundException;
import ch.fablabs.fabjam.cocktail.repository.IngredientConfigRepository;
import ch.fablabs.fabjam.cocktail.repository.IngredientRepository;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.AutowireCapableBeanFactory;
import org.springframework.core.task.AsyncTaskExecutor;
import org.springframework.stereotype.Service;

import java.util.AbstractMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.concurrent.Future;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.function.Consumer;
import java.util.stream.Collectors;

@Slf4j
@Service
public class RecipeExecutorService {

	private AtomicBoolean working;

	@Autowired
	private AsyncTaskExecutor executor;

	@Autowired
	private AutowireCapableBeanFactory autowireCapableBeanFactory;

	@Autowired
	private IngredientRepository ingredientRepository;

	@Autowired
	private IngredientConfigRepository ingredientConfigRepository;

	private Optional<Map.Entry<RecipeExecutor, Future<?>>> currentRecipeExecutor;

	public RecipeExecutorService() {
		this.working = new AtomicBoolean(false);
	}

	public void execute(List<RecipeItem> items) {
		Future<?> future;
		RecipeExecutor recipeExecutor;
		try {
			boolean wasWorking = working.getAndSet(true);
			if (wasWorking) {
				LOG.error("A task is already ongoing, we cannot execute another order");
				throw new BusyException("A recipe is already running, wait for the end");
			}

			Consumer<Boolean> resultConsumer = result -> {
				LOG.info("Execution ends with a result: {}", result);
				this.working.set(false);
				currentRecipeExecutor = Optional.empty();
			};

			List<RecipeItemFull> itemsFull = getFullItems(items);
			recipeExecutor = new RecipeExecutor(itemsFull, resultConsumer);
			autowireCapableBeanFactory.autowireBean(recipeExecutor);

			future = executor.submit(recipeExecutor);
		} catch (Exception ex) {
			LOG.error("Unable to start the making of the recipe", ex);
			working.set(false);
			throw ex;
		}

		currentRecipeExecutor = Optional.of(new AbstractMap.SimpleEntry<RecipeExecutor, Future<?>>(recipeExecutor, future));
	}

	public List<RecipeItemFull> getFullItems(List<RecipeItem> items) {

		List<IngredientConfig> configs = ingredientConfigRepository.findAll();
		List<Ingredient> ingredients = ingredientRepository.findAll();
		return items.stream()
			.map(item -> {

				Ingredient ingredient = ingredients.stream()
					.filter(i -> i.getId().equals(item.getIngredientId()))
					.findAny()
					.orElseThrow(() -> new NotFoundException("Ingredient with id " + item.getIngredientId() + " was not found"));

				IngredientConfig config = configs.stream()
					.filter(c -> c.getIngredientId().equals(ingredient.getId()))
					.findAny()
					.orElseThrow(() -> new NotFoundException("Configuration for Ingredient with id " + item.getIngredientId() + " was not found"));

				return RecipeItemFull.builder()
					.config(config)
					.ingredient(ingredient)
					.ml(item.getMl())
					.build();
			}).collect(Collectors.toList());
	}

	public void cancel() {
		currentRecipeExecutor.ifPresent(e -> {
			e.getKey().cancel();
			e.getValue().cancel(true);
			working.set(false);
			currentRecipeExecutor = Optional.empty();
		});
	}
}
