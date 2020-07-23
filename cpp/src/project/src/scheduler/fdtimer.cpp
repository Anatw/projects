/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <iostream> // cout, cin, cerr
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
}

////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
