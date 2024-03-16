
#include"Lagersystem.h"

#include"FileHandler.h"


int main() {
    std::shared_ptr<Lagersystem> lagersystem = std::make_shared<Lagersystem>();
    FileHandler fileHandler(lagersystem);
    fileHandler.readFromFile("acme.load");
    lagersystem->printKunde();
    lagersystem->printProduktkatalog();
    lagersystem->printLagerbestand();
    fileHandler.exportToFile("export.txt");
    fileHandler.printErrorMessages();
    return 0;
}
