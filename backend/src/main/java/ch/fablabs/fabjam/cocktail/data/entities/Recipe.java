package ch.fablabs.fabjam.cocktail.data.entities;

import lombok.Data;
import org.springframework.data.annotation.Id;

import java.util.ArrayList;
import java.util.List;

@Data
public class Recipe implements ItfData {

	@Id
	private String id;

	private String name;
	private String description;
	private String imageUrl;
	private boolean shakeYourBody;
	private List<RecipeItem> items;

	@Override
	public void sanitize() {
		if (items == null) {
			items = new ArrayList<>();
		}
	}
}
