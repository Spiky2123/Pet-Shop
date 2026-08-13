#pragma once
#include <fstream>
#include "BaseRepository.h"

class TextFileRepository : public BaseRepository {
private:
	std::vector<Dog> data;
	std::string filename;
public:
	explicit TextFileRepository(std::string filename);
	~TextFileRepository() override;

	int size() override { return this->data.size(); }
	std::vector<Dog> getAll() override { return this->data; }
	Dog getDog(int id) override;

	bool isInRepo(const Dog& dog) override;
	void addDog(const Dog& dog) override;
	void removeDog(const Dog& dog) override;
	void updateDog(const Dog& oldDog, const Dog& newDog) override;
private:
	int getDogPosition(const Dog& dog);
	void loadDataFromFile();
	void saveDataToFile();
};