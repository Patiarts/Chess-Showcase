#include "mammal.hh"

Mammal::Mammal(): Animal("Kip kop kip kop") {}

Mammal::~Mammal(){}

void Mammal::suckle(std::ostream &output)
{
    output << "Mus mus" << std::endl;
}
