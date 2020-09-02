/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

Reactor (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 7.7.20
Reviewer: Dean Oron
*******************************************************************************/
#ifndef ILRD_RD8586_REACTOR_HPP
#define ILRD_RD8586_REACTOR_HPP

#include <boost/core/noncopyable.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

#include "advanced_observer.hpp"
#include "advanced_subject.hpp"

// The type of a handle is system specific. We're using UNIX so an handle is
// represented by an integer
typedef int Handle;
class IListener;

#define ORIGINAL_VERSION

////////////////////////////////////////////////////////////////////////////////
//                     IListener class & functions:                           //
////////////////////////////////////////////////////////////////////////////////

// The user may derieve from this class to define his own Listener class
enum MODE
{
    WRITE,
    READ,
    EXCEPTION
};

typedef boost::function< void(int) > HandleFunc;
typedef std::pair< MODE, Handle > HandleAndMode;
typedef std::pair< HandleAndMode, HandleFunc > KeyAndFunc;

class IListener
{
public:
    virtual ~IListener(){};
    // to be implemented to work with "select":
    virtual std::vector< HandleAndMode >
    Listen(const std::vector< HandleAndMode >& handle_and_mode) = 0;
};

////////////////////////////////////////////////////////////////////////////////
//                     Reactor class & functions:                             //
////////////////////////////////////////////////////////////////////////////////

// Registration interface of the Reactor
class Reactor : private boost::noncopyable
{
public:
    // Reactor(IListener *listener) : m_Listener(listener), to_stop(0) {}
    Reactor(IListener* listener) : m_Listener(listener)
    {
    }
    ~Reactor();

    // This add() version is in case that the user has added a function, but
    // will not need to bee in charge to remove it - it will happen automaticly
    // for him (like the RAII principles), and we want to protect the user in
    // case he will forget to remove() this handle_and_func function - we want
    // to crete some sort of an object that in his distructor is releasing
    // the pointer to the function - we have to create a seperation between
    // what we are holding and what the user is holding:
    // we want to holds SimpleSrc(that object we will hold), that will point to
    // another object - Callback: Class SimpleSrc{} <-> class Callback{}
    // Callback can go out of scope.
    void Add(HandleAndMode handle_and_mode,
             Callback< SimpleSrc< int > >* callback);
    // void Remove(HandleAndMode handle_and_mode);

    void Remove(HandleAndMode handle_and_mode);

    void Run();
    void Stop();

private:
    void DeleteOnDestruction();

    // The map holds a function that shouold be activated for a specific
    // combination of MODE and Handle:

    // SimpleSrc is pointing to the Callback onject, and it will not get out of
    // scope.
    std::map< HandleAndMode, SimpleSrc< int >* > m_EventHandlers;
    IListener* const m_Listener;
    // Listener m_listener;
    bool to_stop;
};

#endif // ILRD_RD8586_REACTOR_HPP
