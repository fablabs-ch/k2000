package ch.fablabs.fabjam.cocktail.repository;

import ch.fablabs.fabjam.cocktail.data.entities.ItfData;
import org.springframework.data.mongodb.repository.MongoRepository;

public interface AbstractRepository<T extends ItfData> extends MongoRepository<T, String> {

}
