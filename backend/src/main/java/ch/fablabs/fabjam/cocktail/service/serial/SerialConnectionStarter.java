package ch.fablabs.fabjam.cocktail.service.serial;

import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.beans.factory.config.AutowireCapableBeanFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Service;

import javax.annotation.PreDestroy;
import java.util.Optional;
import java.util.concurrent.Executor;

@Slf4j
@Service
public class SerialConnectionStarter implements CommandLineRunner {

	@Autowired
	private Executor threadPoolTaskExecutor;

	@Autowired
	private AutowireCapableBeanFactory autowireCapableBeanFactory;

	@Value("${serial.port:/dev/ttyUSB0}")
	private String port;

	private Optional<SerialConnection> serialConnection = Optional.empty();

	@Override
	public void run(String... strings) throws Exception {
		serialConnection = Optional.of(new SerialConnection(port));
		autowireCapableBeanFactory.autowireBean(serialConnection.get());
		threadPoolTaskExecutor.execute(serialConnection.get());
	}

	@PreDestroy
	protected void preDestroy() {
		serialConnection.ifPresent(c -> c.close());
	}

	public boolean sendMessage(String rawLine) {
		if (serialConnection.isPresent()) {
			return serialConnection.get().send(rawLine);
		} else {
			LOG.error("Cannot send message serial '{}' because not connexion are available", rawLine);
			return false;
		}
	}
}
