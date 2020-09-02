/*******************************************************************************
Plug&Play - Phase 3:
DLLoader class

Written by Anat Wax, anatwax@gmail.com
Created: 30.8.20
Reviewer:
*******************************************************************************/
#include <iostream> // cout, cin, cerr
#include <string>

#include "circle.hpp"
#include "dlloader.hpp"
#include "factory.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "square.hpp"

using namespace ilrd;

// static void __attribute__((constructor)) init();

Shape* circle = NULL;
Shape* rectangle = NULL;
Shape* square = NULL;

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

typedef Singleton< Factory< std::string, Shape, Params > > ShapeFactory;

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

// TestCase1() test creation of a dlloader and loading a library to monitor
void TestCase1()
{
    DLLoader* dlloader = NULL;
    try
    {
        std::string str = "/home/anat/git/anat-wax/cpp/src/project/src/"
                          "PlugAndPlay/SharedObject";
        dlloader = new DLLoader(str);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

static void DrawShapes()
{
    circle->Draw();
    rectangle->Draw();
}

// Check creation of two shapes that I tought the factory how to built (circle
// and rectangle)
void TestCase2(int argc, char** argv)
{
    std::string str = "/home/anat/git/anat-wax/cpp/src/project/src/PlugAndPlay/"
                      "SharedLibraries/";
    DLLoader dlloader(str);

    Params shape_params;
    shape_params.position_ = Point(400, 400);
    shape_params.angle_ = 28;
    shape_params.color_ = Color();
    shape_params.width_ = 68;
    shape_params.length_ = 87;
    shape_params.radius_ = 100;
    shape_params.edge_ = 95;

    ShapeFactory::GetInstance()->Add("circle", DrawCircle);
    circle = ShapeFactory::GetInstance()->Create("circle", shape_params);

    // ShapeFactory::GetInstance()->Add("rectangle", DrawRectangle);
    // rectangle = ShapeFactory::GetInstance()->Create("rectangle",
    // shape_params);

    // DrawInit(argc, argv, 1000, 1000, DrawShapes);
    // DrawMainLoop();
}

static void DrawSquare()
{

    square->Draw();
}
// Try to create a shape unkown to the factory - square, and try to create it -
// this test should fail
void TestCase3(int argc, char** argv)
{
    Params shape_params;
    shape_params.position_ = Point(400, 400);
    shape_params.angle_ = 28;
    shape_params.color_ = Color();
    shape_params.width_ = 68;
    shape_params.length_ = 87;
    shape_params.radius_ = 100;
    shape_params.edge_ = 95;

    Shape* square = ShapeFactory::GetInstance()->Create("square", shape_params);
    square->Draw();

    DrawInit(argc, argv, 1000, 1000, DrawSquare);
    DrawMainLoop();
}
// load a new shape - square, and try to create it
void TestCase4()
{
}

int main(int argc, char** argv)
{
    TestCase1();
    TestCase2(argc, argv);
    // TestCase3(argc, argv);
    // TestCase4(argc, argv);

    return (0);
}
