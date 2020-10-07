/*******************************************************************************
collage

Written by Anat Wax, anatwax@gmail.com
reated: 7.10.20
Reviewer:
*******************************************************************************/

#ifndef __ILRD_RD8586_COLLAGE_HPP_
#define __ILRD_RD8586_COLLAGE_HPP_

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <map>
#include <vector>

#include "faculty.hpp"
#include "student.hpp"
#include "subject.hpp"

namespace ilrd
{
class Collage
{
public:
    Collage();
    ~Collage();

    void PrintStudent(char* name);
    void PrintStudent(int id);
    void PrintStudents();
    void PrintStudents(int year);
    void PrintStudents(char* faculty);
    void PrintStudents(char* faculty, int year);

    void AddStudent(Student* student);
    void RemoveStudent(int id);
    void RemoveStudent(char* name);

    void ChangeSubject(int student_id, char* subject_to_remove,
                       Subject* subject_to_add);

private:
    std::vector< Faculty > m_faculties;
    std::map< int, Student* > m_students;   // int id, char *name
    std::map< char*, int > m_name_students; // char* name, int id
};
} // namespace ilrd

#endif /* __ILRD_RD8586_COLLAGE_HPP_ */
