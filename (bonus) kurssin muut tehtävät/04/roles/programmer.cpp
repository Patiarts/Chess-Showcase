#include "programmer.hh"

Programmer::Programmer(int from_year):
    Role(from_year), skills_({})
{}

Programmer::~Programmer() {}

void Programmer::add_skill(const std::string &skill)
{
    skills_.insert(skill);
}

void Programmer::print(std::ostream &output) const
{
    if(skills_.empty()){
        output << "No skills" << std::endl;
        return;
    }

    std::string outputtingizer = "Skills: ";
    for (const std::string& skill : skills_){
        outputtingizer += skill + " ";
    }
    outputtingizer.resize(outputtingizer.size()-1);
    output << outputtingizer << std::endl;
}
