/*******************************************************************************
Reactor (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 7.7.20
Reviewer: Dean Oron
*******************************************************************************/
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <cstdio> // perror
#include <iostream>
#include <map>
#include <queue>
#include <stdio.h>      // STDIN_FILENO (this is equal to '0')
#include <sys/select.h> /* select */
#include <utility>
#include <vector>

extern "C"
{
    //#include "ping_pong_server.h" // tcp and udp server functions
}

#include "reactor.hpp"

using namespace std;

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

void FuncW(int d)
{
    d = d;
    static int i = 0;
    cout << "FuncW executed: " << i << endl;
    ++i;
}

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

int main()
{
    // DerievedListener listener;
    Reactor newReactor(new DerievedListener);

    StdinHandler stdinListener(newReactor);

    // reactor.Add(HandleAndMode(READ, STDIN_FILENO), StdinHandler(reactor));
    newReactor.Run();

    // StdinHandler test(reactor);

    // HandleAndMode stdin_w = HandleAndMode(WRITE, STDIN_FILENO);

    // reactor.Add(first, FuncW);
    // reactor.Add(HandleAndMode(READ, STDIN_FILENO), FuncW);
    // reactor.Add(HandleAndMode(EXCEPTION, STDIN_FILENO), FuncW);

    // reactor.Remove(first);

    // reactor.Run();

    return 0;
}
