/*******************************************************************************
                                Shapes
                          Written by Anat Wax
						     June 7th-, 2020
						Reviewer: Laura Bedah
*******************************************************************************/
#include "rectangle.hpp"
#include "glut_utils.h"
#include "shape.hpp"
#include "color.hpp"

using namespace ilrd;

Rectangle::Rectangle() : m_width(100), m_length(100)
{
}

Rectangle::Rectangle(Point position_, double angle_, Color color_, int width_,
                     int length_)
    : Shape(position_, angle_, color_), m_width(width_), m_length(length_)
{
}

void Rectangle::DrawInternal() const
{
    int length_half = this->m_length / 2;
    int width_half = this->m_width / 2;

    Point center = this->GetPosition(); // x, y
    double angle = this->GetAngle() * M_PI / 180;

    int left_top_x = (int)center.GetX() - length_half;
    int left_top_y = (int)center.GetY() + width_half;
    Point left_top(left_top_x, left_top_y);
    left_top.Revolve(center, angle);

    int right_top_x = (int)center.GetX() + length_half;
    int right_top_y = (int)center.GetY() + width_half;
    Point right_top(right_top_x, right_top_y);
    right_top.Revolve(center, angle);

    int right_bottom_x = (int)center.GetX() + length_half;
    int right_bottom_y = (int)center.GetY() - width_half;
    Point right_bottom(right_bottom_x, right_bottom_y);
    right_bottom.Revolve(center, angle);

    int left_bottom_x = (int)center.GetX() - length_half;
    int left_bottom_y = (int)center.GetY() - width_half;
    Point left_bottom(left_bottom_x, left_bottom_y);
    left_bottom.Revolve(center, angle);

    DrawPolygon(this->GetColor(), 4,
                (int)left_top.GetX(), (int)left_top.GetY(),
                (int)right_top.GetX(), (int)right_top.GetY(),
                (int)right_bottom.GetX(), (int)right_bottom.GetY(),
                (int)left_bottom.GetX(), (int)left_bottom.GetY());
}
