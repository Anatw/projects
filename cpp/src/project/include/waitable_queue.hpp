/*******************************************************************************
Waitable queue is a thread safe queue
Written by Anat Wax, anatwax@gmail.com
Created: 11.8.20
Reviewer: Haim Sa'adia

compile with -lboost_system -lboost_chrono -lpthread -lboost_thread
[
    pd waitable_queue.hpp waitable_queue_test.cpp -lboost_system -lboost_chrono
-lpthread -lboost_thread -lboost_thread
]
*******************************************************************************/
#ifndef __ILRD_RD8586_WAITABLE_QUEUE_HPP__
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
    void Pop(T& peaked_value);

    // will use front and pop
    // if the queue is empty the thread will be blocked for a defined amount of
    // time.
    bool Pop(T& peaked_value, Millisec timeout);

    bool Empty();

    inline size_t GetQueueSize()
    {
        boost::unique_lock< boost::mutex > lock(m_mutex);
        return (m_queue.size());
    }

private:
    QUEUE m_queue;
    boost::condition_variable m_pushflag;
    boost::mutex m_mutex;
}; // namespace ilrd

template < class QUEUE, typename T >
void WaitableQueue< QUEUE, T >::Push(const T& val)
{
    // the scoped_lock is automatically unlock when is out of scope
    boost::unique_lock< boost::mutex > lock(m_mutex);

    // if the queue was empty, than the condition variable should be notified -
    // in order to wake a sleeping thread on the pop() method (if there are any
    // there...)
    bool const was_empty = m_queue.empty();

    m_queue.push(val);

    // unlocking here so that if a thread is beeing waked up, it will be able to
    // lock the mutex
    lock.unlock();

    // if (was_empty)
    // {
    //     m_pushflag.notify_one();
    // }
    m_pushflag.notify_one();
}

template < class QUEUE, typename T >
void WaitableQueue< QUEUE, T >::Pop(T& peaked_value)
{
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
    boost::unique_lock< boost::mutex > lock(m_mutex);
    boost::system_time this_time = boost::get_system_time() + timeout;

    while (m_queue.empty())
    {
        // boost::systemtime
        if (!m_pushflag.timed_wait(lock, this_time))
        {
            return false;
        }
    }

    peaked_value = m_queue.front();
    m_queue.pop();

    return true;
}
template < class QUEUE, typename T >
bool WaitableQueue< QUEUE, T >::Empty()
{
    boost::unique_lock< boost::mutex > lock(m_mutex);

    return (m_queue.empty());
}

} // namespace ilrd

#endif /* __ILRD_RD8586_WAITABLE_QUEUE_HPP__ */
