#include "elephant.hh"

Elephant::Elephant() {}

Elephant::~Elephant() {}

void Elephant::vocalize(std::ostream &output) const
{
    output << "Baraag baraag!" << std::endl;
}
