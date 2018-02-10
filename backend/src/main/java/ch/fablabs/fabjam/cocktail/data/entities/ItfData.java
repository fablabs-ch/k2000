package ch.fablabs.fabjam.cocktail.data.entities;

public interface ItfData {

	void setId(String id);

	default void sanitize() {};
}
