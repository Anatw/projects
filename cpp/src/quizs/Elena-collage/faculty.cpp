/*******************************************************************************
Faculty class. Part of a program that manages a collage.
Part of a simulation with Elena.

Written by Anat Wax, anatwax@gmail.com
reated: 7.10.20
*******************************************************************************/
#include <iostream> // cout, cin, cerr
#include <map>
#include <vector>

#include "faculty.hpp"

using namespace ilrd;

Faculty::Faculty(const std::string& name) : m_faculty_name(name)
{
}

////////////////////////////////////////////////////////////////////////////////

void Faculty::AddYear(const int year)
{
    std::vector< std::vector< int > >::iterator iterator = m_years.begin();
    std::vector< int >::iterator inner_it;

    // check if year already exists in the faculty database:
    while (iterator != m_years.end())
    {
        for (inner_it = iterator->begin(); year == inner_it[0]; ++inner_it)
        {
            std::cout << "year already exists in faculty database" << std::endl;
            return;
        }

        ++iterator;
    }

    std::vector< int > new_year;
    new_year.push_back(year);
    m_years.push_back(new_year);
}

////////////////////////////////////////////////////////////////////////////////

void Faculty::AddStudent(const int year, const int students_id)
{
    std::vector< std::vector< int > >::iterator iterator = m_years.begin();
    std::vector< int >::iterator inner_it;

    for (; iterator != m_years.end(); ++iterator)
    {
        inner_it = iterator->begin();
        if (inner_it[0] == year) // find year in the faculty array
        {
            // Insert student into the detabase of the specified year:
            // iterator->insert(inner_it, students_id);
            iterator->push_back(students_id);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Faculty::PrintYear(std::map< int, Student* >& m_students, int year) const
{
    std::vector< std::vector< int > >::const_iterator iterator =
        m_years.begin();
    std::vector< int >::const_iterator inner_it;

    for (; iterator != m_years.end(); ++iterator)
    {
        inner_it = iterator->begin();
        if (inner_it[0] == year) // find year in the faculty array
        {
            // print all students' ids:
            for (++inner_it; inner_it != iterator->end(); ++inner_it)
            {
                m_students.find(*inner_it)->second->Print();
            }

            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Faculty::PrintFacultyStudents(std::map< int, Student* >& m_students) const
{
    std::vector< std::vector< int > >::const_iterator iterator =
        m_years.begin();
    std::vector< int >::const_iterator inner_it;

    for (; iterator != m_years.end(); ++iterator)
    {
        // (begin + 1) because begin is the year itself and not an actual
        // student id:
        for (inner_it = (iterator->begin() + 1); inner_it != iterator->end();
             ++inner_it)
        {
            m_students.find(*inner_it)->second->Print();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Faculty::RemoveStudent(const int id)
{
    std::vector< std::vector< int > >::iterator iterator = m_years.begin();
    std::vector< int >::const_iterator inner_it;

    for (; iterator != m_years.end(); ++iterator)
    {
        for (inner_it = iterator->begin(); inner_it != iterator->end();
             ++inner_it) // find year in the faculty array
        {
            // if ID inside year is a match - delete student from detabase
            if (id == (*inner_it))
            {
                // iterator->erase(inner_it, inner_it);
                iterator->erase(inner_it);
                return;
            }
        }
    }
}
