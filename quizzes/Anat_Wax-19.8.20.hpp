/*******************************************************************************
Implement a class SmartLock that blocks threads from continuing until all the
threads reached the lock. When last thread locks all the threads are released.

Number of threads will be determined in the ctor.

Real life example:
Let's say a nuclear bomb needs to be dropped, it has to get 4 signatures, prime
minister, president, main engineer, and myself. The order of signatures is not
important but after last one signs the bomb will be launched.


Written by Anat Wax, anatwax@gmail.com
Created: 19.8.20
*******************************************************************************/

#ifndef __ILRD_RD8586__HPP_
#define __ILRD_RD8586__HPP__

#include <atomic>
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <condition_variable>

namespace ilrd
{
template < class FUNC >
class SmartLock : private boost::noncopyable
{
public:
    SmartLock(int num_threads) : m_num_threads(num_threads)
    {
    }

    void Activate(FUNC func);
    void CheckIn();

    inline size_t GetNumThreadsCheckedIn()
    {
        boost::unique_lock< boost::mutex > lock(m_mutex);
        return (m_num_checked_in);
    }

private:
    int m_num_threads;
    static int m_is_ready;
    boost::condition_variable m_flag;
    boost::mutex m_lock;
    std::atomic< int > m_num_checked_in;
};

template < class FUNC >
int SmartLock< FUNC >::m_is_ready = false;

template < class FUNC >
void SmartLock< FUNC >::Activate(FUNC func)
{
    boost::unique_lock< boost::mutex > lock(m_lock);

    while (__atomic_fetch_and(&m_is_ready, false, __ATOMIC_SEQ_CST))
    {
        m_flag.wait(lock);
    }

    (*FUNC)(); // executing the functor
}

template < class FUNC >
void SmartLock< FUNC >::CheckIn()
{
    ++m_num_checked_in;

    if (m_num_checked_in == m_num_threads)
    {
        m_lock.unlock();

        m_is_ready.notify_all;
    }
}

} // namespace ilrd

#endif /* __ILRD_RD8586__HPP__ */
