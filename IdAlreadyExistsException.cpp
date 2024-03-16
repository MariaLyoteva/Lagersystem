#include "IdAlreadyExistsException.h"

IdAlreadyExistsException::IdAlreadyExistsException(const std::string &message) : std::runtime_error(message) {}

