/*******************************************************************************
                                Shapes
                          Written by Anat Wax
						     June 7th-, 2020
						Reviewer: Laura Bedah
*******************************************************************************/
#include <iostream> //cout

#include "circle.hpp"
#include "shape.hpp"
#include "color.hpp"
#include "point.hpp"

using namespace ilrd;

Circle::Circle(Point position_, double angle_, Color color_, int radius_)
    : Shape(position_, angle_, color_), m_radius(radius_)
{
}

void Circle::DrawInternal() const
{
    Point point = this->GetPosition();
    this->

        DrawCircle(this->GetColor(), point.GetX(), point.GetY(), this->m_radius);
}
