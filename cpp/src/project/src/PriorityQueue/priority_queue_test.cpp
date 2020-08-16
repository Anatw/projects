/*******************************************************************************
Priority queue

* We will wrap std::priority_queue with our own class in a way that fits the
* WaitableQueue.

* But instead of having std::priority_queue as a member we shall use private
* inheritance. Keeping all template functionality

Written by Anat Wax, anatwax@gmail.com
Created: 16.8.20
Reviewer: Shmuel Sinder
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "priority_queue.hpp"
#include "waitable_queue.hpp"

void BasicPQTest()
{
    ilrd::PriorityQueue< int > p_queue;
    p_queue.push(5);
    p_queue.push(3);
    p_queue.push(2);

    p_queue.pop();
}
void BasicWQPQTest()
{
    ilrd::WaitableQueue< ilrd::PriorityQueue< int >, int > wq;
    wq.Push(5);
    wq.Push(3);
    wq.Push(7);
    wq.Push(2);

    int val = 0;
    while (!wq.Empty())
    {
        wq.Pop(val);
        std::cout << val << std::endl;
    }
}

int main()
{
    BasicPQTest();
    BasicWQPQTest();

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
