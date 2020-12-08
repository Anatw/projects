/*******************************************************************************
Thread Pool

Written by Anat Wax, anatwax@gmail.com
Created: 3.9.20
Reviewer: Daria Korotkova
*******************************************************************************/
#ifndef __ILRD_RD8586__HPP_
#define __ILRD_RD8586__HPP__

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <map>
#include <queue>
#include <vector>

#include "priority_queue.hpp"
#include "waitable_queue.hpp"

namespace ilrd
{

class ThreadPool : private boost::noncopyable
{
public:
    class Task;
    typedef boost::function< void(void) > ActionFunc;
    typedef boost::shared_ptr< ThreadPool::Task > TASK_PTR;

    enum Priority
    {
        HIGH = 1,
        MIDDLE,
        LOW
    };

    class Task
    {
    public:
        Task(ActionFunc func) : m_exec_func(func)
        {
        }
        virtual ~Task()
        {
        }
        virtual void operator()();

    private:
        ActionFunc m_exec_func;
    };

    explicit ThreadPool(size_t num_of_threads);
    ~ThreadPool();

    void SetThreadsAmount(size_t new_amount); // Set a new amount of threads
    size_t GetAmountOfThreads();

    void AddTask(TASK_PTR task, int priority = 2);

    void Start();
    void Pause();  // Pause all threads
    void Resume(); // Resume all threads to work again
    void Stop();

private:
    friend class ActiveThread;
    typedef std::pair< int, TASK_PTR > PriorityAndTask;

    size_t m_num_threads;
    // This map is m_callback bind to Stop() of Active Thread
    std::map< boost::thread::id, boost::function< void(void) > > m_callbacks;
    boost::condition_variable m_cond;
    boost::mutex m_pause_mutex;
    boost::interprocess::interprocess_semaphore m_semaphore;

    bool CompareFunc(PriorityAndTask, PriorityAndTask);
    void ThreadsInit(size_t num_fo_threads);
    void PauseThread();
    void KillThread();

private: //  ActiveThread
    // option  Active Object
    class ActiveThread
    {
    public:
        enum ToRun
        {
            STOP = 0,
            RUN
        };

        ActiveThread(ThreadPool& thread_pool);
        ~ActiveThread();

        void ThreadFunc();
        void StopRunning();

        bool m_state;

        boost::thread m_thread;
        ThreadPool& m_myPool;
    };

private:
    typedef boost::shared_ptr< ThreadPool::ActiveThread > ActiveThreadPtr;
    typedef std::pair< boost::thread::id, boost::function< void() > >
        IdAndCallback;

    struct Compare
    {
        bool operator()(PriorityAndTask a, PriorityAndTask b)
        {
            return (a.first > b.first);
        }
    };

    typedef WaitableQueue<
        PriorityQueue< PriorityAndTask, std::vector< PriorityAndTask >,
                       Compare >,
        PriorityAndTask >
        TASKS_QUQUE;

    TASKS_QUQUE m_tasks;

    // this queue is ment to push inside ActiveThread objects whos threads are
    // meant to be deleted:
    WaitableQueue< std::queue< ActiveThread* >, ActiveThread* > joining_queue;
};

} // namespace ilrd

#endif /* __ILRD_RD8586__HPP__ */
