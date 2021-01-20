/*******************************************************************************
Scheduler (design pattern)

useage flow:
1. Create a scheduler, it creates a timer .
2. add 3 tasks - one in 5,
    the second 10, the third in 1 second

Written by Anat Wax, anatwax@gmail.com
Created: 21.7.20
Reviewer: Kobi Rappaport
*******************************************************************************/
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <iostream> // cout, cin, cerr
extern "C"
{
#include <stdio.h>
}

#include "reactor.hpp"
#include "scheduler.hpp"

using namespace std;
using namespace ilrd;

class DerievedListener : public IListener
{
public:
    vector< HandleAndMode > Listen(const vector< HandleAndMode >& handle)
    {
        fd_set ReadFDs;
        fd_set WriteFDs;
        fd_set ExceptFDs;

        FD_ZERO(&ReadFDs);
        FD_ZERO(&WriteFDs);
        FD_ZERO(&ExceptFDs);

        // Inserting keys from vector into the lists with regards to correct
        // MODE
        vector< HandleAndMode >::const_iterator i;
        for (i = handle.begin(); i != handle.end(); ++i)
        {
            switch (i->first)
            {
            case READ:
                FD_SET(i->second, &ReadFDs);
                break;

            case WRITE:
                FD_SET(i->second, &WriteFDs);
                break;

            case EXCEPTION:
                FD_SET(i->second, &ExceptFDs);
                break;

            default:
                break;
            }
        }

        if (0 > select(FD_SETSIZE, &ReadFDs, &WriteFDs, &ExceptFDs, NULL))
        {
            throw domain_error("select failed");
        }

        vector< HandleAndMode > return_vector;

        for (int index = 0; index < FD_SETSIZE; ++index)
        {
            if (FD_ISSET(index, &ReadFDs))
            {
                return_vector.push_back(HandleAndMode(READ, index));
            }
            if (FD_ISSET(index, &WriteFDs))
            {
                return_vector.push_back(HandleAndMode(WRITE, index));
            }
            if (FD_ISSET(index, &ExceptFDs))
            {
                return_vector.push_back(HandleAndMode(EXCEPTION, index));
            }
        }

        return (return_vector);
    }

    ~DerievedListener()
    {
    }
};

////////////////////////////////////////////////////////////////////////////////

class FuncW
{
public:
    FuncW(Scheduler& scheduler, Scheduler::MS timing)
        : m_scheduler(scheduler), m_timing(timing)
    {
    }
    void operator()(int d);

private:
    Scheduler& m_scheduler;
    Scheduler::MS m_timing;
    static int m_counter;
};

int FuncW::m_counter = 0;

////////////////////////////////////////////////////////////////////////////////

void FuncW::operator()(int d)
{
    d = d;

    if (m_counter < 5)
    {
        cout << "Reacuring FuncW executed: "
             << boost::chrono::system_clock::now() << endl;
        ++m_counter;
        m_scheduler.ScheduleAction(
            (boost::chrono::system_clock::now() + m_timing),
            FuncW(m_scheduler, m_timing));
    }
}

////////////////////////////////////////////////////////////////////////////////

void FuncW2(int d)
{
    d = d;
    cout << "FuncW2 executed: " << boost::chrono::system_clock::now() << endl;
}

////////////////////////////////////////////////////////////////////////////////

class StdinHandler
{
public:
    StdinHandler(Reactor& reactor)
        : m_reactor(reactor),
          m_callback(boost::bind(&StdinHandler::Handler, this),
                     boost::bind(&StdinHandler::ReactorStops, this))
    {
        m_reactor.Add(HandleAndMode(READ, STDIN_FILENO), &m_callback);

        m_reactorOn = true;
    }

private:
    void Handler()
    {
        string input;
        getline(cin, input);

        if (input == "ping")
        {
            cout << "-> pong to stdin!" << endl;
        }
        else if (input == "exit")
        {
            m_reactor.Stop();
        }

        fflush(stdin);
    }

    void ReactorStops()
    {
        m_reactorOn = false;
        cout << "stdin listener is out of reactor" << endl;
    }
    Reactor& m_reactor;
    Callback< SimpleSrc< int > > m_callback;
    bool m_reactorOn;
};

////////////////////////////////////////////////////////////////////////////////
//                              main function:                                //
////////////////////////////////////////////////////////////////////////////////

int main()
{
    Reactor reactor(new DerievedListener);

    Scheduler scheduler(reactor);

    scheduler.ScheduleAction(Scheduler::MS(25000), FuncW2);

    scheduler.ScheduleAction(
        Scheduler::TimePoint(boost::chrono::system_clock::now() +
                             boost::chrono::seconds(5)),
        FuncW(scheduler, Scheduler::MS(5000)));

    StdinHandler stdin_handler(reactor);

    reactor.Run();

    return (0);
}
