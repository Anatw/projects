/*******************************************************************************
Waitable queue is a thread safe queue
Written by Anat Wax, anatwax@gmail.com
Created: 11.8.20
Reviewer: Haim Sa'adia

compile with -lboost_system -lboost_chrono -lpthread -lboost_thread
[
    pd waitable_queue.hpp waitable_queue_test.cpp -lboost_system -lboost_chrono
-lpthread -lboost_thread
]
*******************************************************************************/
#ifndef __ILRD_RD8586_WAITABLE_QUEUE_HPP_
#define __ILRD_RD8586_WAITABLE_QUEUE_HPP__

#include <boost/chrono.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>

namespace ilrd
{
template < class QUEUE, typename T >
class WaitableQueue : private boost::noncopyable
{
public:
    // typedef boost::chrono::milliseconds Millisec;
    typedef boost::posix_time::milliseconds Millisec;

    // default Ctor and Dtor

    void Push(const T& val);
    // If the queue is empty the thread will be blocked until a new data is
    // added to the queue - and than the data will be poped.

    void Pop(T& peaked_value); // will use front and pop
    // if the queue is empty the thread will be blocked for a defined amount of
    // time.

    bool Pop(T& peaked_value, Millisec timeout);

    bool Empty() const; // please make sur to use in a thread-safe environment

    size_t GetQueueSize();

private:
    QUEUE m_queue;
    boost::condition_variable m_pushflag; // use boost::unique_lock
    boost::mutex m_mutex;                 // use boost::unique_lock
};

template < class QUEUE, typename T >
size_t WaitableQueue< QUEUE, T >::GetQueueSize()
{
    return (m_queue.size());
}

template < class QUEUE, typename T >
void WaitableQueue< QUEUE, T >::Push(const T& val)
{
    // the scoped_lock is automatically unlock when is out of scope
    // boost::mutex::scoped_lock lock(m_mutex);
    boost::unique_lock< boost::mutex > lock(m_mutex);

    // if the queue was empty, than the condition variable should be notified -
    // in order to wake a sleeping thread on the pop() method (if there are any
    // there...)
    bool const was_empty = m_queue.empty();

    m_queue.push(val);

    // unlocking here so that if a thread is beeing waked up, it will be able to
    // lock the mutex
    lock.unlock();

    if (was_empty)
    {
        m_pushflag.notify_one();
    }
}

template < class QUEUE, typename T >
void WaitableQueue< QUEUE, T >::Pop(T& peaked_value)
{
    // boost::mutex::scoped_lock lock(m_mutex);
    boost::unique_lock< boost::mutex > lock(m_mutex);

    // lock the conditional variable while the queue is empty
    while (m_queue.empty())
    {
        // the wait unlocks the mutex until the conditional variable is
        // notified, and than lock the mutex again
        m_pushflag.wait(lock);
    }

    peaked_value = m_queue.front();
    m_queue.pop();
}
template < class QUEUE, typename T >
bool WaitableQueue< QUEUE, T >::Pop(T& peaked_value, Millisec timeout)
{
    // boost::system_time const time_to_wake = boost::get_system_time() +
    // timeout;

    // boost::system_time const time_to_wake =
    //     boost::get_system_time() + boost::posix_time::milliseconds(500);

    // boost::mutex::scoped_lock lock(m_mutex);
    boost::unique_lock< boost::mutex > lock(m_mutex);

    while (m_queue.empty())
    {
        // boost::systemtime
        if (!m_pushflag.timed_wait(lock, timeout))
        {
            return false;
        }

        // if (m_pushflag.wait_for(lock, timeout))
        // {
        //     return false;
        // }
    }

    peaked_value = m_queue.front();
    m_queue.pop();

    return true;
}
template < class QUEUE, typename T >
bool WaitableQueue< QUEUE, T >::Empty() const
{
    boost::unique_lock< boost::mutex > lock(m_mutex);

    return (m_queue.empty());
}

} // namespace ilrd

#endif /* __ILRD_RD8586_WAITABLE_QUEUE_HPP__ */
