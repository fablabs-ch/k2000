package ch.fablabs.fabjam.cocktail.data.serial;

import lombok.Data;

import java.time.Instant;

@Data
public class EndOfCommand {
	private final String command;
	private final Instant time;

	public EndOfCommand(String command) {
		this.command = command;
		this.time = Instant.now();
	}
}
