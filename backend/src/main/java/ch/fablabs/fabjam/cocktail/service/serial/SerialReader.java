package ch.fablabs.fabjam.cocktail.service.serial;

import ch.fablabs.fabjam.cocktail.data.type.JmsTopic;
import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jms.core.JmsTemplate;

@Slf4j
@RequiredArgsConstructor
public class SerialReader implements SerialPortEventListener {

	private final SerialPort serialPort;

	protected StringBuffer buffer = new StringBuffer();

	@Autowired
	private JmsTemplate jmsTemplate;

	@Override
	public void serialEvent(SerialPortEvent event) {
		if (event.isRXCHAR()) {
			if (event.getEventValue() > 0) {
				try {
					String receivedData = serialPort.readString(event.getEventValue());
					buffer.append(receivedData);
					checkForLine();
				} catch (SerialPortException ex) {
					LOG.error("Error in receiving string from COM-port ", ex);
				}
			}
		} else {
			LOG.warn("Unknown event type {}", event.getEventType());
		}
	}

	public void checkForLine() {
		int newLine;
		do {
			newLine = buffer.indexOf("\n");
			if (newLine != -1) {
				String line = buffer.substring(0, newLine).replace("\r", "");
				buffer.delete(0, newLine + 1);
				LOG.trace("Read: {}", line);
				if (jmsTemplate != null) {
					jmsTemplate.convertAndSend(JmsTopic.SERIAL_INPUT, line);
				}
			}
		} while (newLine != -1);

	}


}
