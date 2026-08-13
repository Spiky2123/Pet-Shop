#pragma once
#include <string>
#include <exception>

class ServiceException : public std::exception {
private:
	std::string message;
public:
	explicit ServiceException(std::string message = "Undo Exception");
	[[nodiscard]] const char* what() const noexcept override;
};