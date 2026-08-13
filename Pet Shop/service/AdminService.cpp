#include "AdminService.h"

AdminService& AdminService::operator=(const AdminService& other)
{
    this->repository = other.repository;
    return *this;
}

const int AdminService::getBiggestId()
{
    return biggestId;
}

void AdminService::addDog(const Dog& dog)
{
    if (this->repository.isInRepo(dog)) {
        throw ServiceException("Dog already in repository.");
    }
    this->repository.addDog(dog);
    biggestId = std::max(biggestId, dog.getId());
    this->undoService.addAction(std::make_unique<ActionAdd>(this->repository, dog));
}

void AdminService::removeDog(Dog& dog)
{
    try {
        dog = this->repository.getDog(dog.getId());
    }
    catch (RepositoryException&) {
        throw ServiceException("Dog not found\n");
    }

    this->repository.removeDog(dog);
    this->undoService.addAction(std::make_unique<ActionRemove>(this->repository, dog));
}

void AdminService::updateDog(Dog& newDog)
{
    Dog oldDog;
    try {
        oldDog = this->repository.getDog(newDog.getId());

    }
    catch (RepositoryException&) {
        throw ServiceException("Dog not found\n");
    }
    
    this->repository.updateDog(oldDog, newDog);
    this->undoService.addAction(std::make_unique<ActionUpdate>(this->repository, oldDog, newDog));
}

void AdminService::undo()
{
    this->undoService.undo();
}

void AdminService::redo()
{
    this->undoService.redo();
}
