#pragma once
#include "AdoptionRepository.h"
#include <fstream>

class FileRepository : public AdoptionRepository {
protected:
	std::string filename;
public:
	FileRepository(std::string filename);
	virtual ~FileRepository() = default;
	
	virtual void writeToFile() = 0;
	virtual void displayRepo() = 0;
};

class HTMLRepository : public FileRepository {
public:
	HTMLRepository(std::string file) : FileRepository(file) {}

	void writeToFile() override;
	void displayRepo() override;
};

class CSVRepository : public FileRepository {
public:
	CSVRepository(std::string file): FileRepository(file) {}

	void writeToFile() override;
	void displayRepo() override;
};