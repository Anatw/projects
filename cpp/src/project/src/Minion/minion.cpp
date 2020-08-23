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
    (void)master_port;

    /* (0 - read, 1 - writparamse) */
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
    std::cout << "Entring func()\n";
    std::cout << (int)request.m_mode << std::endl;
    std::cout << request.m_index << std::endl;
    std::cout << request.m_uid << std::endl;
    std::cout << request.m_data << std::endl;

    char log_msg[MSG_SIZE] = {0};
    sprintf(log_msg,
            "%s: inside OnRequest(): receieved a request:\n request.m_mode = "
            "%c, request.m_index = %ld, request.m_uid = %ld",
            __FILE__, request.m_mode, request.m_index, request.m_uid);
    LOG_INFO(log_msg);

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
        memset(log_msg, '0', MSG_SIZE);

        sprintf(
            log_msg,
            "%s: inside OnRequest(): ERROR in create():\n request.m_mode = "
            "%c, request.m_index = %ld, request.m_uid = %ld. Response created: "
            "response->m_uid = %ld. error massage: %s",
            __FILE__, request.m_mode, request.m_index, request.m_uid,
            response->m_uid, e.what());
        LOG_INFO(log_msg);
    }

    bc->operator()();

    memset(log_msg, '0', MSG_SIZE);
    sprintf(log_msg,
            "%s: inside OnRequest(): receieved a request:\n request.m_mode = "
            "%c, request.m_index = %ld, request.m_uid = %ld. Response created: "
            "response->m_uid = %ld",
            __FILE__, request.m_mode, request.m_index, request.m_uid,
            response->m_uid);
    LOG_INFO(log_msg);

    m_communicator.Reply(*response);

    delete response;
    delete bc;
}
