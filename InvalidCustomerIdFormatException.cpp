#include"InvalidCustomerIdFormatException.h"

InvalidCustomerIdFormatException::InvalidCustomerIdFormatException(const std::string &message) : std::runtime_error(
        message) {}
