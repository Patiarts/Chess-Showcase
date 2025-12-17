#include "shape.hh"
#include <iostream>

Shape::Shape(char color)
{
    paint(color);
}

Shape::~Shape()
{

}

void Shape::paint(char color)
{
    if(COLOR_CODES.find(color) == COLOR_CODES.end())
    {
        std::cout << "Wrong color" << std::endl;
    }
    for(auto color_code : COLOR_CODES)
    {
        if(color_code.first == color)
        {
            color_ = color_code.second;
        }
    }
}

Color Shape::get_color() const
{
    return color_;
}

void Shape::print(int running_number) const
{
    std::cout << "Shape " << running_number << ":" << std::endl;
}


