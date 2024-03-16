#include<stdexcept>
#include<string>

#pragma once

//This exception cacthes the case where there is a Lager with valid input, but there is no product with such Id in the catalog
class IdNotFoundLager : public std::runtime_error {
public:
    IdNotFoundLager(const std::string &message);
};

