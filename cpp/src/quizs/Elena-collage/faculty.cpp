/*******************************************************************************
WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: .9.20
Reviewer:
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
        inner_it = iterator->begin();
        if (year == inner_it[0])
        {
            std::cout << "ERROR - year already exists in faculty database"
                      << std::endl;
            exit(EXIT_FAILURE);
        }

        ++inner_it;
    }

    std::vector< int > new_year;
    new_year[0] = year;
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
            iterator->insert(inner_it, students_id);
        }
    }
}

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
            for (; inner_it != iterator->end(); ++inner_it)
            {
                m_students.find(*inner_it)->second->Print();
            }

            break;
        }
    }
}

void Faculty::PrintFacultyStudents(std::map< int, Student* >& m_students) const
{
    std::vector< std::vector< int > >::const_iterator iterator =
        m_years.begin();
    std::vector< int >::const_iterator inner_it;

    for (; iterator != m_years.end(); ++iterator)
    {
        for (inner_it = iterator->begin(); inner_it != iterator->end();
             ++inner_it)
        {
            m_students.find(*inner_it)->second->Print();
        }
    }
}

void Faculty::RemoveStudent(const int id)
{
    std::vector< std::vector< int > >::iterator iterator = m_years.begin();
    std::vector< int >::const_iterator inner_it;

    for (; iterator != m_years.end(); ++iterator)
    {
        for (inner_it = iterator->begin(); inner_it != iterator->end();
             ++inner_it)
        {
            if (id == (*inner_it)) // find year in the faculty array
            {
                // Delete student from detabase:
                // iterator->erase(inner_it, inner_it);
            }
        }
    }
}
