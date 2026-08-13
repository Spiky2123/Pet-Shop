#pragma once
#include "../repository/TextFileRepository.h"
#include "../repository/FileRepo.h"
#include "ServiceException.h"

class UserService {
private:
	BaseRepository& repository;
	FileRepository& adoptionRepo;
public:
	UserService(BaseRepository& repository, FileRepository& adoptionRepo): repository(repository), adoptionRepo(adoptionRepo) {}
	void saveAdoptions() const { this->adoptionRepo.writeToFile(); }
	void displayAdoptions() const { this->adoptionRepo.displayRepo(); }
	std::vector<Dog> getDogsByBreed(std::string breed) const;
	std::vector<Dog> getAll() const { return this->repository.getAll(); }
	std::vector<Dog> getAdoptions() const { return this->adoptionRepo.getAll(); }
	void adoptDog(Dog dog);
};