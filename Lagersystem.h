
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include "Kunde.h"
#include "Produkt.h"
#include "Lager.h"
#include"IdAlreadyExistsException.h"
#include"IdNotFoundLager.h"

#pragma once

class Lagersystem {
public:
    void addCustomer(const std::shared_ptr<Kunde> &customer); //adds customers to the map
    void addProdukt(const std::shared_ptr<Produkt> &produkt); //adds product to the catalog
    void addLagerbestand(int productId, const Lager &stockLevel); //adds the "stock levels"

    void printProduktkatalog() const; //prints the catalog
    void printLagerbestand() const;  //prints the "stock levels"
    void printKunde() const; //prints the clients

    std::string getAllAsString() const;

    void replaceSpacesWithUnderscores(std::string &str) const;

private:
    std::map<int, std::shared_ptr<Kunde>> customers; //A map that stores the customers'id as key and a shared_ptr<Kunde> as value
    std::map<int, std::shared_ptr<Produkt>> produktkatalog; //A map that stores the product_id as key and a shared_ptr<Produkt> as value
    std::map<int, Lager> lagerbestand; // A map that stores the product_id as key and object from the class Lager as value
};
