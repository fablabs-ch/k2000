package ch.fablabs.fabjam.cocktail.api;

import ch.fablabs.fabjam.cocktail.data.serial.SerialStatus;
import ch.fablabs.fabjam.cocktail.service.serial.SerialService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.mvc.method.annotation.SseEmitter;

@Slf4j
@RestController
@RequestMapping("/api/sse")
public class SeverSentEventWS {

	@Autowired
	private SerialService serialService;


	@RequestMapping("status")
	public SseEmitter status() {
		return serialService.getStatusSSE();
	}
}
