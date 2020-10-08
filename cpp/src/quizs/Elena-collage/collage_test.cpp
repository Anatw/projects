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

#define KATE_NAME std::string("kath Bush")
#define KATE_ID 123456789

Student AddStudentA1()
{
    Student kate(KATE_NAME, KATE_ID, std::string("science"), 0);
    Subject* subject = new Subject(std::string("Music"));
    kate.AddSubject(subject);
    Subject* subject2 = new Subject(std::string("Math"));
    kate.AddSubject(subject2);
    Subject* subject3 = new Subject(std::string("software engeneer"));
    kate.AddSubject(subject3);
    /*kate.Print();*/

    return (kate);
}

Student AddStudentA2()
{
    Student jack("jack splinter", 1517438, std::string("science"), 2);
    Subject* subject2 = new Subject(std::string("Math"));
    jack.AddSubject(subject2);
    Subject* subject3 = new Subject(std::string("black history"));
    jack.AddSubject(subject3);
    /*kate.Print();*/

    return (jack);
}

Student AddStudentB1()
{
    Student maria("maria callas", 1111111, std::string("music"), 2);
    Subject* subject2 = new Subject(std::string("music"));
    maria.AddSubject(subject2);
    Subject* subject3 = new Subject(std::string("biology"));
    maria.AddSubject(subject3);
    /*kate.Print();*/

    return (maria);
}

int main()
{
    /*AddStudent();*/
    Collage collage;
    collage.AddFaculty(std::string("science"));
    collage.AddFaculty(std::string("music"));

    Student student1 = AddStudentA1();
    Student student2 = AddStudentA2();
    Student student3 = AddStudentB1();
    collage.AddStudent(&student1);
    collage.AddStudent(&student2);
    collage.AddStudent(&student3);
    // collage.PrintStudents();
    // Subject* dance = new Subject(std::string("dance"));
    // collage.ChangeSubject(student1.GetID(), std::string("Math"), dance);
    // collage.ChangeSubject(student1.GetID(), std::string("science"), dance);

    // std::cout << "\nprinting student by id number(123456789):" << std::endl;
    // collage.PrintStudent(KATE_ID);

    // std::cout << "\nprinting student by name (kath Bush):" << std::endl;
    // collage.PrintStudent(KATE_NAME);

    std::cout << "\nprinting students by faculty (\"science\"):" << std::endl;
    collage.PrintStudents(std::string("science"));

    std::cout << "\nprinting students by year (0):" << std::endl;
    collage.PrintStudents(0);

    std::cout << "\nprinting students by faclty (\"science\") and year (0):"
              << std::endl;
    collage.PrintStudents(std::string("science"), 0);

    std::cout << "\nprinting students by faclty (\"science\") and year (1):"
              << std::endl;
    collage.PrintStudents(std::string("science"), 1);

    std::cout << "\nprinting students by faclty (\"science\") and year (2):"
              << std::endl;
    collage.PrintStudents(std::string("science"), 2);

    std::cout << "\n\nprinting students by faclty (\"music\"):" << std::endl;
    collage.PrintStudents(std::string("music"));

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
