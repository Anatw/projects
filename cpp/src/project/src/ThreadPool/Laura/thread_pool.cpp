
/*
 * =============================================================================
 *
 *       Filename:  thread_pool.cpp
 *
 *    Description:  cpp file for threadpool
 *        Created:  12/07/2020
 *
 *         Author:  Tehila Berdah (TB), laura.berdah@gmail.com
 *
 * =============================================================================
 */

#include <boost/make_shared.hpp>

#include "logger.hpp"
#include "thread_pool.hpp"

namespace ilrd
{

/*******TASK ***************************************************************/
void ThreadPool::Task::operator()()
{
    m_exec_func();
}

ThreadPool::Task::~Task()
{
}

/*******ACTIVETHREAD
 * ***************************************************************/
ThreadPool::ActiveThread::ActiveThread(ThreadPool& tp) : m_threadpool(tp)
{
    std::cout << "ACTIVE THREAD constructor "
              << "\n";
    m_thread = boost::thread((boost::bind(&ActiveThread::PopAndExecute, this)));
}

ThreadPool::ActiveThread::~ActiveThread()
{
    std::cout << "DESTRUCTOR of the active thread\n";
}

boost::thread::id ThreadPool::ActiveThread::GetID()
{
    return m_thread.get_id();
}

void ThreadPool::ActiveThread::JoinThread()
{
    m_thread.join();
}

void ThreadPool::ActiveThread::PopAndExecute()
{
    m_flag = true;

    std::cout << "waou I am starting my execution thread"
              << boost::this_thread::get_id() << "\n";

    std::cout << "*this" << this << "\n";

    while (m_flag)
    {
        Task to_fill(&DoNothing);
        boost::shared_ptr< ThreadPool::Task > new_task(new Task(&DoNothing));
        PriorityAndTask task = std::make_pair(MIDDLE, new_task);
        bool ret = m_threadpool.m_tasks.Pop(
            task, boost::posix_time::milliseconds(4000));

        if (ret)
        {
            std::cout << "i popped a function and about to execute it\n";
            (*task.second)();
        }
    }

    std::cout << "out of the while loop\n";

    // push himself into the joining queue
    m_threadpool.m_joining_queue.push(boost::this_thread::get_id());

    m_threadpool.m_stop_semaphore.post();
}

/*******THREAD POOL**********************************************************/

ThreadPool::ThreadPool(size_t num_of_threads)
    : m_numOfThreads(num_of_threads), m_stop_semaphore(0)
{
    std::cout << "constructing the threadpool\n";
}

ThreadPool::~ThreadPool()
{
    std::cout << "about to destroy the threadpool\n";
    this->Stop();
}

void ThreadPool::InitThreads(size_t num)
{
    while (num)
    {
        std::cout << "counter :" << num << "\n";
        std::cout << "creation de pointeur : en cours\n";
        ActiveThreadPtr new_active_thread(new ActiveThread(*this));
        std::cout << "creation de pointeur : terminee et start en cours\n";
        std::cout << "start : terminee\n";
        std::cout << "pointeur dans pool" << new_active_thread.get() << "\n";
        m_running_threads.insert(
            std::pair< boost::thread::id, ActiveThreadPtr >(
                new_active_thread->GetID(), new_active_thread));
        --num;
    }
}

void ThreadPool::Start()
{
    InitThreads(m_numOfThreads);
}

void ThreadPool::AddTask(boost::shared_ptr< ThreadPool::Task > task,
                         ThreadPool::Priority priority)
{
    std::cout << "task " << task.get() << " is added\n";
    m_tasks.Push(PriorityAndTask(priority, task));
}

bool ThreadPool::SetThreadsAmount(size_t new_amount)
{
    // if user shrinks the amount of threads
    if (new_amount < m_numOfThreads)
    {
        int dif = m_numOfThreads - new_amount;

        boost::shared_ptr< ThreadPool::Task > stop_task(
            new Task(boost::bind(&ThreadPool::StopTaskfromPool, this)));

        while (dif)
        {
            std::cout << "pushing the stop task\n";
            m_tasks.Push(PriorityAndTask(LOW + 1, stop_task));
            m_stop_semaphore.wait();
            --dif;
        }

        // Join la joining queue
        JoinAll();
    }
    else // if user increases the amount of threads
    {
        InitThreads(new_amount - m_numOfThreads);
        m_numOfThreads = new_amount;
    }

    return true;
}

void ThreadPool::Stop()
{
    std::cout << "calling stop\n";
    this->SetThreadsAmount(0);
}

void ThreadPool::StopTaskfromPool()
{
    std::cout << "stoptask executing\n";
    // change the flag to false
    m_running_threads.find(boost::this_thread::get_id())
        ->second->SetFlag(false);

    // pusj the object in the joining queue
    // m_joining_queue.Push(m_running_threads.find(boost::this_thread::get_id())->second);
}

void ThreadPool::JoinAll()
{
    std::cout << "size of the joining queue is : " << m_joining_queue.size()
              << "\n";
    while (!m_joining_queue.empty()) // be careful !!! not threadsafe
    {
        boost::thread::id id = m_joining_queue.front();
        m_running_threads.find(id)->second->JoinThread();
        m_running_threads.erase(id);
        m_joining_queue.pop();
    }
}

void ThreadPool::Pause()
{
    m_paused = true;

    int counter = m_numOfThreads;

    boost::shared_ptr< ThreadPool::Task > pause_task(
        new Task(boost::bind(&ThreadPool::PauseTaskfromPool, this)));

    while (counter)
    {
        std::cout << "pushing the pause task\n";
        m_tasks.Push(PriorityAndTask(HIGH - 1, pause_task));
        --counter;
    }
}

void ThreadPool::PauseTaskfromPool()
{
    boost::unique_lock< boost::mutex > lock(m_pause_mutex);
    while (m_paused)
    {
        std::cout << "I am paused\n";
        m_cond.wait(lock);
    }
    std::cout << "going out of the pause\n";
}

void ThreadPool::Resume()
{
    boost::unique_lock< boost::mutex > lock(m_pause_mutex);
    m_paused = false;
    std::cout << "resume\n";
    m_cond.notify_all();
}

size_t ThreadPool::GetAmountOfThreads()
{
    return (m_numOfThreads);
}

} // namespace ilrd
