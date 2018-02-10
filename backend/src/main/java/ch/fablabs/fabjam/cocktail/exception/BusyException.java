package ch.fablabs.fabjam.cocktail.exception;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

@ResponseStatus(HttpStatus.CONFLICT)
public class BusyException extends RuntimeException {
	public BusyException(String message) {
		super(message);
	}
}
