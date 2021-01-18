/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <fstream>
#include <iostream> // cout, cin, cerr

#include "circle.hpp"
#include "point.hpp"
#include "serializer.hpp"
#include "shape.hpp"

using namespace ilrd;

int main()
{
    Serializer< Shape > serializer;

    serializer.Add< Circle >();

    Circle circle(Point(500, 0), 30, Color(0, 0, 0), 10);

    std::ofstream of_fd;
    of_fd.open("Ser.txt");
    serializer.Serialize(circle, of_fd);
    of_fd.close();

    std::ifstream if_fd;
    if_fd.open("Ser.txt");

    boost::shared_ptr< Shape > result = serializer.Deserialize(if_fd);
    if_fd.close();

    std::cout << result->GetPosition().GetX() << std::endl;
    std::cout << result->GetPosition().GetY() << std::endl;

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
