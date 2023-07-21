#include"Produkt.h"
#include"Kunde.h"
#include "Lager.h"
#include <map>
#include"IdAlreadyExistsException.h"
#include"IdNotFoundLager.h"


#ifndef LAGERSYSTEM_H
#define LAGERSYSTEM_H
//a class that represents the sytem
class Lagersystem {
public:
    std::map < int,Kunde > customers; // Map customerID to Kunde
    std::map < int,Produkt * > produktkatalog; // Map productID to Produkt*
    std::map < int,Lager > lagerbestand; // Map productID to Lager

    void addCustomer(const Kunde & customer); //adds customer to the map
    void addProdukt(Produkt * produkt); //adds product to the map
    void addLagerbestand(int productId,
                         const Lager & stockLevel); //adds a "stocklevel" to the map
    void printProduktkatalog() const; //prints the catalog
    void printLagerbestand() const; //prints the storage status
    void printKunde() const; //prints the clients
    std::string getAllAsString() const; // a function that turns everything into one big string. It's used in the exportFile function (FileHandlder.h)
    void replaceSpacesWithUnderscores(std::string & str) const; // thid function replaces back the spaces with underscores

};

#endif
