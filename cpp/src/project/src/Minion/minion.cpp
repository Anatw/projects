/*******************************************************************************
Minion class
The Minion receieves two ports:
port - which is the general udp broadcasting comuunication port for communication with Mastes in the system
master_port - which is a port for udp communication, for read/write requests from his master.

Written by Anat Wax, anatwax@gmail.com
Created: 9.8.20
Reviewer: Daria Korotkova
*******************************************************************************/
#include <boost/bind.hpp>
#include <iostream> // cout, cin, cerr

#include "derived_listener.hpp"
#include "minion.hpp"

#define DNDBUG

using namespace std;
using namespace ilrd;

////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////

DerievedListener* listener = new DerievedListener;

Minion::Minion(int port, size_t num_of_blocks, int master_port)
    : m_reactor(listener),
      m_communicator(port, master_port, m_reactor,
                     boost::bind(&Minion::OnRequest, this, _1)),
      m_storage(num_of_blocks)
{
    /* (0 - read, 1 - write) */
    COMMAND_FACTORY->Add(0, ReadBuilder);
    COMMAND_FACTORY->Add(1, WriteBuilder);

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
#ifndef DNDBUG
    std::cout << "Entring func()\n";
    std::cout << (int)request.m_mode << std::endl;
    std::cout << request.m_index << std::endl;
    std::cout << request.m_uid << std::endl;
    std::cout << request.m_data << std::endl;
#endif // DNDBUG

    LOG_INFO(__FILE__ +
             std::string(
                 "::OnRequest(): receieved a request:\n request.m_mode = " +
                 request.m_mode +
                 std::string(", request.m_index = " + request.m_index +
                             std::string("request.m_uid = " + request.m_uid))));

    size_t msg_size = MAX_BLOCK_SIZE + Request().RequestSize();

    Response* response = (Response*)operator new(msg_size);
    memset(response, 0, msg_size);

    response->m_mode = request.m_mode;
    response->m_status = 0;
    response->m_uid = request.m_uid;

    BaseCommand* bc;
    try
    {
        bc = COMMAND_FACTORY->Create(request.m_mode,
                                     Params(m_storage, *response, request));
    }
    catch (const std::exception& e)
    {
        LOG_INFO(
            __FILE__ +
            std::string(
                "::OnRequest(): ERROR in create():\n request.m_mode = " +
                request.m_mode +
                std::string(", request.m_index = " + request.m_index +
                            std::string(", request.m_uid = " + request.m_uid +
                                        std::string("response->m_uid = " +
                                                    response->m_uid)))));
#ifndef DNDBUG
        std::cerr << " An ERROR has occures inside Minion::OnRequest()"
                  << e.what() << std::endl;
#endif // DNDBUG
    }

    bc->operator()();

    LOG_INFO(
        __FILE__ +
        std::string("::OnRequest(): receieved a request:\n request.m_mode = " +
                    request.m_mode +
                    std::string(" request.m_index = " + request.m_index +
                                std::string("request.m_uid = " + request.m_uid +
                                            std::string("Response created: "
                                                        "response->m_uid = " +
                                                        response->m_uid)))));

    m_communicator.Reply(*response);

    delete response;
    delete bc;
}
