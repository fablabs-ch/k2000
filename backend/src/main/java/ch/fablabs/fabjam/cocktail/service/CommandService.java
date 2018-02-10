package ch.fablabs.fabjam.cocktail.service;

import ch.fablabs.fabjam.cocktail.service.serial.SerialConnectionStarter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.xml.ws.ServiceMode;


@Service
public class CommandService {
	@Autowired
	private SerialConnectionStarter serialConnectionStarter;

	public boolean home() {
		return serialConnectionStarter.sendMessage("h");
	}

	public boolean tare() {
		return serialConnectionStarter.sendMessage("t");
	}

	public boolean fill(int distanceMm, int servoId, int gramme) {
		StringBuilder sb = new StringBuilder("f:");
		sb.append(distanceMm).append(':');
		sb.append(servoId).append(':');
		sb.append(gramme);
		return serialConnectionStarter.sendMessage(sb.toString());
	}

	public boolean move(int distanceMm) {
		String command = new StringBuilder("m:").append(distanceMm).toString();
		return serialConnectionStarter.sendMessage(command);
	}

	public boolean servoAperture(int servoId, int aperture) {
		String command = new StringBuilder("s:").append(servoId).append(':').append(aperture).toString();
		return serialConnectionStarter.sendMessage(command);
	}

}
