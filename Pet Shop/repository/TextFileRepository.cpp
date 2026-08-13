#include "TextFileRepository.h"

TextFileRepository::TextFileRepository(std::string filename): filename(filename)
{
	this->loadDataFromFile();
}

TextFileRepository::~TextFileRepository()
{
	this->saveDataToFile();
}

Dog TextFileRepository::getDog(int id)
{
	for (auto dog : this->data) {
		if (dog.getId() == id)
			return dog;
	}
}

bool TextFileRepository::isInRepo(const Dog& dog)
{
	return (this->getDogPosition(dog) != -1);
}

void TextFileRepository::addDog(const Dog& dog)
{
	this->data.push_back(dog);
	std::sort(this->data.begin(), this->data.end());
	this->saveDataToFile();
}

void TextFileRepository::removeDog(const Dog& dog)
{
	int index = this->getDogPosition(dog);
	if (index == -1)
		throw RepositoryException("Dog not in repository\n");
	this->data.erase(this->data.begin() + index);
	this->saveDataToFile();
}

void TextFileRepository::updateDog(const Dog& oldDog, const Dog& newDog)
{
	int index = this->getDogPosition(oldDog);
	if (index == -1)
		throw RepositoryException("Dog not in repository\n");
	this->data.at(index) = newDog;
	this->saveDataToFile();
}

int TextFileRepository::getDogPosition(const Dog& dog)
{
	const auto it = std::find(this->data.begin(), this->data.end(), dog);
	if (it == this->data.end())
		return -1;
	return static_cast<int>(it - this->data.begin());
}

void TextFileRepository::loadDataFromFile()
{
	if (this->filename.empty())
		return;

	this->data.erase(this->data.begin(), this->data.end());
	std::ifstream fin(this->filename);
	std::string line;
	Dog newDog;
	while (fin >> newDog) {
		if (newDog.getId() == -1)
			break;
		this->data.push_back(newDog);
	}
	fin.close();
}

void TextFileRepository::saveDataToFile()
{
	if (this->filename.empty())
		return;
	
	std::ofstream fout(this->filename);
	for (const auto& dog : this->data) {
		fout << dog << '\n';
	}
	fout.close();
}
