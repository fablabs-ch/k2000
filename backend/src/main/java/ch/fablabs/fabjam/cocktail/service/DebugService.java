package ch.fablabs.fabjam.cocktail.service;

import ch.fablabs.fabjam.cocktail.service.serial.SerialService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Service;

@Slf4j
@Service
public class DebugService implements CommandLineRunner {

	@Autowired
	private SerialService serialService;

	@Override
	public void run(String... strings) throws Exception {
		if (LOG.isTraceEnabled()) {
			serialService.getSerialStatus().subscribe(v -> LOG.trace("Status {}", v));
		}
	}
}
