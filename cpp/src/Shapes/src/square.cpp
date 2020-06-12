/*******************************************************************************
                                Shapes
                          Written by Anat Wax
						     June 7th-, 2020
						Reviewer: Laura Bedah
*******************************************************************************/
#include "square.hpp"
#include "glut_utils.h"

using namespace ilrd;

Square::Square(Point position_, double angle_, Color color_, int edge_)
    : Shape(position_, angle_, color_), m_edge(edge_)
{
}

void Square::DrawInternal() const
{
    int half = m_edge / 2;
    Point center = this->GetPosition(); // x, y

    int left_top_x = (int)center.GetX() - half;
    int left_buttom_x = (int)center.GetX() - half;
    int right_top_x = (int)center.GetX() + half;
    int right_buttom_x = (int)center.GetX() + half;

    int left_top_y = (int)center.GetY() + half;
    int left_buttom_y = (int)center.GetY() - half;
    int right_top_y = (int)center.GetY() + half;
    int right_buttom_y = (int)center.GetY() - half;

    // center.SetX(center.GetX() + (this->m_edge / 2));
    // center.SetY(center.GetY() + (this->m_edge / 2));

    Point left_top(left_top_x, left_top_y);
    left_top.Revolve(center, this->GetAngle() * M_PI / 180);

    Point left_buttom(left_buttom_x, left_buttom_y);
    left_buttom.Revolve(center, this->GetAngle() * M_PI / 180);

    Point right_top(right_top_x, right_top_y);
    right_top.Revolve(center, this->GetAngle() * M_PI / 180);

    Point right_buttom(right_buttom_x, right_buttom_y);
    right_buttom.Revolve(center, this->GetAngle() * M_PI / 180);

    DrawPolygon(this->GetColor(), 4,
                (int)left_top.GetX(), (int)left_top.GetY(),
                (int)right_top.GetX(), (int)right_top.GetY(),
                (int)right_buttom.GetX(), (int)right_buttom.GetY(),
                (int)left_buttom.GetX(), (int)left_buttom.GetY());
}
