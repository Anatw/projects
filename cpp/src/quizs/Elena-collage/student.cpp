/*******************************************************************************
WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: .9.20
Reviewer:
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "student.hpp"
#include "subject.hpp"

using namespace ilrd;

Student::Student(const std::string name, const int id, std::string faculty,
                 int year)
    : m_name(name), m_id(id), m_year(year), m_faculty(faculty),
      NUM_SUBJECTS(10), m_num_subjects(0)
{
    for (int i = 0; i <= NUM_SUBJECTS; ++i)
    {
        m_subjects[i] = NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Student::Print() const
{
    int i = 0;
    std::cout << this->m_name << "   |   id: " << m_id
              << "   |   Faculty: " << m_faculty
              << "   |   Subjects: " << m_subjects[i]->GetName();

    for (i = 1; m_subjects[i] != NULL; ++i)
    {
        std::cout << ", ";
        std::cout << m_subjects[i]->GetName();
    }

    std::cout << "   |   Year of study: " << m_year << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void Student::AddSubject(const Subject* subject)
{
    if (10 >= m_num_subjects)
    {
        // error - no room for new subject
        // return;
    }

    m_subjects[m_num_subjects++] = const_cast< Subject* >(subject);
}

////////////////////////////////////////////////////////////////////////////////

void Student::RemoveSubject(const std::string subject)
{
    Subject* to_remove = NULL;
    int i = 0;
    int j = 0;

    for (; i < NUM_SUBJECTS; ++i)
    {
        if (subject == m_subjects[i]->GetName())
        {
            to_remove = m_subjects[i];
            break;
        }
    }

    if (NULL != to_remove)
    {
        while (i < 10)
        {
            j = i + 1;
            m_subjects[i++] = m_subjects[j];
        }
    }

    delete (to_remove);
}
