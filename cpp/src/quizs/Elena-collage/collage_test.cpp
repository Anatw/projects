/*******************************************************************************
WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: .9.20
Reviewer:
*******************************************************************************/
#include "collage.hpp"
#include <iostream> // cout, cin, cerr
#include <string>

using namespace ilrd;

void AddStudent()
{
    Student kate(std::string("kath Bush"), 123456789,
                 std::string("faculty of life"), 0);
    Subject* subject = new Subject(std::string("Music"));
    kate.AddSubject(subject);
    Subject* subject2 = new Subject(std::string("Math"));
    kate.AddSubject(subject2);
    Subject* subject3 = new Subject(std::string("software engeneer"));
    kate.AddSubject(subject3);
    kate.Print();
}

int main()
{
    /*AddStudent();*/
    Collage collage;
    collage.AddFaculty(std::string("science"));

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
