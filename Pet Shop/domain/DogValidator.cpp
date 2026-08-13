#include "DogValidator.h"

ValidatorException::ValidatorException() : message("Validation Exception") {}

void DogValidator::validateDog(const Dog& dog)
{
    std::string errors;
    if (dog.getId() < 0) {
        errors += std::string("Id must be a non-negative integer.");
    }
    if (dog.getName().empty())
        errors += std::string("Name must not be empty\n");
    for (auto& c : dog.getName())
        if (c != ' ' && !isalpha(c)) {
            errors += std::string("Name must contain letters and spaces only.\n");
            break;
        }
    if (dog.getBreed().empty())
        errors += std::string("Color must not be empty.\n");
    for (auto& c : dog.getBreed())
        if (c != ' ' && !isalpha(c)) {
            errors += std::string("Breed must contain letters and spaces only.\n");
            break;
        }
    if (dog.getAge() < 0)
        errors += std::string("Age must be a non-negative integer.\n");
    if (dog.getLink().empty())
        errors += std::string("Link must not be empty.\n");

    if (!errors.empty())
        throw ValidatorException(errors);
}
