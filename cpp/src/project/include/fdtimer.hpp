/*******************************************************************************
fdtimer.hpp (part of the Scheduler design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 21.7.20
Reviewer: Kobi Rappaport
*******************************************************************************/

#ifndef ILRD_RD8586_TIMER_HPP
#define ILRD_RD8586_TIMER_HPP

#include <boost/chrono.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include "advanced_observer.hpp"
#include "reactor.hpp"

namespace ilrd
{

// use #include <sys/timerfd.h> in the implementation
class FDTimer : private boost::noncopyable
{
public:
    // typedefs for inner types
    typedef Callback< SimpleSrc< int > >::CallbackPointer ActionFunc;
    typedef boost::chrono::milliseconds MS;

    // FDTimer Constructor
    // Receives: reactor - a reference to a reactor to work with
    //           callback_func - a handler function to invoke when the reactor
    //                           calls timer file descriptors' handler
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             created
    explicit FDTimer(Reactor& reactor, ActionFunc callback_func);

    // FDTimer Destructor
    // Exceptions: no exceptions
    ~FDTimer();

    // Set
    // Receives: microseconds - a chrono::microseconds object with the time
    //           requested from now
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             written
    void Set(MS microseconds);

    // Unset
    // Exceptions: throws runtime_error if timer file descriptor can't be
    //             written
    void Unset();

private:
    Reactor* m_reactor;
    Callback< SimpleSrc< int > > m_callback;
    int m_fd;
    void m_death_func();
};

} // namespace ilrd

#endif /* ILRD_RD8586_FD_TIMER_HPP */
