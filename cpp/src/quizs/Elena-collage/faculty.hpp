/*******************************************************************************
Factory header. Part of a program that manages a collage.
Part of a simulation with Elena.

Written by Anat Wax, anatwax@gmail.com
reated: 7.10.20
*******************************************************************************/

#ifndef __ILRD_RD8586_FACULTY_HPP_
#define __ILRD_RD8586_FACULTY_HPP_

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <string>
#include <vector>

#include "student.hpp"

namespace ilrd
{
class Faculty
{
public:
    Faculty(const std::string& name);

    void AddYear(const int year);
    void AddStudent(const int year, const int students_id);
    void PrintYear(std::map< int, Student* >& m_students, int year) const;
    void PrintFacultyStudents(std::map< int, Student* >& m_students) const;
    void RemoveStudent(const int id);

    inline std::string GetFacultyName() const
    {
        return m_faculty_name;
    }

private:
    std::string m_faculty_name;
    std::vector< std::vector< int > > m_years; // int id
};
} // namespace ilrd

#endif /* __ILRD_RD8586_FACULTY_HPP_ */
