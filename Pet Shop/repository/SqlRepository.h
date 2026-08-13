#pragma once
#include "BaseRepository.h"
#include "../utils/sql/sqlite_orm.h"
#include "../utils/sql/sqlite3.h"

using namespace sqlite_orm;

inline auto initStorage(const std::string& filename) {
	return make_storage(filename, make_table(
		"dogs",
		make_column("id", &Dog::getId, &Dog::setId, primary_key()),
		make_column("breed", &Dog::getBreed, &Dog::setBreed),
		make_column("name", &Dog::getName, &Dog::setName),
		make_column("link", &Dog::getLink, &Dog::setLink),
		make_column("age", &Dog::getAge, &Dog::setAge)
	));
}

using Storage = decltype(initStorage(""));

class SqlRepository : public BaseRepository {
private:
	Storage storage;
	std::string filename;
public:
	explicit SqlRepository(const std::string& filename);
	Dog getDog(int id) override;
	std::vector<Dog> getAll();
	bool isInRepo(const int id);
	bool isInRepo(const Dog& dog) override;
	int size() override;
	void addDog(const Dog& dog);
	void removeDog(const Dog& dog);
	void updateDog(const Dog& oldDog, const Dog& newDog);
};