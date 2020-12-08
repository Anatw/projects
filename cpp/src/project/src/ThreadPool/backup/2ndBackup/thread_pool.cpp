/*******************************************************************************
Thread Pool

Written by Anat Wax, anatwax@gmail.com
Created: 3.9.20
Reviewer: Daria Korotkova
*******************************************************************************/

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <queue>
#include <stack>
#include <vector>

// #include "logger.hpp"
#include "thread_pool.hpp"

using namespace ilrd;

////////////////////////////////////////////////////////////////////////////////
//                             Task functions:                                //
////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Task::operator()()
{
    m_exec_func();
}

void DefaultFunc()
{
}

////////////////////////////////////////////////////////////////////////////////
//                           Thread functions:                                //
////////////////////////////////////////////////////////////////////////////////

ThreadPool::ActiveThread::ActiveThread()
    : m_state(STOP), m_thread(boost::bind(&ActiveThread::ThreadTask, this))
{
    // Initialize threads in false state, activate them only inside Start().
}

////////////////////////////////////////////////////////////////////////////////

ThreadPool::ActiveThread::~ActiveThread()
{
    this->m_thread->join();
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::ActiveThread::ThreadTask()
{
    while (RUN == this->m_state)
    {
        if (ThreadPool::m_paused)
        {
            boost::unique_lock< boost::mutex > lock(m_pause_mutex);
            m_cond.wait(lock);
        }

        Task task(DefaultFunc);
        m_tasks.Pop(
            task,
            WaitableQueue< std::priority_queue< std::pair< Task, Priority > >,
                           Task >::Millisec(5000)); // 5 seconds
        task();
    }

    m_thread_running.erase(m_thread_running.find(boost::this_thread::get_id()));
}
////////////////////////////////////////////////////////////////////////////////
//                        ThreadPool functions: //
////////////////////////////////////////////////////////////////////////////////

bool ThreadPool::ShouldThreadRun(const boost::thread::id id)
{
    // find the thread in the list and return it's flags state
    size_t i = 0;

    for (i = 0; i < GetAmountOfThreads(); ++i)
    {
        if (m_threads[i].GetThreadID() == id)
        {
            return (m_threads[i].GetThreadState());
        }
    }

    return (NULL);
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::InitializeThreads(size_t num_of_threads)
{
    for (size_t i = 0; i < num_of_threads; ++i)
    {
        m_threads.push_back(Thread());
    }
}

////////////////////////////////////////////////////////////////////////////////

ThreadPool::ThreadPool(size_t num_of_threads)

{
    // Initialize as many threads as the user requested and place them inside
    // vector m_threads:
    // LOG_DEBUG(__FILE__ + std::string("::ThreadPool()"));

    // InitializeThreads(num_of_threads);
}

////////////////////////////////////////////////////////////////////////////////

ThreadPool::~ThreadPool()
{
    Stop();
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::AddTask(const Task task, Priority priority)
{
    // Add the new task to the waitable queue:
    // m_tasks.Push(std::make_pair(task, priority));
    m_tasks.Push(task);
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::DeleteThread()
{
    // rbegin takes the reverse begin of the std::vector, meaning the last real
    // element of the vector (end is pointing at a non real temination sign)
    // boost::thread* thread = m_threads.rbegin()->get();

    // m_thread_running.find(boost::this_thread::get_id())->second = false;

    // thread->join();
    // m_threads.pop_back();

    std::vector< Thread >::iterator it = m_threads.begin();
    std::vector< Thread >::iterator end = m_threads.end();

    for (; it != end; ++it)
    {
        if (boost::this_thread::get_id() == it->m_thread->get_id())
        {
            std::cout << "FOUND" << std::endl;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

bool ThreadPool::SetThreadsAmount(size_t new_amount)
{
    ssize_t amount_to_change = new_amount - m_num_threads;

    if (0 == amount_to_change)
    {
        ;
    }
    else if (amount_to_change > 0)
    {
        // Create amount_to_change more threads in the thread pool:
        for (ssize_t i = 0; i < amount_to_change; ++i)
        {

            ++m_num_threads;
        }
    }
    else
    {
        // Delete amount_to_change more threads in the thread pool:
        // push to the task queue amount_to_change quantity of mission to delete
        // a thread:
        std::stack< Task > temp_task_stack;
        while (!m_tasks.Empty())
        {
            Task task(DefaultFunc);
            m_tasks.Pop(task,
                        WaitableQueue< std::queue< Task >, Task >::Millisec(
                            5000)); // 5 seconds);
            temp_task_stack.push(task);
        }

        while (amount_to_change < 0)
        {
            ++amount_to_change;
            // Pop all tasks from the vector into a remporary stack, push the
            // delete functions, and than pop the tasks back into the vector
            // m_tasks.Push()
            DeleteThread();
            --m_num_threads;
        }

        while (!temp_task_stack.empty())
        {
            m_tasks.Push(const_cast< const Task& >(temp_task_stack.top()));
            temp_task_stack.pop();
        }
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Stop()
{
    // In case there are threads that are paused, I want to un-block them so
    // they can be joined:
    m_cond.notify_all();

    std::vector< Thread >::iterator it = m_threads.begin();
    for (; it != m_threads.end(); ++it)
    {
        it->ChangeState(false);
        m_threads.erase(it);
        it->m_thread->join();
    }
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Pause()
{
    std::map< boost::thread::id, bool >::iterator it = m_thread_running.begin();
    for (; it != m_thread_running.end(); ++it)
    {
        it->second = false;
    }

    m_paused = true;
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Resume()
{
    std::map< boost::thread::id, bool >::iterator it = m_thread_running.begin();
    for (; it != m_thread_running.end(); ++it)
    {
        it->second = true;
    }

    m_paused = false;

    m_cond.notify_all();
}

////////////////////////////////////////////////////////////////////////////////

size_t ThreadPool::GetAmountOfThreads()
{
    return (m_num_threads);
}
