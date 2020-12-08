/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:

Compile:
pd square_builder.cpp  -fPIC -shared -o libsquarebuilder.so -I
/home/anat/git/anat-wax/cpp/src/project/include/ -I
/home/anat/git/anat-wax/cpp/src/Shapes/include^C
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "factory.hpp"
#include "glut_utils.h"
#include "shape.hpp"
#include "singleton.hpp"
#include "square.hpp"

using namespace ilrd;

static void __attribute__((constructor)) Init();

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

Shape* DrawSquare(Params params)
{
    Square* circle = new Square(params.position_, params.angle_, params.color_,
                                params.edge_);
    return (circle);
}

void Init()
{
    ShapeFactory::GetInstance()->Add("square", DrawSquare);
    std::cout << "Inside square Init" << std::endl;
}
