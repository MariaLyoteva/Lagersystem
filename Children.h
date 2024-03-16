#include"Produkt.h"
//Conatins the children of the Produkt class - DVD and Bluray
#pragma once

class DVD : public Produkt {
public:
    DVD(int id,
        const std::string &titel, int laufzeit);

    int getLaufzeit();

    std::string toString() const override;

private:
    int laufzeit;

};

class Bluray : public Produkt {
public:
    Bluray(int id, const std::string &titel, int anzahlTracks, const std::string &aufloesung);

    int getAnzahlTracks() const;

    std::string getAufloesung() const;

    std::string toString() const override;

private:
    int anzahlTracks;
    std::string aufloesung;
};





