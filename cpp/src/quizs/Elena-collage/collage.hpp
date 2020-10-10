/*******************************************************************************
collage

Written by Anat Wax, anatwax@gmail.com
reated: 7.10.20
Reviewer:
*******************************************************************************/

#ifndef __ILRD_RD8586_COLLAGE_HPP_
#define __ILRD_RD8586_COLLAGE_HPP_

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/thread/mutex.hpp>
#include <map>
#include <string>
#include <vector>

#include "faculty.hpp"
#include "student.hpp"
#include "subject.hpp"

// add - addfaculty method

namespace ilrd
{
class Collage
{
public:
    Collage();
    ~Collage();

    void PrintStudent(std::string name);
    void PrintStudent(int id);
    void PrintStudents();
    void PrintStudents(int year);
    void PrintStudents(std::string faculty);
    void PrintStudents(std::string faculty, int year);

    void AddFaculty(std::string name);

    void AddStudent(Student* student);
    void RemoveStudent(int id);
    void RemoveStudent(std::string name);

    void ChangeSubject(int student_id, std::string subject_to_remove,
                       Subject* subject_to_add);

private:
    std::vector< Faculty > m_faculties;
    std::map< int, Student* > m_students;         // int id, std::stringname
    std::map< std::string, int > m_name_students; // std::string name, int id

    boost::mutex m_students_mutex;
};
} // namespace ilrd

#endif /* __ILRD_RD8586_COLLAGE_HPP_ */
