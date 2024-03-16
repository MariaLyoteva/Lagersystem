#include <stdexcept>
#include<string>

#pragma once

//This exception is for validating the customer format
class InvalidCustomerFormatException : public std::runtime_error {
public:
    InvalidCustomerFormatException(const std::string &message);
};


