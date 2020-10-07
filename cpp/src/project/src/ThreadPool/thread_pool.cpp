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
// ADD try and catch for the operator ()() of catch of "..."
// No spinlock - use waitable queue
// don't call the disdtructore directly
// interface between the thread pool and the active thread.

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
    : m_state(STOP), m_myPool(thread_pool)
{
    // Initialize threads in false state, activate them only inside Start().
}

////////////////////////////////////////////////////////////////////////////////

ThreadPool::ActiveThread::~ActiveThread()
{
    std::cout << "Active Thread - Dtor - ID: " << std::endl;
    // m_thread.join();
    sleep(1);
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::ActiveThread::StopRunning()
{
    this->m_state = STOP;
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::ActiveThread::StartThread()
{
    m_thread = boost::thread(boost::bind(&ActiveThread::ThreadFunc, this));
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::ActiveThread::JoinThread()
{
    m_thread.join();
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::ActiveThread::ThreadFunc()
{
    // boost::unique_lock< boost::mutex > lock(m_myPool->m_pause_mutex);
    // m_myPool->m_cond.wait(lock);
    // m_myPool.m_semaphore.wait();
    m_myPool.m_init_sem.wait();

    m_state = RUN;

    while (RUN == this->m_state)
    {
        TASK_PTR task_ptr(new Task(DefaultFunc));
        PriorityAndTask to_pop(MIDDLE, task_ptr);

        if (1 == m_myPool.m_tasks.Pop(to_pop,
                                      TASKS_QUQUE::Millisec(5000))) // 5 seconds
        {
            to_pop.second->operator()();
        }
        else // Queue is empty
        {
            ;
        }
    }
    // std::cout << "this is  : " << this;
    sleep(1);
    m_myPool.joining_queue.push(this->GetID());
    m_myPool.m_semaphore.post();

    --m_myPool.m_num_threads;
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
    // ActiveThread* thread = NULL;
    ActiveThread* thread;
    for (size_t i = 0; i < num_of_threads; ++i)
    {
        LOG_DEBUG(__FILE__ +
                  std::string("::ThreadInit():creating active thread"));
        try
        {
            // thread = new ActiveThread(*this);
            // ActiveThreadPtr thread(new ActiveThread(*this));
            thread = new ActiveThread(*this);
        }
        catch (...)
        {
            LOG_ERROR(
                __FILE__ +
                std::string(
                    "::TrheadInit: ERROR in new ActiveThread allocation"));

            std::cout << " cought an error in creating an active thread "
                      << std::endl;
        }
        // std::cout << "heap adress is " << thread.get();
        // m_callbacks.insert(
        //     std::make_pair(boost::this_thread::get_id(),
        //                    boost::bind(&ActiveThread::StopRunning, thread)));

        // m_threads.push_back(thread);
        thread->StartThread();
        m_threads.insert(std::make_pair(thread->GetID(), thread));

        ++this->m_num_threads;
    }
}

////////////////////////////////////////////////////////////////////////////////

ThreadPool::ThreadPool(size_t num_of_threads)
    : m_num_threads(0), m_semaphore(0), m_init_sem(0)
{
    // Initialize as many threads as the user requested and place them inside
    LOG_DEBUG(__FILE__ + std::string("::ThreadPool()"));
    std::cout << "ThreadPool - ctor" << std::endl;

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
        m_init_sem.post();
    }
    // sleep(1);
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::AddTask(TASK_PTR task, int priority)
{
    // Add the new task to the waitable queue:
    // m_tasks.Push(std::make_pair(task, priority));
    m_tasks.Push(PriorityAndTask(priority, task));
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::KillThread()
{
    // m_callbacks.find(boost::this_thread::get_id())->second();
    std::map< boost::thread::id, ActiveThreadPtr >::iterator id =
        m_threads.find(boost::this_thread::get_id());

    if (id != m_threads.end())
    {
        id->second->SetFlag(ActiveThread::STOP);
    }
    else
    {
        // LOG
        std::cout << "whoops, id didn't work :(" << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////

void ThreadPool::SetThreadsAmount(size_t new_amount)
{
    LOG_DEBUG(__FILE__ + std::string("::SetThreadsAmount() entering function"));
    ssize_t amount_to_change = new_amount - m_num_threads;

    if (0 == amount_to_change)
    {
        ;
        LOG_DEBUG(__FILE__ +
                  std::string(
                      "::SetThreadsAmount() - no change in amout was needed"));
    }
    else if (amount_to_change > 0)
    {
        // Create amount_to_change more threads in the thread pool:
        ssize_t i = amount_to_change;
        for (; i > 0; --i)
        {
            m_init_sem.post();
        }

        ThreadsInit(amount_to_change);
    }
    else
    {
        // Delete amount_to_change more threads in the thread pool:
        // push to the task queue amount_to_change quantity of mission to delete
        // a thread:

        // make_shared is like a "new" to shared pointer.
        TASK_PTR task_ptr(boost::make_shared< Task >(
            boost::bind(&ThreadPool::KillThread, this)));

        PriorityAndTask to_push((LOW + 1), task_ptr);

        size_t amount_to_delete = (amount_to_change * (-1));
        while (amount_to_change < 0)
        {
            m_tasks.Push(to_push);

            ++amount_to_change;
        }

        boost::thread::id thread_to_delete;
        while (amount_to_delete)
        {
            m_semaphore.wait();
            thread_to_delete = joining_queue.front();
            joining_queue.pop();

            static int i = 1;
            std::cout << "i = " << i++ << std::endl;

            m_threads.find(thread_to_delete)->second->JoinThread();
            // thread_to_delete->JoinThread();
            m_threads.erase(thread_to_delete);
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
    m_cond.notify_all(); // CHANGE TO POST WITH A SWMAPHORE
}

////////////////////////////////////////////////////////////////////////////////

size_t ThreadPool::GetAmountOfThreads()
{
    return (m_num_threads);
}
