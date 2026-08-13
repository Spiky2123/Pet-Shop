#include "FileRepo.h"

FileRepository::FileRepository(std::string filename) : filename(filename){}

void HTMLRepository::writeToFile()
{
	std::ofstream out(this->filename);
	out << "<!DOCTYPE html>\n<html>\n<head>\n\t<title>Dog</title>\n</head>\n<body>\n<table border=\"1\">\n";
	out << "\t<tr>\n\t\t<td>Name</td>\n\t\t<td>Breed</td>\n\t\t<td>Age</td>\n";
	for (const auto& dog : this->data)
		out << dog.toHTML();
	out << "</table>\n</body>\n</html>";
	out.close();
}

void HTMLRepository::displayRepo()
{
	std::string command = "start " + this->filename;
	system(command.c_str());
}

void CSVRepository::writeToFile()
{
	std::ofstream out(this->filename);
	for(const auto& dog: this->data) {
		out << dog.toCSV() << '\n';
	}
	out.close();
}

void CSVRepository::displayRepo()
{
	std::string command = "start " + this->filename;
	system(command.c_str());
}
