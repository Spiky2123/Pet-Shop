#include "ServiceException.h"

ServiceException::ServiceException(std::string message) : message(message) { }

const char* ServiceException::what() const noexcept
{
    return this->message.c_str();
}
