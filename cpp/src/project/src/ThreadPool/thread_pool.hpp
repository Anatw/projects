/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/

#ifndef __ILRD_RD8586__HPP_
#define __ILRD_RD8586__HPP__

#include <boost/chrono.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>

#include "priority_queue.hpp"
#include "task.hpp"

namespace ilrd
{

class ThreadPool : private boost::noncopyable
{
public:
    // CTOR should get number of threads and create it
    ThreadPool(size_t num_of_threads);

    // SetNumberOfThreads which gets new total of threads and add/remove threads
    // from the pool
    void SetNumThreads(size_t num_of_threads);

    // Add a new task, and (in the future) will returns a FutureObject
    void AddTask(const Task& task);
    void Stop();   // Finish all threads
    void Pause();  // Move all threads in blocking mode
    void Resume(); // Move all threads in non-blocking mode

private:
    std::vector< boost::thread > m_threads;
    PriorityQueue< Task > m_pqueue;
    boost::mutex m_mutex;
};

} // namespace ilrd

#endif /* __ILRD_RD8586__HPP__ */
