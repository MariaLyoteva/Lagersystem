#pragma once

#include "Lagersystem.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include<algorithm>
#include<limits>
#include "IdAlreadyExistsException.h"

#include"InvalidCustomerIdFormatException.h"

#include"Children.h"

#include"InvalidCustomerFormatException.h"


class FileHandler {
public:
    FileHandler(std::shared_ptr<Lagersystem> lagersystem);

    // Reads the input from the file
    void readFromFile(const std::string &filename);

    // Exports data to a file
    void exportToFile(const std::string &filename) const;

    // Prints any error messages
    void printErrorMessages() const;

private:
    std::shared_ptr<Lagersystem> lagersystem;
    std::vector<std::string> errorMessages;

    void replaceUnderscoresWithSpaces(std::string &str) const;
};


