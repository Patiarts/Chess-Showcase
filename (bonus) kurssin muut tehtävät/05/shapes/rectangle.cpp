#include "rectangle.hh"
#include <iostream>

Rectangle::Rectangle(char color, double width, double height):
    Shape(color), width_(width), height_(height)
{}

Rectangle::~Rectangle() {}

double Rectangle::area() const
{
    return width_ * height_;
}

double Rectangle::circumference() const
{
    return 2*(width_ + height_);
}

void Rectangle::print(int running_number) const
{
    Shape::print(running_number);

    std::string incredibly_beautifully_colorful = COLOR_NAMES.at(get_color());

    std::cout << incredibly_beautifully_colorful << " rectangle with width " << width_ << " and height " << height_ << std::endl
              << "Area: " << area() << std::endl
              << "Circumference: " << circumference() << std::endl;
}
