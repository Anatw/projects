/*******************************************************************************
Waitable queue is a thread safe queue
Written by Anat Wax, anatwax@gmail.com
Created: 11.8.20
Reviewer: Haim Sa'adia

compile with -lboost_system -lboost_chrono -lpthread -lboost_thread
*******************************************************************************/
#include <queue>

#include "waitable_queue.hpp"

using namespace ilrd;
using namespace std;

WaitableQueue< queue< int >, int > q;

void AddToQueue()
{
    cout << "entring AddToQueue() [++]" << endl;
    static int i = 0;

    // for (int i = 0; i < 10; ++i)
    // {
    q.Push(i);
    // }
    ++i;
}

void PrintQueue()
{
    cout << "entring PrintQueue()" << endl;

    size_t size = q.GetQueueSize();
    int temp_value = 0;
    bool status = 0;

    for (size_t i = 0; i < size; ++i)
    {
        status =
            q.Pop(temp_value,
                  WaitableQueue< std::queue< int >, int >::Millisec(30001));
        if (status)
        {
            cout << temp_value << endl;
        }
    }
}

void PopWhenEmpty()
{
    int temp_val = 0;
    q.Pop(temp_val);
}

int main()
{
    int num_threads = 5;
    boost::thread inserter[5];

    boost::thread thread_to_stuck(PopWhenEmpty);
    // this will leace the program stuck because I'm
    // tryng to pop an empty queue:
    // thread_to_stuck.join();

    for (int i = 0; i < num_threads; ++i)
    {
        inserter[i] = boost::thread(AddToQueue);
    }

    boost::thread printer[2];
    for (int i = 0; i < 2; ++i)
    {
        printer[i] = boost::thread(PrintQueue);
    }

    for (int i = 0; i < num_threads; ++i)
    {
        inserter[i].join();
    }

    for (int i = 0; i < 2; ++i)
    {
        printer[i].join();
    }

    return (0);
}
