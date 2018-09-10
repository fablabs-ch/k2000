package ch.fablabs.fabjam.cocktail.boot;

import ch.fablabs.fabjam.cocktail.service.serial.SerialService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

import java.util.concurrent.Executor;

@Slf4j
@Component
public class ConnexionChecker implements CommandLineRunner {

	@Autowired
	private SerialService serialService;

	@Autowired
	private Executor threadPoolTaskExecutor;

	@Override
	public void run(String... strings) throws Exception {
		threadPoolTaskExecutor.execute(() -> {
			Thread.currentThread().setName("ConnexionChecker");
			try {
				while (!Thread.interrupted()) {
					serialService.checkConnexionStatus();
					Thread.sleep(1000);
				}
			} catch (Exception ex) {
				LOG.error("Error in connexion checker", ex);
			}
		});
	}
}
