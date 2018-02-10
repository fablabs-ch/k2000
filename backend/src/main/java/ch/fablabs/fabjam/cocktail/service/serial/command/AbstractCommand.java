package ch.fablabs.fabjam.cocktail.service.serial.command;

import java.util.Optional;

abstract public class AbstractCommand {
	protected char command;
	protected Optional<Integer> value;

	public AbstractCommand(char command) {
		this.command = command;
		this.value = Optional.empty();
	}

	public AbstractCommand(char command, int value) {
		this.command = command;
		this.value = Optional.of(value);
	}

	public String getCommandAsString() {
		StringBuilder sb = new StringBuilder();
		sb.append(command);
		value.ifPresent(v -> {
			sb.append(':');
			sb.append(value);
		});
		return sb.toString();
	}
}
