#pragma once
#include "../repository/BaseRepository.h"
#include "UndoService.h"
#include "ServiceException.h"

class AdminService {
private:
	BaseRepository& repository;
	UndoService undoService;
	int biggestId;
public:
	AdminService& operator=(const AdminService& other);
	AdminService(BaseRepository& repository) : repository(repository) {
		biggestId = 0;
		std::vector<Dog> data = repository.getAll();
		for (auto a : data) {
			biggestId = std::max(biggestId, a.getId());
		}
	}

	std::vector<Dog> getAllDogs() { return this->repository.getAll(); }
	Dog getDogAt(int index) { return this->repository.getAll().at(index); }
	const int getBiggestId();
	void addDog(const Dog& dog);
	void removeDog(Dog& dog);
	void updateDog(Dog& newDog);
	int size() const { return this->repository.size(); }
	void undo();
	void redo();
};