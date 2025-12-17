#include "person.hh"


Person::Person(const std::string &name, int age):
    name_(name), age_(age)
{
    std::cout << "Person created: " << name_ << std::endl;
}

Person::~Person()
{
    std::cout << "Person destructed: " << name_ << std::endl;
}

std::string Person::get_name() const
{
    return name_;
}

void Person::celebrate_birthday(int next_age)
{
    age_ = next_age;
}

void Person::print(std::ostream &output) const
{
    output << name_ << " : " << age_ << std::endl;
}
