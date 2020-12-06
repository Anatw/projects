/*******************************************************************************
timer.hpp (part of the Scheduler design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 21.7.20
Reviewer:
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

// timer should create a fd - maybe a pipe
// that will invoke callback in specific time
class FDTimer : private boost::noncopyable
{
public:
    typedef Callback< SimpleSrc< int > >::CallbackPointer ActionFunc;
    typedef boost::chrono::microseconds MS;
    explicit FDTimer(
        Reactor& reactor,
        ActionFunc callback_func); // Ctor - callback_func that came from
                                   // the scheduler and invokes the first
                                   // task in the pqueue

    ~FDTimer(); // Dtor - close fd

    void Set(MS time); // read about boost::chrono, think about solutions
                       // for making it non-blocking.
    void Unset();

private:
    Reactor& m_reactor;
    Callback< SimpleSrc< int > > m_callback;
    int fd;
};

////////////////////////////////////////////////////////////////////////////////
///   inline functions implementation   ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace ilrd

#endif /* ILRD_RD8586_TIMER_HPP */
