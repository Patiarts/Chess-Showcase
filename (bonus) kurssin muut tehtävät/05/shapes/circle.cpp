#include "circle.hh"
#include <iostream>

Circle::Circle(char color, double radius):
    Shape(color), radius_(radius)
{}

Circle::~Circle()
{}

double Circle::area() const
{
    return PI * radius_ * radius_;
}

double Circle::circumference() const
{
    return 2 * PI * radius_;
}

void Circle::print(int running_number) const
{
    Shape::print(running_number);

    std::string colllore = COLOR_NAMES.at(get_color());

    std::cout << colllore << " circle with radius " << radius_ << std::endl
              << "Area: " << area() << std::endl
              << "Circumference: " << circumference() << std::endl;
}
