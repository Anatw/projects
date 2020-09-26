/*******************************************************************************
Thread Pool test file

Written by Anat Wax, anatwax@gmail.com
Created: 3.9.20
Reviewer: Daria Korotkova
*******************************************************************************/
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream> // cout, cin, cerr
#include <queue>
#include <vector>

#include "thread_pool.hpp"

using namespace ilrd;

void DoSomething()
{
    std::cout << "Something" << std::endl;
    static int i = 1;
    std::cout << i++ << std::endl;
}

void IncreaseAmountOfThreads(ThreadPool& pool)
{
    pool.SetThreadsAmount(15);
}

void DencreaseAmountOfThreads(ThreadPool& pool)
{
    pool.SetThreadsAmount(5);
}

#define NUM_THREADS (3)

int main()
{
    ThreadPool::ActionFunc func(DoSomething);
    ThreadPool::TASK_PTR task_ptr(new ThreadPool::Task(func));

    ThreadPool pool(NUM_THREADS);
    for (int counter = NUM_THREADS; counter; --counter)
    {
        pool.AddTask(task_ptr, ThreadPool::HIGH);
    }

    std::cout << "number of threads in the thread pool is: "
              << pool.GetAmountOfThreads() << std::endl;

    pool.Start();
    pool.Pause();
    sleep(3);
    pool.Resume();

    sleep(3);

    DencreaseAmountOfThreads(pool);

    std::cout << "Dencreased amount of threads to 5 - number of threads in the"
                 "thread pool is: "
              << pool.GetAmountOfThreads() << std::endl;

    // pool.Stop();

    IncreaseAmountOfThreads(pool);
    sleep(3);
    for (int counter = 10; counter; --counter)
    {
        pool.AddTask(task_ptr);
    }

    std::cout << "Increased amount of threads to 15 - number of threads in the "
                 "thread pool is: "
              << pool.GetAmountOfThreads() << std::endl;

    for (int counter = 5; counter; --counter)
    {
        pool.AddTask(task_ptr);
    }
    for (int counter = 15; counter; --counter)
    {
    }

    pool.Stop();

    return (0);
}
