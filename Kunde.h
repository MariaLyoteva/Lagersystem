#pragma once

#include <string>

//the client class and all the methods
class Kunde {
private:
    int kundenId;
    std::string name;
    std::string vorname;
    std::string adresse;
    std::string hausnummer;
    std::string postleitzahl;
    std::string ort;

public:
    Kunde(int id, const std::string &name, const std::string &vorname, const std::string &adresse,
          const std::string &hausnummer, const std::string &postleitzahl, const std::string &ort)
            : kundenId(id), name(name), vorname(vorname), adresse(adresse),
              hausnummer(hausnummer), postleitzahl(postleitzahl), ort(ort) {}

    int getKundenId() const {
        return kundenId;
    }

    std::string getName() const {
        return name;
    }

    std::string getVorname() const {
        return vorname;
    }

    std::string getAdresse() const {
        return adresse;
    }

    std::string getHausnummer() const {
        return hausnummer;
    }

    std::string getPostleitzahl() const {
        return postleitzahl;
    }

    std::string getOrt() const {
        return ort;
    }

    std::string toString() const;
};


