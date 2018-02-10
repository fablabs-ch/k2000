package ch.fablabs.fabjam.cocktail.api;

import ch.fablabs.fabjam.cocktail.data.entities.ItfData;
import ch.fablabs.fabjam.cocktail.exception.NotFoundException;
import ch.fablabs.fabjam.cocktail.repository.AbstractRepository;
import lombok.Setter;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.PathVariable;

import java.util.List;

public class AbstractCrudWS<T extends ItfData> {

	@Setter
	public AbstractRepository<T> repository;

	@RequestMapping("")
	public List<T> findAll() {
		return repository.findAll();
	}

	@RequestMapping(value = "{id}")
	public T getOne(@PathVariable("id") String id) {
		return getnEntity(id);
	}

	@RequestMapping(value = "", method = RequestMethod.POST)
	public T add(@RequestBody T entity) {
		entity.sanitize();
		return repository.insert(entity);
	}

	@RequestMapping(value = "{id}", method = RequestMethod.PUT)
	public T edit(@PathVariable("id") String id, @RequestBody T entity) {
		getnEntity(id);//just to throw 404
		entity.setId(id);
		entity.sanitize();
		return repository.save(entity);
	}

	@RequestMapping(value = "{id}", method = RequestMethod.DELETE)
	public T delete(@PathVariable("id") String id) {
		T ret = getnEntity(id);
		repository.delete(id);
		return ret;
	}

	protected T getnEntity(String id){
		T ret = repository.findOne(id);
		if (ret == null) {
			throw new NotFoundException("Entity with id " + id + " not found");
		}
		return ret;
	}
}
