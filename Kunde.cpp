#include "Kunde.h"


std::string Kunde::toString() const {
    return "Kunde " + std::to_string(kundenId) + " " + name + " " + vorname + " " +
           adresse + " " + hausnummer + " " + postleitzahl + " " + ort;
}
