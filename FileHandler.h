#ifndef FILEHANDLER_H
#define FILEHANDLER_H

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
private: Lagersystem & lagersystem;
    std::vector < std::string > errorMessages; //a vector that contains all the error messages, so they can be exported at he end in the console
public: FileHandler(Lagersystem & lagersystem);
    void readFromFile(const std::string & filename);
    void exportToFile(const std::string & filename) const;
    void replaceUnderscoresWithSpaces(std::string & str) const;
    void printErrorMessages() const; //prints all the error messages
};

#endif // FILEHANDLER_H
