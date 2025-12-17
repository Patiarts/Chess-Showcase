#include "student.hh"

Student::Student(const std::string &name, int age, const std::string student_num):
    Person(name, age), student_num_(student_num)
{
    std::cout << "Student created: " << get_name() << std::endl;
}

Student::~Student()
{
    std::cout << "Student destructed: " << get_name() << std::endl;
}

void Student::complete_course(const std::string &course)
{
    completed_courses_.push_back(course);
}

void Student::print(std::ostream &output) const
{
    Person::print(output);
    output << "+++ " << student_num_ << ": ";


    if(completed_courses_.empty()){
        output << "No courses completed" << std::endl;
        return;
    }

    for(size_t i = 0; i < completed_courses_.size() -1; i++){
        output << completed_courses_[i] << ", ";
    }
    output << completed_courses_.back() << std::endl;
}
