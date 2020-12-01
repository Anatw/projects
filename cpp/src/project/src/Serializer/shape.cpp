/*******************************************************************************
                                Shapes
                          Written by Anat Wax
                             June 7th-, 2020
                        Reviewer: Laura Bedah
*******************************************************************************/
#include <cmath> // M_PI

#include "glut_utils.h"
#include "shape.hpp"

using namespace ilrd;

std::ostream& Shape::operator<<(std::ostream& os) const
{
    std::string params;
    // boost::lexical_cast converts numbers from strings to numeric types like
    // int or double and vice versa.
    params.append(boost::lexical_cast< std::string >(position_m.GetX()));
    params.push_back(' ');
    params.append(boost::lexical_cast< std::string >(position_m.GetY()));
    params.push_back(' ');

    params.append(boost::lexical_cast< std::string >(angle_m));
    params.push_back(' ');

    params.append(boost::lexical_cast< std::string >(color_m.GetR()));
    params.push_back(' ');
    params.append(boost::lexical_cast< std::string >(color_m.GetG()));
    params.push_back(' ');
    params.append(boost::lexical_cast< std::string >(color_m.GetB()));
    params.push_back(' ');

    os << params;

    return os;
}

std::istream& Shape::operator>>(std::istream& is)
{
    std::string str_xpoint;
    is >> str_xpoint;
    std::string str_ypoint;
    is >> str_ypoint;
    SetPosition(Point(atof(str_xpoint.c_str()), atof(str_ypoint.c_str())));
    // this->position_m.Move(atof(str_xpoint.c_str()),
    // atof(str_ypoint.c_str()));

    std::string str_angle;
    is >> str_angle;
    this->SetAngle(atof(str_angle.c_str()));

    std::string str_colorR;
    is >> str_colorR;
    std::string str_colorG;
    is >> str_colorG;
    std::string str_colorB;
    is >> str_colorB;
    Color color;
    color.SetR(atoi(str_colorR.c_str()));
    color.SetG(atoi(str_colorG.c_str()));
    color.SetB(atoi(str_colorB.c_str()));

    return is;
}

Shape::Shape() : position_m(Point(400, 400)), angle_m(0), color_m(Color())
{
}

Shape::Shape(Point point_, double angle_, Color color_)
    : position_m(point_), angle_m(angle_), color_m(color_)
{
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

void Shape::Revolve_m(const Point& c_point, double angle)
{
    angle = angle * M_PI / 180;
    this->position_m.Revolve(c_point, angle);
}

void Shape::Move_m(const Point& vector)
{
    this->position_m += vector;
}
