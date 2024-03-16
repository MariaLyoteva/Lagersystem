#include<stdexcept>
#include<string>

#pragma once

//this exception is for validating the customer's id format (using an id that exceeds the int limit is not allowed)
class InvalidCustomerIdFormatException : public std::runtime_error {
public:
    InvalidCustomerIdFormatException(const std::string &message);
};


