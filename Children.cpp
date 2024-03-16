#include"Children.h"


DVD::DVD(int id,  const std::string& titel, int laufzeit)
        : Produkt(id, titel), laufzeit(laufzeit) {}

int DVD::getLaufzeit(){
    return laufzeit;
}

std::string DVD::toString() const {
    return "DVD " + std::to_string(produktId) + " " + titel + " " + std::to_string(laufzeit);
}

Bluray::Bluray(int id, const std::string& titel, int anzahlTracks, const std::string& aufloesung)
        : Produkt(id, titel), anzahlTracks(anzahlTracks), aufloesung(aufloesung) {}

int Bluray::getAnzahlTracks() const {
    return anzahlTracks;
}

std::string Bluray::getAufloesung() const {
    return aufloesung;
}

std::string Bluray::toString() const{
    return "Bluray " + std::to_string(produktId) + " " + titel + " " + std::to_string(anzahlTracks) + " " + aufloesung;
}
