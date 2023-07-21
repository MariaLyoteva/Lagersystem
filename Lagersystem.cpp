#include "Lagersystem.h"

#include "FileHandler.h"

void Lagersystem::addCustomer(const Kunde & customer) {

    int customerId = customer.getKundenId();

    //Check for customerId duplications

    if (customers.find(customerId) != customers.end()) {
        throw IdAlreadyExistsException("Customer with ID " + std::to_string(customerId) + " already exists.");
    }

    customers.insert(std::make_pair(customer.getKundenId(), customer));
}

void Lagersystem::addProdukt(Produkt * produkt) {
    int productId = produkt -> getProduktId();

    //Check for productId duplications

    if (produktkatalog.find(productId) != produktkatalog.end()) {
        throw IdAlreadyExistsException("Produkt with ID " + std::to_string(productId) + " already exists.");
    }
    produktkatalog.insert(std::make_pair(productId, produkt));
}

void Lagersystem::addLagerbestand(int productId,
                                  const Lager & stockLevel) {
    // Check if the productId  exists in the produktkatalog map
    auto produktIter = produktkatalog.find(productId);
    if (produktIter == produktkatalog.end()) {
        throw std::runtime_error("Error: Produkt with ID " + std::to_string(productId) + " not found in produktkatalog.");
    }

    lagerbestand.insert(std::make_pair(productId, stockLevel));
}

void Lagersystem::printProduktkatalog() const {
    for (const auto & pair: produktkatalog) {
        std::cout << * (pair.second);
    }
    std::cout << std::endl;
}

void Lagersystem::printLagerbestand() const {
    for (const auto & pair: lagerbestand) {
        int produktId = pair.first;
        const Produkt * produkt = produktkatalog.at(produktId);
        const Lager & lager = pair.second;
        std::cout << "Lager " << produktId << " " << lager.getAnzahl() << std::endl;
    }
    std::cout << std::endl;
}

void Lagersystem::printKunde() const {
    for (const auto & pair: customers) {
        std::cout << pair.second.toString() << std::endl;
    }
    std::cout << std::endl;
}

std::string Lagersystem::getAllAsString() const {
    std::string result;

    // Append customers data to the result string
    for (const auto & pair: customers) {
        result += pair.second.toString() + "\n";
    }
    result += "\n";

    // Append produktkatalog data to the result string
    for (const auto & pair: produktkatalog) {
        Produkt * produkt = pair.second;
        int produktId = produkt -> getProduktId();
        std::string titel = produkt -> getTitel();

        // Replace spaces with underscores before export
        replaceSpacesWithUnderscores(titel);
        produkt -> setTitel(titel);

        result += produkt -> toString() + "\n";
    }
    result += "\n";

    // Append lagerbestand data to the result string
    for (const auto & pair: lagerbestand) {
        int produktId = pair.first;
        const Produkt * produkt = produktkatalog.at(produktId);
        auto lagerIter = lagerbestand.find(produktId);
        if (lagerIter != lagerbestand.end()) {
            const Lager & lager = lagerIter -> second;
            result += "Lager " + std::to_string(produktId) + " " + " " + std::to_string(lager.getAnzahl()) + "\n";
        }
    }

    return result;
}

void Lagersystem::replaceSpacesWithUnderscores(std::string & str) const {
    std::replace(str.begin(), str.end(), ' ', '_');
}
