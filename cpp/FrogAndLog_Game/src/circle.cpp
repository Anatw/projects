/*******************************************************************************
                                Shapes
                          Written by Anat Wax
                             June 7th-, 2020
                        Reviewer: Laura Bedah
*******************************************************************************/
#include <iostream> //cout
#include <sstream>
#include <string>

#include "circle.hpp"
#include "color.hpp"
#include "point.hpp"
#include "shape.hpp"

using namespace ilrd;

std::ostream& Circle::operator<<(std::ostream& os) const
{
    std::string radius_str;
    radius_str.append(to_string(m_radius));

    return (os << radius_str);
}

std::istream& Circle::operator>>(std::istream& is)
{
    std::string radius_str;
    is >> radius_str;

    int inner_radius = std::atoi(radius_str.c_str());

    this->SetRadius(inner_radius);

    return (is);
}

Circle::Circle(Point position_, double angle_, Color color_, int radius_)
    : Shape(position_, angle_, color_), m_radius(radius_)
{
}

void Circle::DrawInternal() const
{
    Point point = this->GetPosition();
    DrawCircle(this->GetColor(), point.GetX(), point.GetY(), this->m_radius);
}
