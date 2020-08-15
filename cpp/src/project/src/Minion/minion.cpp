/*******************************************************************************
Minion class
Written by Anat Wax, anatwax@gmail.com
Created: 9.8.20
Reviewer: Daria Korotkova
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
    : m_reactor(listener),
      m_communicator(port, m_reactor,
                     boost::bind(&Minion::OnRequest, this, _1)),
      m_storage(num_of_blocks)
{
    StdinHandler stdinListener(m_reactor);
    Run();
}

Minion::~Minion()
{
    m_reactor.Stop();

    delete listener;
}

void Minion::Run()
{
    m_reactor.Run();
}

void Minion::OnRequest(const Request& request)
{
    std::cout << "Entring func()\n";
    std::cout << request.m_mode << std::endl;
    std::cout << request.m_index << std::endl;
    std::cout << request.m_uid << std::endl;
    std::cout << request.m_data << std::endl;

    size_t msg_size = MAX_BLOCK_SIZE + Request().RequestSize();

    Response* response = (Response*)operator new(msg_size);
    memset(response, 0, msg_size);

    /*(0 - read, 1 - write) */
    if (0 == request.m_mode) // read mode
    {
        m_storage.Read(request.m_index, response->m_data);
    }
    else // write mode
    {
        m_storage.Write(request.m_index, request.m_data);
    }

    response->m_mode = request.m_mode;
    response->m_status = 0;
    response->m_uid = request.m_uid;

    m_communicator.Reply(*response);
    delete response;
}
