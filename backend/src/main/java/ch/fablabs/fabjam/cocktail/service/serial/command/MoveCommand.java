package ch.fablabs.fabjam.cocktail.service.serial.command;

public class MoveCommand extends AbstractCommand {
	public MoveCommand(int distMm) {
		super('m', distMm);
	}
}
