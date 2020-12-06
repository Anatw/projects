/*******************************************************************************
Thread Pool

Written by Anat Wax, anatwax@gmail.com
Created: 3.9.20
Reviewer: Daria Korotkova
*******************************************************************************/

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <queue>
#include <stack>
#include <vector>

#include "logger.hpp"
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
    std::cout << "DefaultFunc()" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
//                           Thread functions:                                //
////////////////////////////////////////////////////////////////////////////////

ThreadPool::ActiveThread::ActiveThread(ThreadPool& thread_pool)
    : m_state(RUN), m_thread(boost::bind(&ActiveThread::ThreadFunc, this)),
      m_myPool(thread_pool)
{
    // Initialize threads in false state, activate them only inside Start().
}

////////////////////////////////////////////////////////////////////////////////

ThreadPool::ActiveThread::~ActiveThread()
{
    m_thread.join();
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::ActiveThread::StopRunning()
{
    this->m_state = STOP;
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::ActiveThread::ThreadFunc()
{
    // boost::unique_lock< boost::mutex > lock(m_myPool->m_pause_mutex);
    // m_myPool->m_cond.wait(lock);
    m_myPool.m_semaphore.wait();

    m_state = RUN;

    while (RUN == this->m_state)
    {
        std::cout << boost::this_thread::get_id() << std::endl;
        TASK_PTR task_ptr(new Task(DefaultFunc));
        PriorityAndTask to_pop(MIDDLE, task_ptr);

        if (m_myPool.m_tasks.Pop(to_pop,
                                 TASKS_QUQUE::Millisec(5000))) // 5 seconds
        {
            std::cout << "ThreadFunc" << std::endl;
            to_pop.second->operator()();
        }
    }

    m_myPool.joining_queue.Push(this);
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::PauseThread()
{
    boost::unique_lock< boost::mutex > lock(m_pause_mutex);
    m_cond.wait(lock);
}

////////////////////////////////////////////////////////////////////////////////
//                  get      ThreadPool functions: //
////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Stop()
{
    // In case there are threads that are paused, I want to un-block them so
    // they can be joined:
    LOG_DEBUG(__FILE__ + std::string("::Stop()"));

    SetThreadsAmount(0);
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::ThreadsInit(size_t num_of_threads)
{
    ActiveThread* thread;

    for (size_t i = 0; i < num_of_threads; ++i)
    {
        thread = new ActiveThread(*this);
        std::cout << "Creation" << thread->m_thread.get_id() << std::endl;
        m_callbacks.insert(
            std::make_pair(boost::this_thread::get_id(),
                           boost::bind(&ActiveThread::StopRunning, thread)));

        ++this->m_num_threads;
    }
}

////////////////////////////////////////////////////////////////////////////////

ThreadPool::ThreadPool(size_t num_of_threads) : m_num_threads(0), m_semaphore(0)
{
    // Initialize as many threads as the user requested and place them inside
    LOG_DEBUG(__FILE__ + std::string("::ThreadPool()"));

    ThreadsInit(num_of_threads);
}

////////////////////////////////////////////////////////////////////////////////

ThreadPool::~ThreadPool()
{
    Stop();
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Start()
{
    for (size_t i = 0; i < m_num_threads; ++i)
    {
        m_semaphore.post();
    }
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::AddTask(TASK_PTR task, int priority)
{
    // Add the new task to the waitable queue:
    // m_tasks.Push(std::make_pair(task, priority));
    std::cout << "ADDING TASK" << std::endl;
    m_tasks.Push(PriorityAndTask(priority, task));
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::KillThread()
{
    m_callbacks.find(boost::this_thread::get_id())->second();
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::SetThreadsAmount(size_t new_amount)
{
    ssize_t amount_to_change = new_amount - m_num_threads;

    if (0 == amount_to_change)
    {
        ;
    }
    else if (amount_to_change > 0)
    {
        // Create amount_to_change more threads in the thread pool:
        ThreadsInit(amount_to_change);
    }
    else
    {
        // Delete amount_to_change more threads in the thread pool:
        // push to the task queue amount_to_change quantity of mission to delete
        // a thread:
        std::stack< Task > temp_task_stack;
        while (!m_tasks.Empty())
        {
            TASK_PTR task_ptr(new Task(DefaultFunc));
            PriorityAndTask to_pop(MIDDLE, task_ptr);
            m_tasks.Pop(to_pop,
                        TASKS_QUQUE::Millisec(5000)); // 5 seconds);
            // temp_task_stack.push(task);
        }

        // make_shared is like a "new" to shared pointer.
        TASK_PTR task_ptr(boost::make_shared< Task >(
            boost::bind(&ThreadPool::KillThread, this)));
        PriorityAndTask to_push(HIGH, task_ptr);
        size_t amount_to_delete = (amount_to_change * (-1));
        while (amount_to_change < 0)
        {
            m_tasks.Push(to_push);

            ++amount_to_change;
        }

        ActiveThread* thread_to_delete;
        while (amount_to_delete)
        {
            joining_queue.Pop(thread_to_delete);
            delete thread_to_delete;

            --amount_to_delete;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Pause()
{
    TASK_PTR task =
        boost::make_shared< Task >(boost::bind(&ThreadPool::PauseThread, this));
    PriorityAndTask to_push((HIGH - 1), task);
    for (size_t i = 0; i < m_num_threads; ++i)
    {
        m_tasks.Push(to_push);
    }
}

// ////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Resume()
{
    m_cond.notify_all();
}

////////////////////////////////////////////////////////////////////////////////

size_t ThreadPool::GetAmountOfThreads()
{
    return (m_num_threads);
}
