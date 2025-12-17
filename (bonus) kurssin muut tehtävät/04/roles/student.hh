#ifndef STUDENT_HH
#define STUDENT_HH

#include "role.hh"

class Student : public Role
{
public:
    Student(int from_year, int student_number);
    virtual ~Student();

    void print(std::ostream& output) const;
private:
    int student_number_;
};

#endif // STUDENT_HH
