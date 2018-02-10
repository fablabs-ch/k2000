package ch.fablabs.fabjam.cocktail.data.serial;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class SerialStatus {

	private int carrierDistMm;
	private int payloadWeightGr;
}
