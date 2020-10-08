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

Student AddStudent()
{
    Student kate(std::string("kath Bush"), 123456789, std::string("science"),
                 0);
    Subject* subject = new Subject(std::string("Music"));
    kate.AddSubject(subject);
    Subject* subject2 = new Subject(std::string("Math"));
    kate.AddSubject(subject2);
    Subject* subject3 = new Subject(std::string("software engeneer"));
    kate.AddSubject(subject3);
    /*kate.Print();*/

    return (kate);
}

int main()
{
    /*AddStudent();*/
    Collage collage;
    collage.AddFaculty(std::string("science"));
    collage.AddFaculty(std::string("music"));

    Student student = AddStudent();
    collage.AddStudent(&student);
    collage.PrintStudents();
    Subject* dance = new Subject(std::string("dance"));
    collage.ChangeSubject(student.GetID(), std::string("science"), dance);
    collage.PrintStudents();

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
