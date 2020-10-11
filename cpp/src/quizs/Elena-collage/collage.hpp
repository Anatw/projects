/*******************************************************************************
Collage header. Part of a program that manages a collage.
Part of a simulation with Elena.

Written by Anat Wax, anatwax@gmail.com
reated: 7.10.20
*******************************************************************************/

#ifndef __ILRD_RD8586_COLLAGE_HPP_
#define __ILRD_RD8586_COLLAGE_HPP_

#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <map>
#include <string>
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
    Student* PeekStudent();

    void ChangeSubject(int student_id, std::string subject_to_remove,
                       Subject* subject_to_add);
    inline size_t GetNumStudents() const
    {
        return m_students.size();
    }

private:
    std::vector< Faculty > m_faculties;
    std::map< int, Student* > m_students;         // int id, std::stringname
    std::map< std::string, int > m_name_students; // std::string name, int id

    void RemoveStudentNotTS(int id);                   // not thread safe
    void RemoveStudentNotTS(std::string name, int id); // not thread safe

    /**************************************************************************/
    /* Sync objects. The writers will always have priority over the reader -  */
    /* the printings should always be as accurate as possible                 */
    /**************************************************************************/
    // mutex to synchronise between readers themselves:
    boost::mutex m_mutexR;
    // mutex to synchronise between writers themselves:
    boost::mutex m_mutexW;
    // mutex to make sure writers get prioretised:
    boost::mutex m_mutex_sync;
    // consition variable - only when all writers waiting to write will finish
    // writing - the readers can read:
    boost::condition_variable m_cond_writer;
    boost::condition_variable m_cond_reader;
    // semaphore se syncronize between readers and writers
    boost::interprocess::interprocess_semaphore m_semaphore;
    int m_writer_counter;
    bool m_finished_writing;
    bool m_finished_reading;
};
} // namespace ilrd

#endif /* __ILRD_RD8586_COLLAGE_HPP_ */
