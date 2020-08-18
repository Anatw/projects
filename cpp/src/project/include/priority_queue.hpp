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

#ifndef __ILRD_RD8586_PRIORITY_QUEUE_HPP_
#define __ILRD_RD8586_PRIORITY_QUEUE_HPP__

#include <iostream>
#include <queue>
#include <vector>

namespace ilrd
{
template < typename T, class Container = std::vector< T >,
           class Compare = std::less< typename Container::value_type > >
class PriorityQueue : private std::priority_queue< T, Container, Compare >
{
public:
    explicit PriorityQueue(const Compare& comp = Compare(),
                           const Container& ctnr = Container())
        : PriorityQueue::priority_queue(comp, ctnr)
    {
    }

    template < class InputIterator >
    PriorityQueue(InputIterator first, InputIterator last,
                  const Compare& comp = Compare(),
                  const Container& ctnr = Container())
        : PriorityQueue::priority_queue(first, last, comp, ctnr)
    {
    }

    void push(const T& val);
    void pop(void);
    const T& front() const;
    bool empty() const;
};

template < typename T, class Container, class Compare >
void PriorityQueue< T, Container, Compare >::push(const T& val)
{
    PriorityQueue::priority_queue::push(val);
}

template < typename T, class Container, class Compare >
void PriorityQueue< T, Container, Compare >::pop(void)
{
    PriorityQueue::priority_queue::pop();
}

template < typename T, class Container, class Compare >
const T& PriorityQueue< T, Container, Compare >::front() const
{
    return (PriorityQueue::priority_queue::top());
}

template < typename T, class Container, class Compare >
bool PriorityQueue< T, Container, Compare >::empty() const
{
    return (PriorityQueue::priority_queue::empty());
}

} // namespace ilrd

#endif /* __ILRD_RD8586_PRIORITY_QUEUE_HPP__ */
