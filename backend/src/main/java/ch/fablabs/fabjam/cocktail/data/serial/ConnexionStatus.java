package ch.fablabs.fabjam.cocktail.data.serial;

import lombok.Builder;
import lombok.Data;

import java.util.Date;

@Builder
@Data
public class ConnexionStatus {
	private boolean connected;
	private long lastStatus;
}
