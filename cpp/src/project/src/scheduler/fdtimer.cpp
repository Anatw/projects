/*******************************************************************************
fdtimer.hpp (part of the Scheduler design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 21.7.20
Reviewer: Kobi Rappaport
*******************************************************************************/
#include <boost/bind.hpp>
#include <iostream>   // cout, cin, cerr
#include <sys/time.h> // itimerspec
#include <sys/timerfd.h>
#include <unistd.h> // close()

#include "advanced_observer.hpp"
#include "fdtimer.hpp"

using namespace std;
using namespace ilrd;

FDTimer::FDTimer(Reactor& reactor, ActionFunc callback_func)
    : m_reactor(&reactor),
      m_callback(callback_func, boost::bind(&FDTimer::m_death_func, this)),
      m_fd(timerfd_create(CLOCK_REALTIME, 0))
{

    if (0 > m_fd)
    {
        throw runtime_error(
            "Error in creating a new fd using timerfd_create()");
    }

    try
    {
        m_reactor->Add(HandleAndMode(READ, m_fd), &m_callback);
    }
    catch (...)
    {
        close(m_fd);

        throw runtime_error("error in add function insidr FDTimer\n");
    }
}

void FDTimer::m_death_func()
{
    m_reactor = NULL;
}

FDTimer::~FDTimer()
{
    if (m_reactor)
    {
        m_reactor->Remove(HandleAndMode(READ, m_fd));
    }

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
    temp_timer.it_value.tv_sec = microseconds.count() / 1000;
    // converting microseconds to nanoseconds ( 1 microsecond = 1000
    // nanoseconds)
    temp_timer.it_value.tv_nsec = (microseconds.count() % 1000) * 1000000;

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
