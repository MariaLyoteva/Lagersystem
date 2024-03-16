#include<stdexcept>
#include<string>

#pragma once

class IdAlreadyExistsException : public std::runtime_error {
public:
    IdAlreadyExistsException(const std::string &message);
};

