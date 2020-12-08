/*******************************************************************************
 * File: Thread_pool.hpp - 	header file			  				 		       *
 * Author: Yonathan Naor                                          			   *
 * Reviewed by: 				                                   			   *
 * Date: 		                                                           	   *
 ******************************************************************************/

#ifndef ILRD_RD8586_THREAD_POOL_HPP
#define ILRD_RD8586_THREAD_POOL_HPP

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <map>
#include <queue>
#include <vector>

#include "priority_queue.hpp"
#include "waiting_queue.hpp"

////////////////////////////////////////////////////////////////////////////////
// ThreadPool class is not thread safe - meaning that the methods of this object
// should be call from a single thread
////////////////////////////////////////////////////////////////////////////////

namespace ilrd
{

class ThreadPool : private boost::noncopyable
{
public:
    typedef boost::function< void() > ActionFunc; // function to execute
    enum Priority // enum for priority of execution
    {
        HIGH = 1,
        MIDDLE,
        LOW
    };

    class Task // nested class task for the user to use for the ThreadPool
               // methods
    {
    public:
        Task() : m_exec_func(boost::bind(&ThreadPool::Task::EmptyFunc, this))
        {
        }
        Task(ActionFunc func) : m_exec_func(func)
        {
        }
        virtual ~Task();
        virtual void operator()();

    private:
        void EmptyFunc();
        ActionFunc m_exec_func;
    };

    typedef boost::shared_ptr< ThreadPool::Task > taskPtr;
    ////////////////////////////////////////////////////////////////////////////
    //                             PUBLIC METHODS
    // CTOR
    // num_of_thread - is the num of threads that shell be created when start
    // function
    // will be called
    explicit ThreadPool(size_t num_of_threads);

    // DTOR
    ~ThreadPool();

    // Addtask to tasks queue
    // taskPtr is a shared ptr to a task object
    void AddTask(taskPtr task, ThreadPool::Priority priority = MIDDLE);

    // Start - will start the running of the threads for the first time
    void Start();

    // set amount will set new amount of threads- no need to call start after
    // calling set amount
    // if set amount was called with(0) while ThreadsPool is paused  resume will
    // be called from with in set amount;
    void SetThreadsAmount(size_t new_amount); // Set a new amount of threads

    // Pauses all threads after executing the current task
    // if no task is executed by a thread it will paused imidiatly
    void Pause(); // Pause all threads

    // resumes all paused threads to work
    void Resume(); // Resume all threads to work again

    // terminats all threads after executing all tasks in queue
    void Stop();
    //                              END OF PUBLIC METHODS
    ////////////////////////////////////////////////////////////////////////////////

private: // this private section includes the clasess ActiveThread & QueueWraper
         // as friends in also includes the CompareFunc class definition
    typedef std::pair< int, taskPtr > PriorityAndTask;
    class QueuesWraper;
    friend class QueuesWraper;

    // nested class functior CompFunc
    class CompareFunc
    {
    public:
        bool operator()(const PriorityAndTask task1,
                        const PriorityAndTask task2);
    };
    class ActiveThread;
    friend class ActiveThread;

    // nested class QueueWraper- interface between the an ActiveThread and a
    // Threadpool
    class QueuesWraper
    {
        typedef std::pair< int, ThreadPool::taskPtr > priorty_and_task_t;
        typedef ThreadPool::ActiveThread* active_thread_ptr_t;
        typedef WaitableQueue< PriorityQueue< priorty_and_task_t,
                                              std::vector< priorty_and_task_t >,
                                              ThreadPool::CompareFunc >,
                               priorty_and_task_t >
            tasks_queue_t;
        typedef WaitableQueue< std::queue< active_thread_ptr_t >,
                               active_thread_ptr_t >
            deleting_queue_t;

    public:
        QueuesWraper(tasks_queue_t* tasks_queue,
                     deleting_queue_t* deleting_queue)
            : m_tasks_queue(tasks_queue), m_deleting_queue(deleting_queue)

        {
        }
        bool PopTask(priorty_and_task_t& task,
                     tasks_queue_t::Millisec wating_time);
        void PushActive(active_thread_ptr_t thread);

    private:
        tasks_queue_t* m_tasks_queue;
        deleting_queue_t* m_deleting_queue;
    };

    // nested class ActiveThread- an active object represents a thread
    class ActiveThread
    {

    public:
        ActiveThread(ThreadPool::QueuesWraper* pool)
            : myPool(pool), to_run(RUN),
              m_thread(boost::bind(&ActiveThread::ThreadFunc, this))

        {
        }
        ~ActiveThread();
        enum ToRun
        {
            STOP = 0,
            RUN
        };

        void StopRunning();
        boost::thread::id GetID();

    private:
        QueuesWraper* myPool;
        bool to_run;
        void ThreadFunc();
        boost::thread m_thread;
    };

private: // this private section includes all internal methods and variables of
         // ThreadPool calss
    // typedef boost::shared_ptr< ThreadPool::ActiveThread > ActiveThreadPtr;
    typedef std::pair< boost::thread::id, boost::function< void() > >
        IdAndCallback;

    WaitableQueue<
        PriorityQueue< PriorityAndTask, std::vector< PriorityAndTask >,
                       ThreadPool::CompareFunc >,
        PriorityAndTask >
        m_tasks;
    WaitableQueue< std::queue< ActiveThread* >, ActiveThread* > JoiningQueue;
    size_t m_init_num_of_threads;
    size_t m_numOfThreads;
    int is_paused;
    QueuesWraper m_wraper;
    void ThreadsInit(size_t num_fo_threads);
    std::map< boost::thread::id, boost::function< void(void) > > m_callbacks;
    void KillThread();
    void PauseThread();
};
boost::condition_variable cv_pause;
boost::mutex mutex_pause;

////////////////////////////////////////////////////////////////////////////////
///   inline functions implementation   ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace ilrd

#endif /* ILRD_RD8586_THREAD_POOL_HPP */
