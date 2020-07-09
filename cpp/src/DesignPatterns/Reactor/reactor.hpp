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

using namespace std;

// The type of a handle is system specific. We're using UNIX so an handle is
// represented by an integer
typedef int Handle;
class IListener;

enum MODE
{
    WRITE,
    READ,
    EXCEPTION
};

////////////////////////////////////////////////////////////////////////////////
//                     IListener class & functions:                           //
////////////////////////////////////////////////////////////////////////////////

typedef boost::function<void(int)> HandleFunc;
typedef pair<MODE, Handle> HandleAndMode;
typedef pair<HandleAndMode, HandleFunc> KeyAndFunc;

//The user may derieves from this class to define his own Listener class
class IListener
{
public:
    virtual ~IListener(){};
    // to be implemented to work with "select":
    virtual vector<HandleAndMode> Listen(const vector<HandleAndMode> &handle) = 0;
};

////////////////////////////////////////////////////////////////////////////////
//                     Reactor class & functions:                             //
////////////////////////////////////////////////////////////////////////////////

// Registration interface of the Reactor
class Reactor : private boost::noncopyable
{
public:
    Reactor(IListener *listener) : m_Listener(listener), to_stop(0) {}
    inline ~Reactor()
    {
        delete this->m_Listener;
    }

    void Add(HandleAndMode handle_and_mode, HandleFunc func);
    void Remove(HandleAndMode handle_and_mode);

    void Run();
    void Stop();

private:
    // The map holds a function that shouold be activated for a specific
    // combination of MODE and Handle:
    map<HandleAndMode, HandleFunc> m_EventHandlers;
    IListener *m_Listener;
    bool to_stop;
};

#endif // ILRD_RD8586_REACTOR_HPP
