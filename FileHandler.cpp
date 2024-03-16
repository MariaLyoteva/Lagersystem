#include "FileHandler.h"


#include "FileHandler.h"
#include <fstream>
#include <sstream>

FileHandler::FileHandler(std::shared_ptr<Lagersystem> lagersystem)
        : lagersystem(lagersystem) {}

void FileHandler::readFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Fehler beim Öffnen der Datei." << std::endl;
        return;
    }

    std::string line;
    int lineNum = 1; // Keeps track of the line number (for error reporting)
    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::istringstream iss(line);
        std::string category;
        iss >> category;

        try {
            if (category == "Kunde") {
                int kundenId;
                std::string name, vorname, adresse, hausnummer, postleitzahl, ort;
                iss >> kundenId >> name >> vorname >> adresse >> hausnummer >> postleitzahl >> ort;
                //Check if the customer format is valid
                if (!iss || iss.fail()) {
                    throw InvalidCustomerFormatException("Invalid customer format at line " + std::to_string(lineNum));
                }
                //Check if the customerId is valid
                if (kundenId < 0 || kundenId > std::numeric_limits<int>::max()) {
                    throw InvalidCustomerIdFormatException(
                            "Invalid customer ID format at line " + std::to_string(lineNum));
                }
                lagersystem->addCustomer(
                        std::make_shared<Kunde>(kundenId, name, vorname, adresse, hausnummer, postleitzahl, ort));
            } else if (category == "DVD") {
                int produktId, laufzeit;
                std::string titel;
                iss >> produktId >> titel >> laufzeit;
                replaceUnderscoresWithSpaces(titel); // replaces the _ with an empty space
                lagersystem->addProdukt(std::make_shared<DVD>(produktId, titel, laufzeit));
            } else if (category == "Bluray") {
                int produktId, anzahlTracks;
                std::string titel, aufloesung;
                iss >> produktId >> titel >> anzahlTracks >> aufloesung;
                replaceUnderscoresWithSpaces(titel); // replaces the _ with an empty space
                lagersystem->addProdukt(std::make_shared<Bluray>(produktId, titel, anzahlTracks, aufloesung));
            } else if (category == "Lager") {
                int produktId, anzahl;
                iss >> produktId >> anzahl;
                lagersystem->addLagerbestand(produktId, Lager(anzahl));
            } else {
                throw std::runtime_error("Ungültige Kategorie: " + category);
            }
        } catch (const IdAlreadyExistsException &e) {
            errorMessages.push_back("Fehler beim Verarbeiten der Zeile " + std::to_string(lineNum) + ": " + e.what());
        } catch (const InvalidCustomerIdFormatException &e) {
            errorMessages.push_back("Fehler beim Verarbeiten der Zeile " + std::to_string(lineNum) + ": " + e.what());
        } catch (const InvalidCustomerFormatException &e) {
            errorMessages.push_back("Fehler beim Verarbeiten der Zeile " + std::to_string(lineNum) + ": " + e.what());
        } catch (const std::exception &e) {
            errorMessages.push_back("Fehler beim Verarbeiten der Zeile " + std::to_string(lineNum) + ": " + line);
            errorMessages.push_back(e.what());
        }

        lineNum++; // Moves to the next line
    }

    file.close();
}

void FileHandler::exportToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Fehler beim Öffnen der Datei zum Exportieren." << std::endl;
        return;
    }

    std::string allData = lagersystem->getAllAsString();
    file << allData;

    file.close();
}

void FileHandler::replaceUnderscoresWithSpaces(std::string &str) const {
    replace(str.begin(), str.end(), '_', ' ');
}

void FileHandler::printErrorMessages() const {
    // Prints all the error messages at the end
    for (const std::string &errorMessage: errorMessages) {
        std::cerr << errorMessage << std::endl;
    }
}

