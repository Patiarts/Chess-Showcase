#ifndef PLAYER_HH
#define PLAYER_HH

#include "role.hh"

class Player : public Role
{
public:
    Player(int from_year);
    virtual ~Player();

    void add_instrument(const std::string& instrument);
    void print(std::ostream& output) const;
private:
    std::string instrument_;
};

#endif // PLAYER_HH
