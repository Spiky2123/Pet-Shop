#include "UserService.h"

std::vector<Dog> UserService::getDogsByBreed(std::string breed) const
{
    std::vector<Dog> result;
    std::vector<Dog> data = this->repository.getAll();
    for (auto a : data) {
        if (a.getBreed().find(breed) != std::string::npos) {
            result.push_back(a);
        }
    }
    return result;
}

void UserService::adoptDog(Dog dog)
{
    if (!this->repository.isInRepo(dog))
        throw ServiceException("Dog not in repository.");
    this->repository.removeDog(dog);
    this->adoptionRepo.addDog(dog);
}
