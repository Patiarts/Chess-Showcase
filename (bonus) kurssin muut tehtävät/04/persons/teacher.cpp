#include "teacher.hh"


Teacher::Teacher(const std::string &name, int age, const std::string &office_num):
    Person(name, age), office_num_(office_num)
{
    std::cout << "Teacher created: " << get_name() << std::endl;
}

Teacher::~Teacher()
{
    std::cout << "Teacher destructed: " << get_name() << std::endl;
}

void Teacher::change_room(const std::string &new_room)
{
    office_num_ = new_room;
}

void Teacher::add_new_course(const std::string &course)
{
    courses_.insert(course);
}

void Teacher::remove_course(const std::string &course)
{
    courses_.erase(course);
}

void Teacher::print(std::ostream &output) const
{
    Person::print(output);
    output << "*** " << office_num_ << ": ";

    if(courses_.empty()){
        output << "No responsibilities" << std::endl;
        return;
    }

    std::string outputterer = "";
    for(const std::string& course : courses_){
        outputterer += course + ", ";
    }
    outputterer.resize(outputterer.size()-2);
    output << outputterer << std::endl;
}
