#include "SqlRepository.h"

SqlRepository::SqlRepository(const std::string& filename) :storage(initStorage(filename))
{
	storage.sync_schema();
}

Dog SqlRepository::getDog(int id)
{
	auto dog = storage.get_pointer<Dog>(id);
	if (!dog) {
		throw RepositoryException("Dog with ID " + std::to_string(id) + " not found.\n");
	}
	return *dog;
}

std::vector<Dog> SqlRepository::getAll()
{
	auto dogs = storage.get_all<Dog>();
	return dogs;
}

bool SqlRepository::isInRepo(const int id)
{
	auto count = storage.count<Dog>(where(c(&Dog::getId) == id));
	return count > 0;
}

bool SqlRepository::isInRepo(const Dog& dog)
{
	return this->isInRepo(dog.getId());
}


int SqlRepository::size()
{
	return storage.count<Dog>();
}

void SqlRepository::addDog(const Dog& dog)
{
	if (isInRepo(dog.getId())) {
		throw RepositoryException("Dog with ID " + std::to_string(dog.getId()) + " already exists.\n");
	}
	storage.insert(dog);
}

void SqlRepository::removeDog(const Dog& dog)
{
	if (!isInRepo(dog.getId()))
	{
		throw RepositoryException("Dog with ID " + std::to_string(dog.getId()) + " not found.\n");
	}
	storage.remove<Dog>(dog.getId());
}

void SqlRepository::updateDog(const Dog& oldDog, const Dog& newDog)
{
	if (!isInRepo(oldDog.getId())) {
		throw RepositoryException("Dog with ID " + std::to_string(oldDog.getId()) + " not found.\n");
	}
	storage.update(newDog);
}
