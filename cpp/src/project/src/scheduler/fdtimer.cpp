/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <iostream>   // cout, cin, cerr
#include <sys/time.h> // itimerspec
#include <sys/timerfd.h>
#include <unistd.h> // close()

#include "advanced_observer.hpp"
#include "fdtimer.hpp"

using namespace std;
using namespace ilrd;

FDTimer::FDTimer(Reactor& reactor, ActionFunc callback_func)
    : m_reactor(reactor), m_callback(callback_func),
      m_fd(timerfd_create(CLOCK_REALTIME, 0))
{
    m_reactor.Add(HandleAndMode(READ, m_fd), &m_callback);

    if (0 > m_fd)
    {
        throw runtime_error(
            "Error in creating a new fd using timerfd_create()");
    }
}

FDTimer::~FDTimer()
{
    close(m_fd);
}

void FDTimer::Set(MS microseconds)
{
    if (0 > microseconds.count())
    {
        microseconds = MS(1);
    }
    // itimerspec has within it two timespec struct and initializing to 0
    struct itimerspec temp_timer = {{0, 0}, {0, 0}};
    // timespec temp_timer = {0, 0};
    // converting microseconds to nanoseconds ( 1 second = 1000000
    // microseconds)
    temp_timer.it_value.tv_sec = microseconds.count() / 1000000;
    // converting microseconds to nanoseconds ( 1 microsecond = 1000
    // nanoseconds)
    temp_timer.it_value.tv_nsec = (microseconds.count() % 1000000) * 1000;

    if (0 > (timerfd_settime(m_fd, 0, &temp_timer, NULL)))
    {
        throw runtime_error("error in Set()");
    }
}

void FDTimer::Unset()
{
    // itimerspec has within it two timespec struct and initializing to 0
    struct itimerspec temp_timer = {{0, 0}, {0, 0}};

    // setting a timer to 0...
    if (0 > (timerfd_settime(m_fd, 0, &temp_timer, NULL)))
    {
        throw runtime_error("error in Unset()");
    }
}

////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
