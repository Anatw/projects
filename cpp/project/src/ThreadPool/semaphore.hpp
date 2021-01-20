/*******************************************************************************
Taken from here (on 9.9.20):
https://stackoverflow.com/questions/4792449/c0x-has-no-semaphores-how-to-synchronize-threads
*******************************************************************************/

#ifndef __ILRD_RD8586_SEMAPHORE_HPP_
#define __ILRD_RD8586_SEMAPHORE_HPP_

#include <boost/thread/mutex.hpp>

#include "singleton.hpp"

namespace ilrd
{

class Semaphore
{
private:
    boost::mutex mutex_;
    boost::condition_variable condition_;
    unsigned long count_ = 0; // Initialized as locked.

public:
    void post()
    {
        boost::lock_guard< boost::mutex(mutex_) > lock(mutex_);
        ++count_;
        condition_.notify_one();
    }

    void wait()
    {
        boost::unique_lock< boost::mutex(mutex_) > lock(mutex_);
        while (!count_) // Handle spurious wake-ups.
        {
            condition_.wait(lock);
        }

        --count_;
    }

    bool try_wait()
    {
        boost::lock_guard< boost::mutex(mutex_) > lock(mutex_);
        if (count_)
        {
            --count_;

            return true;
        }

        return false;
    }
};

} // namespace ilrd

#endif /* __ILRD_RD8586_SEMAPHORE_HPP_s */
