#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<string>
#include<algorithm>


using namespace std;
//--------------------Products------------------//
class Produkt{
public:
    Produkt(int id, const string& titel)
            :produktId(id), titel(titel){}

    int getProduktId(){
        return produktId;
    }

    string getTitel() const {
        return titel;
    }

    virtual string toString() const = 0;

    friend ostream& operator<<(ostream& os, const Produkt& produkt);


protected:
    int produktId;
    string titel;
};

ostream& operator<<(ostream& os, const Produkt& produkt) {
    os << produkt.toString()<< endl;
    return os;
}

class DVD: public Produkt{
public:
    DVD(int id,  const string& titel, int laufzeit)
            : Produkt(id, titel), laufzeit(laufzeit) {}

    int getLaufzeit(){
        return laufzeit;
     }

    string toString() const override {
        return "DVD " + to_string(produktId) + " " + titel + " " + to_string(laufzeit);
    }

private:
    int laufzeit;

};

class Bluray: public Produkt{
public:
    Bluray(int id, const string& titel, int anzahlTracks, const string& aufloesung)
            : Produkt(id, titel), anzahlTracks(anzahlTracks), aufloesung(aufloesung) {}

    int getAnzahlTracks() const {
        return anzahlTracks;
    }

    string getAufloesung() const {
        return aufloesung;
    }

    string toString() const override {
        return "Bluray " + to_string(produktId) + " " + titel + " " + to_string(anzahlTracks) + " " + aufloesung;
    }

private:
    int anzahlTracks;
    string aufloesung;
};

//---------------end of products-----------------------//


//Kunde class//

class Kunde {
private:
    int kundenId;
    string name;
    string vorname;
    string adresse;
    string hausnummer;
    string postleitzahl;
    string ort;

public:
    Kunde(int id, const string& name, const string& vorname, const string& adresse,
          const string& hausnummer, const string& postleitzahl, const string& ort)
            : kundenId(id), name(name), vorname(vorname), adresse(adresse),
              hausnummer(hausnummer), postleitzahl(postleitzahl), ort(ort) {}

    int getKundenId() const  {
        return kundenId;
    }

    string getName() const {
        return name;
    }

    string getVorname() const {
        return vorname;
    }

    string getAdresse() const {
        return adresse;
    }

    string getHausnummer() const {
        return hausnummer;
    }

    string getPostleitzahl() const {
        return postleitzahl;
    }

    string getOrt() const {
        return ort;
    }

    string toString() const {
        return "Kunde " + to_string(kundenId) + " " + name + " " + vorname + " " +
               adresse + " " + hausnummer + " " + postleitzahl + " " + ort;
    }
};

//Storage classes//
class Lager {
public:
    Lager(int anzahl) : anzahl(anzahl) {}

    int getAnzahl() const {
        return anzahl;
    }

private:
    int anzahl;
};



class Lagersystem {
public:
    std::map<int, Kunde> customers;              // Map customerID to Kunde
    std::map<int, Produkt*> produktkatalog;     // Map productID to Produkte*
    std::map<int, Lager> lagerbestand;       // Map productID to StockLevel

    void addCustomer(const Kunde& customer) {
        customers.insert(std::make_pair(customer.getKundenId(), customer));
    }

    void addProdukt(Produkt* produkt) {
        int productId = produkt->getProduktId();
        if (produktkatalog.find(productId) != produktkatalog.end()) {
            throw runtime_error("Produkt with ID " + to_string(productId) + " already exists.");
        }
        produktkatalog.insert(std::make_pair(productId, produkt));
    }

    void addLagerbestand(int productId, const Lager& stockLevel) {
        lagerbestand.insert(std::make_pair(productId, stockLevel));
    }


    void printProduktkatalog() const {
        for (const auto& pair : produktkatalog) {
            cout << *(pair.second) << endl;
        }
    }

    void printKunde() const {
        for (const auto& pair : customers) {
            cout << pair.second.toString() << endl;
        }
    }
};


class FileHandler {
private:
    Lagersystem& lagersystem;

public:
    FileHandler(Lagersystem& lagersystem) : lagersystem(lagersystem) {}

    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Fehler beim Öffnen der Datei." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty())
                continue;

            istringstream iss(line);
            string category;
            iss >> category;

            try {
                if (category == "Kunde") {
                    int kundenId;
                    string name, vorname, adresse, hausnummer, postleitzahl, ort;
                    iss >> kundenId >> name >> vorname >> adresse >> hausnummer >> postleitzahl >> ort;
                    lagersystem.addCustomer(Kunde(kundenId, name, vorname, adresse, hausnummer, postleitzahl, ort));
                } else if (category == "DVD") {
                    int produktId, laufzeit;
                    string titel;
                    iss >> produktId >> titel >> laufzeit;
                    replace(titel.begin(), titel.end(), '_', ' ');  // Ersetze Unterstriche durch Leerzeichen
                    lagersystem.addProdukt(new DVD(produktId, titel, laufzeit));
                } else if (category == "Bluray") {
                    int produktId, anzahlTracks;
                    string titel, aufloesung;
                    iss >> produktId >> titel >> anzahlTracks >> aufloesung;
                    replace(titel.begin(), titel.end(), '_', ' ');  // Ersetze Unterstriche durch Leerzeichen
                    lagersystem.addProdukt(new Bluray(produktId, titel, anzahlTracks, aufloesung));
                } else if (category == "Lager") {
                    int produktId, anzahl;
                    iss >> produktId >> anzahl;
                    lagersystem.addLagerbestand(produktId, Lager(anzahl));
                } else {
                    throw runtime_error("Ungültige Kategorie: " + category);
                }
            } catch (const exception& e) {
                cerr << "Fehler beim Verarbeiten der Zeile: " << line << endl;
                cerr << e.what() << endl;
            }
        }

        file.close();
    }
    void replaceSpacesWithUnderscores(string& str) const {
        std::replace(str.begin(), str.end(), ' ', '_');
    }

    void exportToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cerr << "Fehler beim Öffnen der Datei zum Exportieren." << endl;
            return;
        }

        for (const auto& pair : lagersystem.customers) {
            file << pair.second.toString() << endl;
        }

        for (const auto& pair : lagersystem.produktkatalog) {
            Produkt* produkt = pair.second;
            int produktId = produkt->getProduktId();
            string titel = produkt->getTitel();

            // Replace spaces with underscores before export
            replaceSpacesWithUnderscores(titel);
            file << *(pair.second) << endl;

            // Check if the key exists in lagerbestand map
            auto lagerIter = lagersystem.lagerbestand.find(produktId);
            if (lagerIter != lagersystem.lagerbestand.end()) {
                const Lager& lager = lagerIter->second;
                file << "Lager " << produktId << " " << titel << " " << lager.getAnzahl() << endl;
            } else {
                // Handle the case when Lager data is missing for a product
                file << "Lager " << produktId << " " << titel << " 0" << endl; // Assuming default value is 0
            }
        }

        file.close();
    }

};

int main() {
    Lagersystem lagersystem;
    FileHandler fileHandler(lagersystem);

    fileHandler.readFromFile("C:\\Users\\maria\\CLionProjects\\untitled2\\acme.load");

   // lagersystem.printKunde();
    lagersystem.printProduktkatalog();
    //lagersystem.printLagerbestand();

    fileHandler.exportToFile("C:\\Users\\maria\\CLionProjects\\untitled2\\export.txt");

    return 0;
}
