#pragma once
#include "../domain/Dog.h"
#include "../domain/DogValidator.h"
#include "RepositoryException.h"
#include <vector>
#include <algorithm>

class BaseRepository {
public:
	virtual ~BaseRepository() = default;
	virtual int size() = 0;
	virtual std::vector<Dog> getAll() = 0;
	virtual bool isInRepo(const Dog& dog) = 0;
	virtual Dog getDog(int id) = 0;
	virtual void addDog(const Dog& dog) = 0;
	virtual void removeDog(const Dog& dog) = 0;
	virtual void updateDog(const Dog& oldDog, const Dog& newDog) = 0;

};