#pragma once

#include <iostream>
#include <string>

//Product as parent class
class Produkt {
public:
    Produkt(int id, const std::string &titel)
            : produktId(id), titel(titel) {}

    int getProduktId() const {
        return produktId;
    }

    std::string getTitel() const {
        return titel;
    }

    void setTitel(const std::string &newTitel) {
        titel = newTitel;
    }

    virtual std::string toString() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Produkt &produkt);

protected:
    int produktId;
    std::string titel;
};

std::ostream &operator<<(std::ostream &os, const Produkt &produkt);

