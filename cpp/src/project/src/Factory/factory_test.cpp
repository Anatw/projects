/*******************************************************************************
Factory (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 2.8.20
Reviewer: Shmuel Sinder
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
#include "singleton.hpp"
#include "square.hpp"

using namespace std;
using namespace ilrd;

Shape* circle = NULL;
Shape* rectangle = NULL;
Shape* square = NULL;
Shape* line = NULL;

struct Params
{
    Point position_;
    double angle_;
    Color color_;
    int width_;
    int length_;
    int radius_;
    int edge_;
};

typedef Singleton< Factory< string, Shape, Params > > ShapeFactory;

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
                     params.length_));
}

static void DrawShapes()
{
    circle->Draw();
    rectangle->Draw();
    line->Draw();
    square->Draw();
}

int main(int argc, char** argv)
{
    Params shape_params;
    shape_params.position_ = Point(400, 400);
    shape_params.angle_ = 28;
    shape_params.color_ = Color();
    shape_params.width_ = 68;
    shape_params.length_ = 87;
    shape_params.radius_ = 100;
    shape_params.edge_ = 95;

    // Factory< string, Shape, Params > shape_factory;

    ShapeFactory::GetInstance()->Add("circle", DrawCircle);
    circle = ShapeFactory::GetInstance()->Create("circle", shape_params);

    ShapeFactory::GetInstance()->Add("rectangle", DrawRectangle);
    rectangle = ShapeFactory::GetInstance()->Create("rectangle", shape_params);

    ShapeFactory::GetInstance()->Add("square", DrawSquare);
    square = ShapeFactory::GetInstance()->Create("square", shape_params);

    ShapeFactory::GetInstance()->Add("line", DrawLine);
    line = ShapeFactory::GetInstance()->Create("line", shape_params);

    DrawInit(argc, argv, 1000, 1000, DrawShapes);
    DrawMainLoop();

    return (0);
}
