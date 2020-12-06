/*******************************************************************************
Test for a program that manages a collage.
Part of a simulation with Elena.

Written by Anat Wax, anatwax@gmail.com
Created: 7.10.20
*******************************************************************************/
#include <atomic>
#include <boost/thread.hpp>
#include <iostream> // cout, cin, cerr
#include <string>

#include "collage.hpp"

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

void DeleteStudent(Student& student)
{
    int num_subjects = student.GetNumSubjects();
    for (int i = 0; i < num_subjects; ++i)
    {
        student.RemoveSubject(student.PickSubject(0));
    }
}

void DoCoolStuff()
{
    std::atomic< int > thread_num(1);
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
    collage.PrintStudents();
    Subject* dance = new Subject(std::string("dance"));
    collage.ChangeSubject(student1.GetID(), std::string("Math"), dance);
    collage.ChangeSubject(student1.GetID(), std::string("science"), dance);

    std::cout << "\nprinting student by id number(123456789):" << std::endl;
    collage.PrintStudent(KATE_ID);

    std::cout << "\nprinting student by name (kath Bush):" << std::endl;
    collage.PrintStudent(KATE_NAME);

    std::cout << "\n"
              << thread_num++
              << ": printing students by faculty (\"science\"):" << std::endl;
    collage.PrintStudents(std::string("science"));

    sleep(1);

    std::cout << "\n"
              << thread_num++
              << ": printing students by year (0):" << std::endl;
    collage.PrintStudents(0);

    sleep(1);

    std::cout << "\n"
              << thread_num++
              << ": printing students by faclty (\"science\") and year (0):"
              << std::endl;
    collage.PrintStudents(std::string("science"), 0);

    sleep(1);

    std::cout << "\n"
              << thread_num++
              << ": printing students by faclty (\"science\") and year (1):"
              << std::endl;
    collage.PrintStudents(std::string("science"), 1);

    sleep(1);

    std::cout << "\n"
              << thread_num++
              << ": printing students by faclty (\"science\") and year (2):"
              << std::endl;
    collage.PrintStudents(std::string("science"), 2);

    sleep(1);

    std::cout << "\n\n"
              << thread_num++
              << ": printing students by faclty (\"music\"):" << std::endl;
    collage.PrintStudents(std::string("music"));

    DeleteStudent(student1);
    DeleteStudent(student2);
    DeleteStudent(student3);
}

Student* AddLargeStudent()
{
    static int id = 11111;
    Student* student =
        new Student("L_student", id++, std::string("large_numbers"), 0);
    Subject* subject = new Subject(std::string("magic"));
    (*student).AddSubject(subject);
    Subject* subject2 = new Subject(std::string("touch"));
    (*student).AddSubject(subject2);

    return student;
}

void DeleteLargeStudent(Collage& collage)
{
    size_t num_students = collage.GetNumStudents();
    for (size_t i = 0; i < num_students; ++i)
    {
        collage.RemoveStudent(collage.PeekStudent()->GetID());
    }
}

void LargeNumbers()
{
    std::atomic< int > thread_num(1);
    /*AddStudent();*/
    Collage collage;
    collage.AddFaculty(std::string("large_numbers"));
    Student* student;
    int i = 0;
    int num = 1000;

    for (i = num; i > 0; --i)
    {
        student = AddLargeStudent();
        collage.AddStudent(student);
    }

    collage.PrintStudents();
    Subject* dance = new Subject(std::string("dance"));
    collage.ChangeSubject((*student).GetID(), std::string("Math"), dance);
    collage.ChangeSubject((*student).GetID(), std::string("science"), dance);

    std::cout << "\nprinting student by id number(11111):" << std::endl;
    collage.PrintStudent(11111);

    std::cout << "\n"
              << thread_num++
              << ": printing students by faculty (\"large_numbers\"):"
              << std::endl;
    collage.PrintStudents(std::string("large_numbers"));

    std::cout << "\n"
              << thread_num++
              << ": printing students by year (0):" << std::endl;
    collage.PrintStudents(0);

    std::cout
        << "\n"
        << thread_num++
        << ": printing students by faclty (\"large_numbers\") and year (0):"
        << std::endl;
    collage.PrintStudents(std::string("large_numbers"), 0);

    std::cout << "\n"
              << thread_num++
              << ": printing students by faclty (\"large_numbers\") and year"
                 "(1) (should be empty):"
              << std::endl;
    collage.PrintStudents(std::string("large_numbers"), 1);

    std::cout << "\n"
              << thread_num++
              << ": printing students by faclty (\"large_numbers\") and year"
                 "(2) (should be empty):"
              << std::endl;
    collage.PrintStudents(std::string("large_numbers"), 2);

    std::cout << "\n\n"
              << thread_num++
              << ": printing students by faclty (\"music\"):" << std::endl;
    collage.PrintStudents(std::string("music"));

    DeleteLargeStudent(collage);
    delete dance;
    // delete student;
}

int main()
{
    boost::thread thread1(DoCoolStuff);
    boost::thread thread3(LargeNumbers);
    boost::thread thread2(DoCoolStuff);

    thread1.join();
    thread3.join();
    thread2.join();

    return (0);
}
