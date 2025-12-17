#ifndef STUDENT_HH
#define STUDENT_HH

#include "person.hh"
#include <vector>

class Student : public Person
{
public:
    Student(const std::string& name,int age, const std::string student_num);
    virtual ~Student();

    void complete_course(const std::string& course);
    void print(std::ostream& output) const;
private:
    std::string student_num_;
    std::vector<std::string> completed_courses_;
};

#endif // STUDENT_HH
