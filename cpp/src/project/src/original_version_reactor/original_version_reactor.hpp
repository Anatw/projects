/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

Reactor (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 7.7.20
Reviewer: Dean Oron
*******************************************************************************/
#ifndef ILRD_RD8586_REACTOR_HPP
#define ILRD_RD8586_REACTOR_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <boost/function.hpp>
#include <utility>
#include <boost/core/noncopyable.hpp>

#include "advanced_subject.hpp"
#include "advanced_observer.hpp"

// The type of a handle is system specific. We're using UNIX so an handle is
// represented by an integer
typedef int Handle;
class IListener;

#define ORIGINAL_VERSION

////////////////////////////////////////////////////////////////////////////////
//                     IListener class & functions:                           //
////////////////////////////////////////////////////////////////////////////////

//The user may derieves from this class to define his own Listener class
#define ORIGINAL_VERSION
class IListener
{
public:
    enum MODE
    {
        WRITE,
        READ,
        EXCEPTION
    };
    typedef std::pair<MODE, Handle> HandleAndMode;

    virtual ~IListener(){};
    // to be implemented to work with "select":
    virtual std::vector<HandleAndMode> Listen(const std::vector<HandleAndMode> &handle) = 0;
};
#endif // ORIGINAL_VERSION

////////////////////////////////////////////////////////////////////////////////
//                     Reactor class & functions:                             //
////////////////////////////////////////////////////////////////////////////////

// Registration interface of the Reactor
class Reactor : private boost::noncopyable
{
public:
    enum MODE
    {
        WRITE,
        READ,
        EXCEPTION
    };

    typedef boost::function<void(int)> HandleFunc;
    typedef std::pair<MODE, Handle> HandleAndMode;
    typedef std::pair<HandleAndMode, HandleFunc> KeyAndFunc;

    // Reactor(IListener *listener) : m_Listener(listener), to_stop(0) {}
    Reactor() {}
    inline ~Reactor()
    {
        delete this->m_Listener; // I THINK THIS MIGHT HAVE TO BE DELETED - I'M DELETING SOMETHING THAT NOT I CREATED (USING 'NEW').
    }

    void Add(HandleAndMode handle_and_mode, HandleFunc func);
    void Remove(HandleAndMode handle_and_mode);

    void Run();
    void Stop();

private:
    // The map holds a function that shouold be activated for a specific
    // combination of MODE and Handle:
    std::map<HandleAndMode, HandleFunc> m_EventHandlers;

    // IListener *const m_Listener;
    Listener m_listener;
    bool to_stop;
};

#endif // ILRD_RD8586_REACTOR_HPP
