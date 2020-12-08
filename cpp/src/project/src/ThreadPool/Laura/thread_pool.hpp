/*
 * =============================================================================
 *
 *       Filename: threadpool.hpp
 *
 *    Description:  header file for threadpool design pattern
 *        Created:  12/07/2020
 *
 *         Author:  Tehila Berdah (TB), laura.berdah@gmail.com
 *
 * =============================================================================
 */

#ifndef ILRD_RD8586_THREAD_POOL_HPP
#define ILRD_RD8586_THREAD_POOL_HPP

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <map>
#include <queue>
#include <vector>

#include "logger.hpp"
#include "priority_queue.hpp"
#include "waitable_queue.hpp"

namespace ilrd
{

class ThreadPool : private boost::noncopyable
{
    typedef boost::function< void(void) > ActionFunc;

public:
    enum Priority
    {
        HIGH = 1,
        MIDDLE,
        LOW
    };

    class Task
    {
    public:
        Task(ActionFunc func = &DoNothing) : m_exec_func(func)
        {
        }
        virtual ~Task();
        virtual void operator()();

    private:
        ActionFunc m_exec_func;
    };

    explicit ThreadPool(size_t num_of_threads);
    ~ThreadPool();
    void Start();
    void InitThreads(size_t num);
    void AddTask(boost::shared_ptr< ThreadPool::Task > task,
                 ThreadPool::Priority priority = MIDDLE);
    bool SetThreadsAmount(size_t new_amount); // Set a new amount of threads
    void Stop();                              // Exits all threads
    void Pause();                             // Pause all threads
    void Resume(); // Resume all threads to work again

    size_t GetAmountOfThreads();

private:
    class ActiveThread;
    typedef boost::shared_ptr< ThreadPool::ActiveThread > ActiveThreadPtr;
    typedef std::pair< int, boost::shared_ptr< ThreadPool::Task > >
        PriorityAndTask;

    size_t m_numOfThreads;

    class ActiveThread
    {
    public:
        ActiveThread(ThreadPool& tp);
        ~ActiveThread(); // Don't forget to join the m_thread so the task will
                         // be finished before destruction
        enum ToRun
        {
            STOP = 0,
            RUN
        };

        void StartThread();
        boost::thread::id GetID();
        void PopAndExecute(); // Popping the task from queue and execute
        void SetFlag(const bool _x)
        {
            m_flag = _x;
        }
        bool GetFlag() const
        {
            return m_flag;
        }
        void JoinThread();

    private:
        boost::thread m_thread;
        ThreadPool& m_threadpool;
        bool m_flag;
    };

    std::map< boost::thread::id, ActiveThreadPtr > m_running_threads;
    std::queue< boost::thread::id > m_joining_queue;

    struct Compare
    {
        bool operator()(PriorityAndTask a, PriorityAndTask b)
        {
            return (a.first > b.first);
        }
    };

    WaitableQueue< PriorityQueue< PriorityAndTask,
                                  std::vector< PriorityAndTask >, Compare >,
                   PriorityAndTask >
        m_tasks;
    boost::condition_variable m_cond;
    boost::mutex m_pause_mutex;
    boost::interprocess::interprocess_semaphore m_stop_semaphore;
    boost::interprocess::interprocess_semaphore m_pause_semaphore;
    bool m_paused;
    static void DoNothing()
    {
    }
    void StopTaskfromPool();
    void JoinAll();
    void PauseTaskfromPool();
};

} // namespace ilrd

#endif // ILRD_RD8586_THREAD_POOL_HPP
