/*******************************************************************************
Thread Pool

Written by Anat Wax, anatwax@gmail.com
Created: 3.9.20
Reviewer: Daria Korotkova
*******************************************************************************/
#ifndef __ILRD_RD8586__HPP_
#define __ILRD_RD8586__HPP__

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <map>
#include <queue>
#include <vector>

#include "waitable_queue.hpp"

namespace ilrd
{

class ThreadPool : private boost::noncopyable
{
public:
    typedef boost::function< void() > ActionFunc;
    typedef boost::shared_ptr< boost::thread > SHARED_PTR;

    class Task
    {
    public:
        Task(ActionFunc func) : m_exec_func(func)
        {
        }
        virtual ~Task()
        {
        }
        virtual void operator()(); // activate the ActionFunc

    private:
        ActionFunc m_exec_func;
    };

    explicit ThreadPool(size_t num_of_threads);

    ~ThreadPool();

    // Add a new task, and (in the future) will returns a FutureObject
    void AddTask(const Task& task);

    // SetNumberOfThreads which gets new total of threads and add/remove threads
    // from the pool
    bool SetThreadsAmount(size_t new_amount);

    // Exits all threads - if a thread is in the middle of a task - it will wait
    // for the task to end before stoping the thread:
    void Stop();
    void Pause();  // Move all threads in blocking mode
    void Resume(); // Resume all threads to work again (non-blocking mode)

    size_t GetAmountOfThreads();

private:
    void ThreadTask();
    boost::thread::id PrepareForDelete();
    void DeleteThread();

    size_t m_num_threads;
    std::vector< SHARED_PTR > m_threads;
    WaitableQueue< std::queue< Task >, Task > m_tasks;

    boost::condition_variable m_cond;
    boost::mutex m_pause_mutex;
    bool m_paused;
    std::map< boost::thread::id, bool >
        m_thread_running; // flag to run activate flags in a loop
    bool ShouldThreadRun(boost::thread::id thread_id);
    void InitializeThreads(size_t num_of_threads);
};

} // namespace ilrd

#endif /* __ILRD_RD8586__HPP__ */
