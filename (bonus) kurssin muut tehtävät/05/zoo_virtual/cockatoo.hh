#ifndef COCKATOO_HH
#define COCKATOO_HH

#include "bird.hh"

class Cockatoo : public Bird
{
public:
    Cockatoo();
    virtual ~Cockatoo();

    virtual void vocalize(std::ostream& output) const;

};

#endif // COCKATOO_HH
