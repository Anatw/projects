#include "shape.hpp"
#include "color.hpp"
#include "glut_utils.h"
#include "point.hpp"

using namespace ilrd;
Shape::Shape() : position_m(Point(500, 500)), angle_m(0), color_m(Color())
{
}

Shape::Shape(Point point_, double angle_, Color color_)
{
    this->position_m = point_;
    this->angle_m = angle_;
    this->color_m = color_;
}

void Shape::Draw() const
{
    DrawInternal();
}

// Please input angles in degrees.
void Shape::Rotate_m(const double delta_angle)
{
    this->angle_m += delta_angle;
}

void Shape::Revolve_m(const Point &c_point, double angle)
{
    angle = angle * M_PI / 180;
    this->position_m.Revolve(c_point, angle);
}

void Shape::Move_m(const Point &vector)
{
    this->position_m += vector;
}
