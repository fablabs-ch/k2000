package ch.fablabs.fabjam.cocktail.api;

import ch.fablabs.fabjam.cocktail.service.CommandService;
import ch.fablabs.fabjam.cocktail.service.serial.SerialConnectionStarter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;


@RestController
@RequestMapping("/api/debug")
public class DebugWS {

	@Autowired
	private SerialConnectionStarter serialConnectionStarter;

	@Autowired
	private CommandService commandService;

	@RequestMapping(value = "move/{mm}")
	public boolean setCarrierPost(@PathVariable("mm") int mm) {
		return commandService.move(mm);
	}

	@RequestMapping(value = "servo/{servoId}/{aperture}")
	public boolean setCarrierPost(@PathVariable("servoId") int servo, @PathVariable("aperture") int aperture) {
		return commandService.servoAperture(servo, aperture);
	}

	@RequestMapping(value = "fill/{mm}/{servoId}/{aperture}")
	public boolean fill(@PathVariable("mm") int mm, @PathVariable("servoId") int servo, @PathVariable("aperture") int aperture) {
		return commandService.fill(mm, servo, aperture);
	}

	@RequestMapping(value = "tare", method = RequestMethod.POST)
	public String tare() {
		return "not implemented";
	}

	@RequestMapping(value = "test/{message}")
	public String test(@PathVariable("message") String message) {
		serialConnectionStarter.sendMessage(message);
		return "ok";
	}
}
