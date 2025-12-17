#ifndef PROGRAMMER_HH
#define PROGRAMMER_HH

#include "role.hh"
#include <set>

class Programmer : public Role
{
public:
    Programmer(int from_year);
    virtual ~Programmer();

    void add_skill(const std::string& skill);
    void print(std::ostream& output) const;
private:
    std::set<std::string> skills_;
};

#endif // PROGRAMMER_HH
