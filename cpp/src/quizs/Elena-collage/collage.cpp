/*******************************************************************************
WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: .9.20
Reviewer:
*******************************************************************************/
#include <algorithm>
#include <iostream> // cout, cin, cerr

#include "collage.hpp"

using namespace ilrd;

Collage::Collage()
{
}
Collage::~Collage()
{
}

void Collage::PrintStudent(std::string name)
{
    PrintStudent(m_name_students.find(name)->second);
}

void Collage::PrintStudent(int id)
{
    m_students.find(id)->second->Print();
}

void Collage::PrintStudents()
{
    std::map< int, Student* >::iterator iterator = m_students.begin();
    std::map< int, Student* >::iterator end_iter = m_students.end();

    for (; iterator != end_iter; ++iterator)
    {
        iterator->second->Print();
    }
}

void Collage::PrintStudents(int year)
{
    size_t num_faculties = m_faculties.size();
    size_t i = 0;

    for (; i < num_faculties; ++i)
    {
        m_faculties[i].PrintYear(m_students, year);
    }
}

void Collage::PrintStudents(std::string faculty)
{
    // size_t num_faculties = m_faculties.size();
    // size_t i = 0;

    // if (m_faculties.end() != std::find(m_faculties.begin(),
    // m_faculties.end(), faculty))
    // {

    // }

    // for (; i < num_faculties; ++i)
    // {
    //     if (faculty == m_faculties[i].)
    //     {
    //         m_faculties[i].PrintFacultyStudents(m_students);
    //     }
    // }
    std::vector< Faculty >::iterator iterator = m_faculties.begin();

    for (; iterator != m_faculties.end(); ++iterator)
    {
        if (iterator->GetFacultyName() == faculty)
        {
            iterator->PrintFacultyStudents(m_students);
        }
    }
}

void Collage::PrintStudents(std::string faculty, int year)
{
    std::vector< Faculty >::iterator iterator = m_faculties.begin();

    for (; iterator != m_faculties.end(); ++iterator)
    {
        if (iterator->GetFacultyName() == faculty)
        {
            iterator->PrintYear(m_students, year);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Collage::AddStudent(Student* student)
{
    m_students.insert(std::make_pair(student->GetID(), student));
    m_name_students.insert(
        std::make_pair(student->GetName(), student->GetID()));

    // insert the student to the relevant faculty:
    std::string faculty_name = student->GetFaculty();
    std::vector< Faculty >::iterator iterator = m_faculties.begin();

    for (; iterator != m_faculties.end(); ++iterator)
    {
        if (iterator->GetFacultyName() == faculty_name)
        {
            iterator->AddStudent(student->GetYear(), student->GetID());
            break;
        }
        else
        {
            std::cout
                << "ERROR in adding student to a faculty - faculty is not "
                   "inside list!"
                << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Collage::RemoveStudent(int id)
{
    std::string student_name;
    std::string faculty_name;
    std::map< int, Student* >::iterator iterator = m_students.find(id);

    if (iterator == m_students.end())
    {
        std::cout << "The requested student is not inside the collage database"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    student_name = iterator->second->GetName();
    faculty_name = iterator->second->GetFaculty();

    // remove student to the relevant faculty:
    std::vector< Faculty >::iterator faculty_iterator = m_faculties.begin();

    for (; faculty_iterator != m_faculties.end(); ++faculty_iterator)
    {
        if (iterator->second->GetFaculty() == faculty_name)
        {
            faculty_iterator->RemoveStudent(iterator->second->GetID());
            break;
        }
    }

    RemoveStudent(student_name);
    m_students.erase(iterator);
}

////////////////////////////////////////////////////////////////////////////////

void Collage::RemoveStudent(std::string name)
{
    m_name_students.erase(m_name_students.find(name));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Collage::ChangeSubject(int student_id, std::string subject_to_remove,
                            Subject* subject_to_add)
{
    std::map< int, Student* >::iterator iterator = m_students.find(student_id);

    iterator->second->RemoveSubject(subject_to_remove);
    iterator->second->AddSubject(subject_to_add);
}
////////////////////////////////////////////////////////////////////////////////

void Collage::AddFaculty(std::string name)
{
    Faculty faculty(name);
    m_faculties.push_back(faculty);
}
