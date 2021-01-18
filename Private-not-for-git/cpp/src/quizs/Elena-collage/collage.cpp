/*******************************************************************************
Collage class. Part of a program that manages a collage.
Part of a simulation with Elena.

Written by Anat Wax, anatwax@gmail.com
reated: 7.10.20
*******************************************************************************/
#include <algorithm>
#include <iostream> // cout, cin, cerr

#include "collage.hpp"

using namespace ilrd;

Collage::Collage()
    : m_semaphore(1), m_writer_counter(0), m_finished_writing(true),
      m_finished_reading(true)
{
}

Collage::~Collage()
{
}

////////////////////////////////////////////////////////////////////////////////

void Collage::PrintStudent(std::string name)
{
    // Give priority for writer threads
    m_mutex_sync.lock();
    m_mutex_sync.unlock();

    // If another thread is currently reading, the thread will stop here, and
    // after the previous thread has finished reading, the current thread will
    // first wait for any writers that need to write, and only if no writers are
    // waiting (meaning that no new writers had arrived while the current thread
    // was blocked on the condition variable) - it will acquire the semaphore:
    boost::unique_lock< boost::mutex > lock(m_mutexR);
    while (false == m_finished_reading)
    {
        m_cond_reader.wait(lock);
    }
    m_finished_reading = false;

    // Check if there is a writer in the middle of writing
    m_semaphore.wait();

    m_students.find(m_name_students.find(name)->second)->second->Print();

    m_semaphore.post();
    m_finished_reading = true;
    m_cond_reader.notify_one();
}

////////////////////////////////////////////////////////////////////////////////

void Collage::PrintStudent(int id)
{
    m_mutex_sync.lock();
    m_mutex_sync.unlock();

    boost::unique_lock< boost::mutex > lock(m_mutexR);
    while (false == m_finished_reading)
    {
        m_cond_reader.wait(lock);
    }
    m_finished_reading = false;

    m_semaphore.wait();

    m_students.find(id)->second->Print();

    m_semaphore.post();
    m_finished_reading = true;
    m_cond_reader.notify_one();
}

////////////////////////////////////////////////////////////////////////////////

void Collage::PrintStudents()
{
    std::map< int, Student* >::iterator iterator = m_students.begin();
    std::map< int, Student* >::iterator end_iter = m_students.end();

    m_mutex_sync.lock();
    m_mutex_sync.unlock();

    boost::unique_lock< boost::mutex > lock(m_mutexR);
    while (false == m_finished_reading)
    {
        m_cond_reader.wait(lock);
    }
    m_finished_reading = false;

    m_semaphore.wait();

    for (; iterator != end_iter; ++iterator)
    {
        iterator->second->Print();
    }

    m_semaphore.post();
    m_finished_reading = true;
    m_cond_reader.notify_one();
}

////////////////////////////////////////////////////////////////////////////////

void Collage::PrintStudents(int year)
{
    size_t i = 0;
    m_mutex_sync.lock();
    m_mutex_sync.unlock();

    boost::unique_lock< boost::mutex > lock(m_mutexR);
    while (false == m_finished_reading)
    {
        m_cond_reader.wait(lock);
    }
    m_finished_reading = false;

    m_semaphore.wait();

    size_t num_faculties = m_faculties.size();
    for (; i < num_faculties; ++i)
    {
        m_faculties[i].PrintYear(m_students, year);
    }

    m_semaphore.post();
    m_finished_reading = true;
    m_cond_reader.notify_one();
}

////////////////////////////////////////////////////////////////////////////////

void Collage::PrintStudents(std::string faculty)
{
    m_mutex_sync.lock();
    m_mutex_sync.unlock();

    boost::unique_lock< boost::mutex > lock(m_mutexR);
    while (false == m_finished_reading)
    {
        m_cond_reader.wait(lock);
    }
    m_finished_reading = false;

    m_semaphore.wait();

    std::vector< Faculty >::iterator iterator = m_faculties.begin();
    for (; iterator != m_faculties.end(); ++iterator)
    {
        if (iterator->GetFacultyName() == faculty)
        {
            iterator->PrintFacultyStudents(m_students);
        }
    }

    if (iterator == m_faculties.end())
    {
        std::cout << "inside PrintStudents(faculty): requested faculty (\""
                  << faculty << "\") is not inside the database" << std::endl;
    }

    m_semaphore.post();
    m_finished_reading = true;
    m_cond_reader.notify_one();
}

////////////////////////////////////////////////////////////////////////////////

void Collage::PrintStudents(std::string faculty, int year)
{
    m_mutex_sync.lock();
    m_mutex_sync.unlock();

    boost::unique_lock< boost::mutex > lock(m_mutexR);
    while (false == m_finished_reading)
    {
        m_cond_reader.wait(lock);
    }
    m_finished_reading = false;

    m_semaphore.wait();

    std::vector< Faculty >::iterator iterator = m_faculties.begin();
    for (; iterator != m_faculties.end(); ++iterator)
    {
        if (iterator->GetFacultyName() == faculty)
        {
            iterator->PrintYear(m_students, year);
        }
    }

    m_semaphore.post();
    m_finished_reading = true;
    m_cond_reader.notify_one();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Collage::AddStudent(Student* student)
{
    // Getting priority over reader threads - the first writer will aquire the
    // semaphore:
    m_mutex_sync.lock();
    if (++m_writer_counter == 1)
    {
        m_semaphore.wait();
    }
    m_mutex_sync.unlock();

    // Condition variable to synchronise between several reader threads:
    boost::unique_lock< boost::mutex > lock(m_mutexW);
    while (false == m_finished_writing)
    {
        m_cond_writer.wait(lock);
    }
    m_finished_writing = false;

    m_students.insert(std::make_pair(student->GetID(), student));
    m_name_students.insert(
        std::make_pair(student->GetName(), student->GetID()));

    // Insert the student to the relevant faculty:
    std::string faculty_name = student->GetFaculty();
    std::vector< Faculty >::iterator faculty_iterator = m_faculties.begin();

    for (; faculty_iterator != m_faculties.end(); ++faculty_iterator)
    {
        if (faculty_iterator->GetFacultyName() == faculty_name)
        {
            faculty_iterator->AddYear(student->GetYear());
            faculty_iterator->AddStudent(student->GetYear(), student->GetID());
            break;
        }
    }

    m_finished_writing = true;
    m_cond_writer.notify_one();

    // The last writer will open the semaphore for any readers waiting:
    m_mutex_sync.lock();
    if (--m_writer_counter == 0)
    {
        m_semaphore.post();
    }
    m_mutex_sync.unlock();

    if (faculty_iterator == m_faculties.end())
    {
        std::cout << "ERROR in adding student to a faculty - faculty \""
                  << student->GetFaculty()
                  << "\" is not inside list! (error for student id "
                  << student->GetID() << ")" << std::endl;
        exit(EXIT_FAILURE);
    }
}

////////////////////////////////////////////////////////////////////////////////

void Collage::RemoveStudentNotTS(std::string name, int id)
{
    Student* to_delete = m_students.find(id)->second;
    int num_subjects = to_delete->GetNumSubjects();
    for (int i = 0; i < num_subjects; ++i)
    {
        to_delete->RemoveSubject(to_delete->PickSubject(0));
    }
    // Delete student:
    std::map< std::string, int >::iterator iterator = m_name_students.begin();
    std::map< std::string, int >::iterator i_end = m_name_students.end();

    for (; iterator != i_end; ++iterator)
    {
        if (iterator->first == name && iterator->second == id)
        {
            m_name_students.erase(iterator);
            break;
        }
    }

    delete to_delete;
}

void Collage::RemoveStudent(int id)
{
    std::string student_name;
    std::string faculty_name;

    m_mutex_sync.lock();
    if (++m_writer_counter == 1)
    {
        m_semaphore.wait();
    }
    m_mutex_sync.unlock();

    boost::unique_lock< boost::mutex > lock(m_mutexW);
    while (false == m_finished_writing)
    {
        m_cond_writer.wait(lock);
    }
    m_finished_writing = false;

    std::map< int, Student* >::iterator iterator = m_students.find(id);

    if (iterator == m_students.end())
    {
        std::cout << "The requested student is not inside the collage database"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    student_name = iterator->second->GetName();
    faculty_name = iterator->second->GetFaculty();

    // Remove student to the relevant faculty:
    std::vector< Faculty >::iterator faculty_iterator = m_faculties.begin();

    for (; faculty_iterator != m_faculties.end(); ++faculty_iterator)
    {
        if (iterator->second->GetFaculty() == faculty_name)
        {
            // Delete student from faculty inner detabase:
            faculty_iterator->RemoveStudent(iterator->second->GetID());
            break;
        }
    }

    // Delete student from name_student detabase:
    RemoveStudentNotTS(student_name, id);
    // Delete student from general Students detabase
    m_students.erase(iterator);

    m_finished_writing = true;
    m_cond_writer.notify_one();

    m_mutex_sync.lock();
    if (--m_writer_counter == 0)
    {
        m_semaphore.post();
    }
    m_mutex_sync.unlock();
}

////////////////////////////////////////////////////////////////////////////////

void Collage::RemoveStudentNotTS(int id)
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

    // Remove student to the relevant faculty:
    std::vector< Faculty >::iterator faculty_iterator = m_faculties.begin();

    for (; faculty_iterator != m_faculties.end(); ++faculty_iterator)
    {
        if (iterator->second->GetFaculty() == faculty_name)
        {
            faculty_iterator->RemoveStudent(iterator->second->GetID());
            break;
        }
    }

    m_students.erase(iterator);

    RemoveStudent(student_name);
}

void Collage::RemoveStudent(std::string name)
{
    m_mutex_sync.lock();
    if (++m_writer_counter == 1)
    {
        m_semaphore.wait();
    }
    m_mutex_sync.unlock();

    boost::unique_lock< boost::mutex > lock(m_mutexW);
    while (false == m_finished_writing)
    {
        m_cond_writer.wait(lock);
    }
    m_finished_writing = false;

    // Delete student's subjects:
    int to_delete_id = m_name_students.find(name)->second;
    Student* to_delete = m_students.find(to_delete_id)->second;
    int num_subjects = to_delete->GetNumSubjects();
    for (int i = 0; i < num_subjects; ++i)
    {
        to_delete->RemoveSubject(to_delete->PickSubject(0));
    }
    // Delete student:
    m_name_students.erase(m_name_students.find(name));
    RemoveStudentNotTS(to_delete_id);

    delete to_delete;

    m_finished_writing = true;
    m_cond_writer.notify_one();

    m_mutex_sync.lock();
    if (--m_writer_counter == 0)
    {
        m_semaphore.post();
    }
    m_mutex_sync.unlock();
}

////////////////////////////////////////////////////////////////////////////////

void Collage::ChangeSubject(int student_id, std::string subject_to_remove,
                            Subject* subject_to_add)
{
    m_mutex_sync.lock();
    if (++m_writer_counter == 1)
    {
        m_semaphore.wait();
    }
    m_mutex_sync.unlock();

    boost::unique_lock< boost::mutex > lock(m_mutexW);
    while (false == m_finished_writing)
    {
        m_cond_writer.wait(lock);
    }
    m_finished_writing = false;

    std::map< int, Student* >::iterator iterator = m_students.find(student_id);

    if (iterator->second->RemoveSubject(subject_to_remove) == true)
    {
        iterator->second->AddSubject(subject_to_add);
    }

    m_finished_writing = true;
    m_cond_writer.notify_one();

    m_mutex_sync.lock();
    if (--m_writer_counter == 0)
    {
        m_semaphore.post();
    }
    m_mutex_sync.unlock();
}
////////////////////////////////////////////////////////////////////////////////

void Collage::AddFaculty(std::string name)
{
    m_mutex_sync.lock();
    if (++m_writer_counter == 1)
    {
        m_semaphore.wait();
    }
    m_mutex_sync.unlock();

    boost::unique_lock< boost::mutex > lock(m_mutexW);
    while (false == m_finished_writing)
    {
        m_cond_writer.wait(lock);
    }
    m_finished_writing = false;

    Faculty faculty(name);
    m_faculties.push_back(faculty);

    m_finished_writing = true;
    m_cond_writer.notify_one();

    m_mutex_sync.lock();
    if (--m_writer_counter == 0)
    {
        m_semaphore.post();
    }
    m_mutex_sync.unlock();
}

Student* Collage::PeekStudent()
{
    m_mutex_sync.lock();
    if (++m_writer_counter == 1)
    {
        m_semaphore.wait();
    }
    m_mutex_sync.unlock();

    boost::unique_lock< boost::mutex > lock(m_mutexW);
    while (false == m_finished_writing)
    {
        m_cond_writer.wait(lock);
    }
    m_finished_writing = false;

    Student* student = m_students.begin()->second;

    m_finished_writing = true;
    m_cond_writer.notify_one();

    m_mutex_sync.lock();
    if (--m_writer_counter == 0)
    {
        m_semaphore.post();
    }
    m_mutex_sync.unlock();

    return (student);
}
