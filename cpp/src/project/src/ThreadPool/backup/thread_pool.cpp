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

#include "logger.hpp"
#include "thread_pool.hpp"

using namespace ilrd;

void ThreadPool::Task::operator()()
{
    m_exec_func();
}

void DesaultFunc()
{
}

bool ThreadPool::ShouldThreadRun(const boost::thread::id id)
{
    return (m_thread_running.find(id)->second);
}

void ThreadPool::ThreadTask()
{
    while (true == (ShouldThreadRun(boost::this_thread::get_id())))
    {
        if (m_paused)
        {
            boost::unique_lock< boost::mutex > lock(m_pause_mutex);
            m_cond.wait(lock);
        }

        Task task(DesaultFunc);
        m_tasks.Pop(task, WaitableQueue< std::queue< Task >, Task >::Millisec(
                              5000)); // 5 seconds
        task();
    }
    m_thread_running.erase(m_thread_running.find(boost::this_thread::get_id()));
}

void ThreadPool::InitializeThreads(size_t num_of_threads)
{
    for (size_t i = 0; i < num_of_threads; ++i)
    {
        m_threads.push_back(SHARED_PTR(
            new boost::thread(boost::bind(&ThreadPool::ThreadTask, this))));

        m_thread_running.insert(std::pair< boost::thread::id, bool >(
            m_threads.rbegin()->get()->get_id(), true));
    }
}

ThreadPool::ThreadPool(size_t num_of_threads)
    : m_num_threads(num_of_threads), m_paused(false)
{
    // Initialize as many threads as the user requested and place them inside
    // vector m_threads:
    LOG_DEBUG(__FILE__ + std::string("::ThreadPool()"));

    InitializeThreads(num_of_threads);
}

ThreadPool::~ThreadPool()
{
    Stop();
}

void ThreadPool::AddTask(const Task& task)
{
    // Add the new task tstacko the waitable queue:
    m_tasks.Push(task);
}

void ThreadPool::DeleteThread()
{
    // rbegin takes the reverse begin of the std::vector, meaning the last real
    // element of the vector (end is pointing at a non real temination sign)
    boost::thread* thread = m_threads.rbegin()->get();

    m_thread_running.find(boost::this_thread::get_id())->second = false;

    thread->join();
    m_threads.pop_back();
}

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
            m_threads.push_back(SHARED_PTR(
                new boost::thread(boost::bind(&ThreadPool::ThreadTask, this))));

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
            Task task(DesaultFunc);
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

void ThreadPool::Stop()
{
    // In case there are threads that are paused, I want to un-block them so
    // they can be joined:
    m_cond.notify_all();

    for (size_t counter = 0; counter < m_num_threads; ++counter)
    {

        m_threads[counter]->join();
    }
}

void ThreadPool::Pause()
{
    std::map< boost::thread::id, bool >::iterator it = m_thread_running.begin();
    for (; it != m_thread_running.end(); ++it)
    {
        it->second = false;
    }

    m_paused = true;
}

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

size_t ThreadPool::GetAmountOfThreads()
{
    return (m_num_threads);
}
