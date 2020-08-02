/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "circle.hpp"
#include "color.hpp"
#include "factory.hpp"
#include "glut_utils.h"
#include "line.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "square.hpp"

using namespace std;
using namespace ilrd;

struct Params
{
    Point position_;
    double angle_;
    Color color_;
    int width_;
    int length_;
    int radius_;
    int edge_;
    int length_;
};

Shape* DrawCircle(Params params)
{
    Shape* circle = new Circle(params.position_, params.angle_, params.color_,
                               params.radius_);
    return (circle);
}

Shape* DrawRectangle(Params params)
{
    Shape* rectangle =
        new Rectangle(params.position_, params.angle_, params.color_,
                      params.width_, params.length_);
    return (rectangle);
}

Shape* DrawSquare(Params params)
{
    Shape* square = new Square(params.position_, params.angle_, params.color_,
                               params.edge_);
    return (square);
}

Shape* DrawLine(Params params)
{
    return (new Line(params.position_, params.angle_, params.color_,
                     params.length_))
}

int main()
{
    // Params circle_parameters;
    // Params params_p;
    // circle_parameters.position_ = Point(0, 0);
    // circle_parameters.angle_ = 27;
    // circle_parameters.color_ = Color();
    // circle_parameters.radius_ = 100;

    // Params rectangle_parameters;
    // rectangle_parameters.position_ = Point(400, 400);
    // rectangle_parameters.angle_ = 28;
    // rectangle_parameters.color_ = Color();
    // rectangle_parameters.width_ = 68;
    // rectangle_parameters.length_ = 87;

    shape_params(Point(400, 400), 27, Color(), 27, 28, 68, 87, 100);

    Factory< string, Shape, Params > shape_factory;
    shape_factory.Add("circle", DrawCircle);

    Shape* circle = shape_factory.Create("circle", shape_params);

    return (0);
}
