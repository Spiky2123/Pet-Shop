#pragma once
#include "../domain/Dog.h"
#include <exception>
#include <vector>

class AdoptionException : public std::exception {
private:
	std::string message;
public:
	AdoptionException(): message("Adoption Exception") {}
	explicit AdoptionException(std::string message) : message(message) {}
	[[nodiscard]] const char* what() const noexcept override { return this->message.c_str(); }
};

class AdoptionRepository {
protected:
	std::vector<Dog> data;
public:
	[[nodiscard]] int size() const { return this->data.size(); }
	[[nodiscard]] std::vector<Dog> getAll() { return this->data; }
	
	void addDog(Dog& dog);
};