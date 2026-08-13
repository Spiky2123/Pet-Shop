#include "Dog.h"

Dog::Dog(int id, std::string breed, std::string name, std::string link, int age) : id(id), breed(breed), name(name), link(link), age(age) {}
Dog::Dog():id(-1), breed(""), name(""), link(""), age(0) {}

std::string Dog::toCSV() const
{
	std::string result;
	result += std::to_string(this->id) + "," + this->breed + "," + this->name + "," + this->link + "," + std::to_string(this->age);
	return result;
}

std::string Dog::toHTML() const
{
    std::string htmlFormat = "\t<tr>\n";
    htmlFormat += "\t\t<td><a href=\"" + this->link + "\">" + this->name + "</a></td>\n";
    htmlFormat += "\t\t<td>" + this->breed + "</td>\n";
    htmlFormat += "\t\t<td>" + std::to_string(this->age) + "</td>\n";
    htmlFormat += "\t</tr>\n";
    return htmlFormat;
}

Dog& Dog::operator=(const Dog& other)
{
    this->id = other.id;
    this->breed = other.breed;
    this->name = other.name;
    this->link = other.link;
    this->age = other.age;
    return *this;
}

bool Dog::operator<(const Dog& other)
{
    return this->breed < other.breed;
}

bool Dog::operator==(const Dog& other)
{
    return this->id == other.id;
}

std::ostream& operator<<(std::ostream& output_stream, const Dog& dog)
{
    output_stream << dog.id << "," << dog.breed << "," << dog.name << "," << dog.link << "," << dog.age;
    return output_stream;
}

std::istream& operator>>(std::istream& input_stream, Dog& dog)
{
    std::string line;
    std::getline(input_stream, line);
    if (line.empty())
        return input_stream;
    std::istringstream lineStream(line);

    std::string idString, breed, name, link, ageString;
    std::getline(lineStream, idString, ',');
    std::getline(lineStream, breed, ',');
    std::getline(lineStream, name, ',');
    std::getline(lineStream, link, ',');
    std::getline(lineStream, ageString, '\n');

    int id = std::stoi(idString);
    int age = std::stoi(ageString);

    dog = Dog(id, breed, name, link, age);
    return input_stream;
}
