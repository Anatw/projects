/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <boost/bind.hpp>
#include <iostream> // cout, cin, cerr

#include "minion.hpp"

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

        // fflush(stdin);
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
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////

DerievedListener* listener = new DerievedListener;

Minion::Minion(int port, size_t num_of_blocks, int master_port)
    : m_reactor(listener), m_communicator(port, m_reactor, OnRequest),
      m_storage(num_of_blocks)
{
    StdinHandler stdinListener(m_reactor);
}

Minion::~Minion()
{
    delete listener;
}

void Minion::Run()
{
    m_reactor.Run();
}
