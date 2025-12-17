#ifndef CIRCLE_HH
#define CIRCLE_HH

#include "shape.hh"

const double PI = 3.14159;

class Circle : public Shape
{
public:
    Circle(char color, double radius);
    virtual ~Circle();

    virtual double area() const;
    virtual double circumference() const;
    virtual void print(int running_number) const;
private:
    double radius_;
};

#endif // CIRCLE_HH
