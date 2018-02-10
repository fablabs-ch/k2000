package ch.fablabs.fabjam.cocktail.service.serial;

import org.junit.Test;

import static org.junit.Assert.*;

public class SerialReaderTest {
	@Test
	public void checkForLine() throws Exception {

		SerialReader reader = new SerialReader(null);
		reader.buffer.append("test\nsalut\r\nbl");
		reader.checkForLine();
		reader.buffer.append("abbla\n");
		reader.checkForLine();
	}

}
