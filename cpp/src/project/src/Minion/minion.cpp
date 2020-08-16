/*******************************************************************************
Minion class
Written by Anat Wax, anatwax@gmail.com
Created: 9.8.20
Reviewer: Daria Korotkova
*******************************************************************************/
#include <boost/bind.hpp>
#include <iostream> // cout, cin, cerr

#include "derived_listener.hpp"
#include "minion.hpp"

using namespace std;
using namespace ilrd;

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

    // Both be64toh() were added after rewiewing Shmuel code. delete this if it
    // makes any problems... Leave only whats innside the paranthesis!

    /*(0 - read, 1 - write) */
    if (0 == request.m_mode) // read mode
    {
        try
        {
            m_storage.Read(be64toh(request.m_index), response->m_data);
        }
        catch (...)
        {
            throw runtime_error("error in Read() method");
        }
    }
    else // write mode
    {
        try
        {
            m_storage.Write(be64toh(request.m_index), request.m_data);
        }
        catch (...)
        {
            throw runtime_error("error in Write() method");
        }
    }

    response->m_mode = request.m_mode;
    response->m_status = 0;
    response->m_uid = request.m_uid;

    m_communicator.Reply(*response);
    delete response;
}
