#include "cockatoo.hh"

Cockatoo::Cockatoo() {}

Cockatoo::~Cockatoo() {}

void Cockatoo::sing(std::ostream &output)
{
    output << "Kee-ow kee-ow!" << std::endl;
}

