/*******************************************************************************


Written by Anat Wax, anatwax@gmail.com
reated: 7.10.20
Reviewer:
*******************************************************************************/

#ifndef __ILRD_RD8586_STUDENT_HPP_
#define __ILRD_RD8586_STUDENT_HPP_

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <string>

#include "subject.hpp"

namespace ilrd
{
class Student
{
public:
    // for now I'm assuming that the faculty name entered is valid. In actual
    // working system - this should be checked.
    Student(const std::string name, const int id, std::string faculty,
            int year = 0);
    void Print() const;
    void AddSubject(const Subject* subject);
    bool RemoveSubject(const std::string subject);

    inline int GetID() const
    {
        return m_id;
    }
    inline std::string GetName() const
    {
        return m_name;
    }

    inline std::string GetFaculty() const
    {
        return m_faculty;
    }

    inline int GetYear() const
    {
        return m_year;
    }

private:
    std::string m_name;
    int m_id;
    int m_year;
    std::string m_faculty;
    int NUM_SUBJECTS; // 10
    Subject* m_subjects[11];
    int m_num_subjects;
};

} // namespace ilrd

#endif /* __ILRD_RD8586_STUDENT_HPP_ */
