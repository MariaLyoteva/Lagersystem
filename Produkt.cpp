#include "Produkt.h"

//redefining the << operator
std::ostream & operator << (std::ostream & os,const Produkt & produkt) {
    os << produkt.toString() << std::endl;
    return os;
}
