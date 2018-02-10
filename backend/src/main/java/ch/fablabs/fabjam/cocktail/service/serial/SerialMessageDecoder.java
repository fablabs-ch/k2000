package ch.fablabs.fabjam.cocktail.service.serial;

import ch.fablabs.fabjam.cocktail.data.serial.SerialStatus;
import ch.fablabs.fabjam.cocktail.data.type.JmsTopic;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jms.annotation.JmsListener;
import org.springframework.jms.core.JmsTemplate;
import org.springframework.stereotype.Service;

@Slf4j
@Service
public class SerialMessageDecoder {

	@Autowired
	private JmsTemplate jmsTemplate;

	@JmsListener(destination = JmsTopic.SERIAL_INPUT)
	public void receiveMessage(String rawLine) {
		String[] split = rawLine.split(":");
		String command = split[0];
		if (command.equals("s")) {
			decodeStatus(rawLine, split);
		} else if (command.equals("h") || command.equals("t") || command.equals("f") || command.equals("m") || command.equals("a")) {
			decodeEndOfCOmmand(rawLine, split);
		} else if (command.equals("i")) {
			LOG.trace("Info: {}", rawLine);
		} else {
			LOG.warn("Unknown message {}", rawLine);
		}
	}

	protected void decodeStatus(String raw, String[] parts) {
		if (parts.length == 3) {
			try {
				int dist = (int) Double.parseDouble(parts[1]);
				int weight = (int) Double.parseDouble(parts[2]);
				SerialStatus status = SerialStatus.builder()
					.carrierDistMm(dist)
					.payloadWeightGr(weight)
					.build();
				jmsTemplate.convertAndSend(JmsTopic.SERIAL_STATUS, status);
			} catch (NumberFormatException ex) {
				LOG.error("Unable to parse integer from status: {}", raw);
			}
		} else {
			LOG.error("SerialStatus message must have 3 parts but had {} : {}", parts.length, raw);
		}
	}

	protected void decodeEndOfCOmmand(String raw, String[] parts) {
		jmsTemplate.convertAndSend(JmsTopic.SERIAL_END_OF_COMMAND, parts[0]);
	}
}
