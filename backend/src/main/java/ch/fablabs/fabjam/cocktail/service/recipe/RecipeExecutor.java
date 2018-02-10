package ch.fablabs.fabjam.cocktail.service.recipe;

import ch.fablabs.fabjam.cocktail.data.recipe.RecipeItemFull;
import ch.fablabs.fabjam.cocktail.service.recipe.actions.AbstractAction;
import ch.fablabs.fabjam.cocktail.service.recipe.actions.FillAction;
import ch.fablabs.fabjam.cocktail.service.recipe.actions.HomeAction;
import ch.fablabs.fabjam.cocktail.service.recipe.actions.TareAction;
import ch.fablabs.fabjam.cocktail.service.serial.SerialService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;

import java.util.LinkedList;
import java.util.List;
import java.util.function.Consumer;
import java.util.stream.Collectors;

@Slf4j
@RequiredArgsConstructor
public class RecipeExecutor implements Runnable {

	private final List<RecipeItemFull> items;
	private final Consumer<Boolean> endCallback;

	@Value("${recipe.executor.delayms:100}")
	private int delayMs;

	@Autowired
	private SerialService serialService;

	@Override
	public void run() {
		long totalStart = System.currentTimeMillis();
		try {
			LOG.debug("Start recipe of {} items", items.size());

			//wait for first status
			checkStatusDelay();

			for (AbstractAction action : getActionList()) {
				long actionStart = System.currentTimeMillis();
				LOG.debug("Start action {}", action);

				action.setSerialService(serialService);
				int iter = 0;
				boolean timeout;

				action.initialRun();
				do {
					Thread.sleep(delayMs);
					action.run();
					checkStatusDelay();
					iter++;
					timeout = (System.currentTimeMillis() - actionStart) >= action.getTimeoutMs();
				} while (!action.isFinished() && !timeout);

				long timeMs = System.currentTimeMillis() - actionStart;
				if (timeout) {
					LOG.info("Timeout for action {} after {} iterations and {}ms", action, iter, timeMs);
					break;
				} else {
					LOG.info("End of action {} after {} iterations and {}ms", action, iter, timeMs);
				}
			}

			LOG.debug("End of recipe after {}ms", (System.currentTimeMillis() - totalStart));
			endCallback.accept(true);
		} catch (
			InterruptedException e)

		{
			endCallback.accept(false);
			LOG.debug("Task interrupted after {}ms", (System.currentTimeMillis() - totalStart));
		}

	}

	public void cancel() {
		LOG.warn("Task was cancelled");
		endCallback.accept(false);
	}

	protected List<AbstractAction> getActionList() {
		List<AbstractAction> actions = new LinkedList<>();
		actions.add(new TareAction());
		actions.add(new HomeAction());
		actions.addAll(items.stream()
			.map(item -> new FillAction(item))
			.collect(Collectors.toList()));
		actions.add(new HomeAction());
		return actions;
	}

	protected void checkStatusDelay() {
		//TODO wait for status


	}
}
