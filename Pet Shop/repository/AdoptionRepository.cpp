#include "AdoptionRepository.h"

void AdoptionRepository::addDog(Dog& dog)
{
	auto pos = std::find(this->data.begin(), this->data.end(), dog);
	if (pos == this->data.end())
		this->data.push_back(Dog(dog.getId(), dog.getBreed(), dog.getName(), dog.getLink(), dog.getAge()));
	else
		throw AdoptionException("Dog already exists.");
}
