/*******************************************************************************
Master communicator (Minion)
Written by Anat Wax, anatwax@gmail.com
Created: 6.8.20
Reviewer: Haim Sa'adia
*******************************************************************************/
#include <boost/bind.hpp>
#include <iostream> // cout, cin, cerr

#include "master_communicator.hpp"

using namespace std;
using namespace ilrd;

#define PORT (8765)

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

void func(const Request& request);

DerievedListener* listener = new DerievedListener;
Reactor reactor(listener);
StdinHandler stdinListener(reactor);
MasterCommunicator master_communicator(PORT, reactor, func);

void func(const Request& request)
{
    std::cout << "Entring func()\n";
    std::cout << request.m_mode << std::endl;
    std::cout << request.m_index << std::endl;
    std::cout << request.m_uid << std::endl;
    std::cout << request.m_data << std::endl;

    size_t msg_size = MAX_BLOCK_SIZE + Request().RequestSize();

    Response* response = (Response*)operator new(msg_size);
    memset(response, 0, msg_size);

    response->m_mode = '0';
    response->m_status = 'A';
    response->m_uid = 456789;
    const char* msg = "hello back";
    memcpy(response->m_data, msg, strlen(msg));

    master_communicator.Reply(*response);
    delete response;

    reactor.Stop();
}

int main()
{
    reactor.Run();

    delete listener;

    return (0);
}
