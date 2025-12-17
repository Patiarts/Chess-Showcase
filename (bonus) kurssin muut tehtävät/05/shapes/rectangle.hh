#ifndef RECTANGLE_HH
#define RECTANGLE_HH

#include "shape.hh"

class Rectangle : public Shape
{
public:
    Rectangle(char color, double width, double height);
    virtual ~Rectangle();

    virtual double area() const;
    virtual double circumference() const;
    virtual void print(int running_number) const;

private:
    double width_;
    double height_;
};

#endif // RECTANGLE_HH
