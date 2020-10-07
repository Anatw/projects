/*******************************************************************************
 * File: thread_pool.cpp - operation funcs					 				   *
 * Author: Yonathan Naor                                            		   *
 * Reviewed by: 				                                   			   *
 * Date: 		                                                           	   *
 ******************************************************************************/

#include <boost/atomic.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread/locks.hpp>
#include <cassert>
#include <iostream>

#include "logger.hpp"
#include "thread_pool.hpp"

using namespace ilrd;

////////////////////////////////////////////////////////////////////////////////
//                   ThreadPool::TASK
//                        DTOR
////////////////////////////////////////////////////////////////////////////////
ThreadPool::Task::~Task()
{
}
////////////////////////////////////////////////////////////////////////////////
//                   ThreadPool::TASK
//                        operator()
////////////////////////////////////////////////////////////////////////////////
void ThreadPool::Task::operator()()
{
    this->m_exec_func();
}
////////////////////////////////////////////////////////////////////////////////
//                        ThreadPool
//                          CTOR
////////////////////////////////////////////////////////////////////////////////

// exception thrown from init function when bad allocation acurr
ThreadPool::ThreadPool(size_t num_of_threads)
    : m_init_num_of_threads(num_of_threads), m_numOfThreads(0), is_paused(0),
      m_wraper(&m_tasks, &JoiningQueue)
{
    LOG_DEBUG("ThreadPool::CTOR finished intialization");
}

////////////////////////////////////////////////////////////////////////////////
//                        ThreadPool
//                          AddTask
////////////////////////////////////////////////////////////////////////////////
void ThreadPool::AddTask(taskPtr task, ThreadPool::Priority priority)
{
    m_tasks.Push(PriorityAndTask(priority, task));
    LOG_DEBUG("ThreadPool::AddTask");
    std::cout << "ThreadPool::AddTask" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
//                        ThreadPool
//                      SetAmountOfThreads
////////////////////////////////////////////////////////////////////////////////

// Set a new amount of threads
void ThreadPool::SetThreadsAmount(size_t new_amount)
{
    LOG_DEBUG("ThreadPool::SetThreadsAmount");
    // new num of threads equals to the prev one no need to do anything
    if (new_amount == m_numOfThreads)
    {
        LOG_DEBUG("ThreadPool::SetThreadsAmount- no set needed");
        return;
    }
    //
    if (new_amount > m_numOfThreads)
    {
        size_t amount_to_set = new_amount - m_numOfThreads;
        LOG_DEBUG("ThreadPool::SetThreadsAmount- adding threads");

        ThreadsInit(amount_to_set);

        if (true == is_paused)
        {
            taskPtr task = boost::make_shared< Task >(
                boost::bind(&ThreadPool::PauseThread, this));
            PriorityAndTask to_push((HIGH - 1), task);
            for (size_t i = 0; i < amount_to_set; ++i)
            {
                LOG_DEBUG("ThreadPool::Pause- pushing pause tasks");
                m_tasks.Push(to_push);
            }
        }
    }
    else // reducing amount of threads
    {
        std::cout << "ThreadPool::SetThreadsAmount- reducing threads"
                  << std::endl;
        LOG_DEBUG("ThreadPool::SetThreadsAmount- reducing threads");

        size_t threads_to_stop = m_numOfThreads - new_amount;
        size_t counter = 0;
        boost::shared_ptr< Task > stop_task = boost::make_shared< Task >(
            boost::bind(&ThreadPool::KillThread, this));

        while (threads_to_stop > counter)
        {
            m_tasks.Push(PriorityAndTask(LOW + 1, stop_task));
            ++counter;
            std::cout << "ThreadPool::SetThreadsAmount- m_numOfThreads"
                      << m_numOfThreads << std::endl;
            --m_numOfThreads;
        }

        // killing all threads while paused- Resume must be called first
        if ((0 == new_amount) && (is_paused == true))
        {
            Resume();
        }

        // deleting all active threads
        ActiveThread* thread_ptr = NULL;
        for (; threads_to_stop > 0; --threads_to_stop)
        {
            LOG_DEBUG("ThreadPool::SetThreadsAmount- reducing threads waiting "
                      "on pop");
            std::cout << "ThreadPool::SetThreadsAmount- reducing threads "
                         "waiting on pop"
                      << std::endl;
            JoiningQueue.Pop(thread_ptr);
            delete thread_ptr;
            LOG_DEBUG(
                "ThreadPool::SetThreadsAmount- reducing threads after poped");
            std::cout
                << "ThreadPool::SetThreadsAmount- reducing threads after poped"
                << std::endl;
        }
        LOG_DEBUG("ThreadPool::SetThreadsAmount- reducing threads deleted all");
        std::cout
            << "ThreadPool::SetThreadsAmount- reducing threads deleted all"
            << std::endl;
    }
}
////////////////////////////////////////////////////////////////////////////////
//                        ThreadPool
//                          DTOR
////////////////////////////////////////////////////////////////////////////////
ThreadPool::~ThreadPool()
{
    LOG_DEBUG("ThreadPool::DTOR");
    cv_pause.notify_all();
    SetThreadsAmount(0);
}

////////////////////////////////////////////////////////////////////////////////
//                        ThreadPool
//                          Start
////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Start()
{
    LOG_DEBUG("ThreadPool::Start- calling SetAmount");
    SetThreadsAmount(m_init_num_of_threads);
}
////////////////////////////////////////////////////////////////////////////////
//                        ThreadPool
//                          Stop
////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Stop()
{
    LOG_DEBUG("ThreadPool::Stop");
    SetThreadsAmount(0);
}

////////////////////////////////////////////////////////////////////////////////
//                        ThreadPool
//                        Threads Init
////////////////////////////////////////////////////////////////////////////////
// privte function to create new ActiveThreads and push<m_thread::id,
//&callback>
// to the map
// need to check if throwing exeption (boost::shared  boost ::thread)

void ThreadPool::ThreadsInit(size_t num_of_threads)
{
    LOG_DEBUG("ThreadPool::TrheadInit");
    size_t counter = 0;
    ActiveThread* active_thread_ptr = NULL;
    while (counter < num_of_threads)
    {
        LOG_DEBUG("ThreadPool::ThreadInit-creating active thread");
        try
        {
            active_thread_ptr = new ThreadPool::ActiveThread(&m_wraper);
        }
        catch (...)
        {
            LOG_ERROR("ThreadPool::TrheadInit- bad alloc");
            --m_numOfThreads;
        }
        m_callbacks.insert(IdAndCallback(
            active_thread_ptr->GetID(),
            boost::bind(&ActiveThread::StopRunning, active_thread_ptr)));
        ++m_numOfThreads;
        ++counter;
    }
}
////////////////////////////////////////////////////////////////////////////////
//                        ThreadPool
//                        KillThreads
////////////////////////////////////////////////////////////////////////////////

// privste function that is used to invoke a callback(Active Thread stop
// function) for a registerd ActiveMap that should be terminated
// it is used in Set AMount Of Threads

void ThreadPool::KillThread()
{
    assert(m_callbacks.find(boost::this_thread::get_id()) != m_callbacks.end());

    m_callbacks.find(boost::this_thread::get_id())->second();

    std::cout << "found it" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
//                              ThreadPool
//                        Functor CompareFunc
////////////////////////////////////////////////////////////////////////////////

// is used as a compare function in the task queue

bool ThreadPool::CompareFunc::operator()(const PriorityAndTask task1,
                                         const PriorityAndTask task2)
{
    if (task1.first > task2.first)
    {
        return (true);
    }
    else
        return (false);
}

////////////////////////////////////////////////////////////////////////////////
//                              ThreadPool
//                                 Pause
////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Pause()
{
    LOG_DEBUG("ThreadPool::Pause-in Pause");
    boost::unique_lock< boost::mutex > lock(mutex_pause);
    if (is_paused == false)
    {
        is_paused = true;
        lock.unlock();

        taskPtr task = boost::make_shared< Task >(
            boost::bind(&ThreadPool::PauseThread, this));
        PriorityAndTask to_push((HIGH - 1), task);
        for (size_t i = 0; i < m_numOfThreads; ++i)
        {
            LOG_DEBUG("ThreadPool::Pause- pushing pause tasks");
            m_tasks.Push(to_push);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
//                              ThreadPool
//                                Resume
////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Resume()
{
    LOG_DEBUG("ThreadPool::Resume-notifying all");
    boost::unique_lock< boost::mutex > lock(mutex_pause);
    is_paused = false;
    lock.unlock();
    cv_pause.notify_all();
}

////////////////////////////////////////////////////////////////////////////////
//                              ThreadPool
//                              PauseThread
////////////////////////////////////////////////////////////////////////////////

// private pause function will be pushed in a task for pausing a thread
/// used in Pause function
void ThreadPool::PauseThread()
{

    boost::unique_lock< boost::mutex > lock(mutex_pause);
    if (true == is_paused)
    {
        cv_pause.wait(lock);
    }
}

////////////////////////////////////////////////////////////////////////////////
//                   ThreadPool::ACTIVE THREAD
//                          Thread Func
////////////////////////////////////////////////////////////////////////////////

// thread function for all threads to be intialized with
void ThreadPool::ActiveThread::ThreadFunc(void)
{
    LOG_DEBUG("ActiveThread::ThreadFunc- in a new thread");

    WaitableQueue< std::queue< Task >, Task >::Millisec wating_time(2000);

    ThreadPool::PriorityAndTask new_task;

    while (true == to_run)
    {

        if (myPool->PopTask(new_task, wating_time))
        {
            LOG_DEBUG("ActiveThread::ThreadFunc- calling new task");
            std::cout << "ThreadPool::ThreadFunc - calling new task"
                      << std::endl;
            new_task.second->operator()();
        }
    }

    myPool->PushActive(this);

    LOG_DEBUG("ThreadPool::ThreadFunc - exited while loop");
    std::cout << "ThreadPool::ThreadFunc - exited while loop" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
//                   ThreadPool::ACTIVE THREAD
//                              DTOR
////////////////////////////////////////////////////////////////////////////////

ThreadPool::ActiveThread::~ActiveThread()
{
    LOG_DEBUG("ThreadPool::ActiveThread::~ActiveThread");
    m_thread.join();
}
////////////////////////////////////////////////////////////////////////////////
//                   ThreadPool::ACTIVE THREAD
//                          StopRunning
////////////////////////////////////////////////////////////////////////////////

void ThreadPool::ActiveThread::StopRunning()
{
    std::cout << "in stop" << std::endl;
    to_run = STOP;
}

////////////////////////////////////////////////////////////////////////////////
//                   ThreadPool::ACTIVE THREAD
//                          GetID
////////////////////////////////////////////////////////////////////////////////
boost::thread::id ThreadPool::ActiveThread::GetID()
{
    return (m_thread.get_id());
}

////////////////////////////////////////////////////////////////////////////////
//                   ThreadPool::QueuesWraper
//                               PopTask
////////////////////////////////////////////////////////////////////////////////
bool ThreadPool::QueuesWraper::PopTask(PriorityAndTask& task,
                                       tasks_queue_t::Millisec wating_time)
{
    return (m_tasks_queue->Pop(task, wating_time));
}

////////////////////////////////////////////////////////////////////////////////
//                   ThreadPool::QueuesWraper
//                          PushActive
////////////////////////////////////////////////////////////////////////////////
void ThreadPool::QueuesWraper::PushActive(active_thread_ptr_t thread)
{
    m_deleting_queue->Push(thread);
}
