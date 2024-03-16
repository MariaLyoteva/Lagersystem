#include "InvalidCustomerFormatException.h"

InvalidCustomerFormatException::InvalidCustomerFormatException(const std::string &message) : std::runtime_error(
        message) {}
