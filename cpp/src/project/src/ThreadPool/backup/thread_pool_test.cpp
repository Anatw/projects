///////////////////////////////////////////////////////////////////////BS"S**///
//	Title:		Thread Pool
//	Authour:	Shmuel Sinder
//	Reviewer:	
//	Version:	01.09.2020.0
 ///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cassert>

#include "thread_pool.hpp"

using namespace ilrd;

void Foo()
{
    static int i = 0;
    std::cout << "foooo" << ++i << std::endl;
}

void Test1()
{
    ThreadPool::Task task(Foo);
    task();
}

void Test2()
{
    ThreadPool threadpool(5);

    boost::shared_ptr<ThreadPool::Task> task( new  ThreadPool::Task(Foo));

    ThreadPool::Task tmp_task = *task;

    threadpool.AddTask(task);
    threadpool.AddTask(task);
    threadpool.AddTask(task);
    threadpool.AddTask(task);

    sleep(10);
}

void Test3()
{
    ThreadPool threadpool(5);

    boost::shared_ptr<ThreadPool::Task> task( new  ThreadPool::Task(Foo));

    threadpool.AddTask(task);
    threadpool.AddTask(task);

    sleep(1);
    threadpool.Pause();
    sleep(1);

    threadpool.AddTask(task);
    threadpool.AddTask(task);

    threadpool.Resume();

    sleep(10);
}

void Test4()
{
    ThreadPool threadpool(3);

    sleep(5);

    threadpool.SetThreadsAmount(5);

    sleep(5);

    threadpool.SetThreadsAmount(2);

    sleep(10);
}

void Foo1()
{
    std::cout << "LOW\n";
}

void Foo2()
{
    std::cout << "MIDDLE\n";
}

void Foo3()
{
    std::cout << "HIGH\n";
}

void Test5()
{
    ThreadPool threadpool(1);

    boost::shared_ptr<ThreadPool::Task> task1( new  ThreadPool::Task(Foo1));
    boost::shared_ptr<ThreadPool::Task> task2( new  ThreadPool::Task(Foo2));
    boost::shared_ptr<ThreadPool::Task> task3( new  ThreadPool::Task(Foo3));

    threadpool.AddTask(task1, ThreadPool::LOW);
    threadpool.AddTask(task2, ThreadPool::MIDDLE);
    threadpool.AddTask(task3, ThreadPool::HIGH);

    sleep(10);
}


int main()
{
    // Test1();
    // Test2();
    // Test3();
    // Test4();
    Test5();
    
    return 0;
}