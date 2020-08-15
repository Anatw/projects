/*******************************************************************************
Master communicator (Minion)
Written by Anat Wax, anatwax@gmail.com
Created: 6.8.20
Reviewer: Haim Sa'adia
*******************************************************************************/
#include <boost/bind.hpp>
#include <endian.h> // htobe64
#include <iostream> // cout, cin, cerr
#include <new>      // operator new

#include "master_communicator.hpp"
#include "reactor.hpp"

using namespace std;
using namespace ilrd;

MasterCommunicator::MasterCommunicator(int port, Reactor& reactor,
                                       ActionRequest ar_func)
    : m_udpConnector(port), m_reactor(reactor), m_arFunc(ar_func),
      m_callback(boost::bind(&MasterCommunicator::ReadRequest, this, _1))
{
    m_reactor.Add(make_pair(READ, m_udpConnector.GetFD()), &m_callback);
}

MasterCommunicator::~MasterCommunicator()
{
    m_reactor.Remove(make_pair(READ, m_udpConnector.GetFD()));
}

void MasterCommunicator::ReadRequest(int fd) const
{
    size_t size = MAX_BLOCK_SIZE + sizeof(Request);
    char* buffer = (char*)operator new(size);

    socklen_t addr_len = sizeof(m_master_address);

    int num_bytes_received = 0;

    if (0 > (num_bytes_received =
                 recvfrom(fd, buffer, size, MSG_WAITALL,
                          (struct sockaddr*)&m_master_address, &addr_len)))
    {
        throw runtime_error("error in read request (recvfrom())");
    }

    Request* request = (Request*)buffer;
    request->m_index =
        htobe64(request->m_index); // switch endianess to network endianess

    m_arFunc(*request);

    delete request;
}

void MasterCommunicator::Reply(const Response& response) const
{
    int msg_size = 0;
    if (0 == response.m_mode) // read mode
    {
        msg_size = MAX_BLOCK_SIZE + offsetof(Response, m_data);
    }
    else // write mode
    {
        msg_size = offsetof(Response, m_data);
    }

    if (0 >
        (sendto(m_udpConnector.GetFD(), &response, msg_size, MSG_CONFIRM,
                (struct sockaddr*)&m_master_address, sizeof(m_master_address))))
    {
        throw runtime_error("error in master communicator (Reply())");
    }
}
