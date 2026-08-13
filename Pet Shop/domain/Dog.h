#pragma once
#include <string>
#include <sstream>

class Dog {
private:
	std::string breed, name, link;
	int id, age;
public:
	// -- constructors --
	Dog(int id, std::string breed, std::string name, std::string link, int age);
	Dog();

	// -- special methods --
	[[nodiscard]] std::string toCSV() const;
	[[nodiscard]] std::string toHTML() const;

	// -- operators --
	Dog& operator=(const Dog& other);
	bool operator<(const Dog& other);
	bool operator==(const Dog& other);
	friend std::ostream& operator<<(std::ostream& output_stream, const Dog& dog);
	friend std::istream& operator>>(std::istream& input_stream, Dog& dog);

	// -- getters --
	[[nodiscard]] std::string getBreed() const { return this->breed; }
	[[nodiscard]] std::string getName() const { return this->name; }
	[[nodiscard]] std::string getLink() const { return this->link; }
	[[nodiscard]] int getId() const { return this->id; }
	[[nodiscard]] int getAge() const { return this->age; }

	// -- setters --
	void setId(const int id) { this->id = id; }
	void setBreed(const std::string breed) { this->breed = breed; }
	void setName(const std::string name) { this->name = name; }
	void setLink(const std::string link) { this->link = link; }
	void setAge(const int age) { this->age = age; }
};