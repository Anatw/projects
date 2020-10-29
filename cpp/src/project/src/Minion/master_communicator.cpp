/*******************************************************************************
Master communicator (Minion)
Each Minion's MasterCommunicator will have two file descriptors for two ports - one as a udp broadcast channel to communitcate with Masters broadcasts, and one for udp communication by read/write requests with his master.

Written by Anat Wax, anatwax@gmail.com
Created: 6.8.20
Reviewer: Haim Sa'adia
Version: II (27.10.20)
*******************************************************************************/
#include <boost/bind.hpp>
#include <endian.h> // htobe64
#include <iostream> // cout, cin, cerr
#include <new>      // operator new
#include <cassert> // asserts

#include "master_communicator.hpp"
#include "reactor.hpp"

using namespace std;
using namespace ilrd;

MasterCommunicator::MasterCommunicator(int port, int master_port, Reactor& reactor, ActionRequest ar_func)
    : m_udpConnector(port), m_masterudpConnector(master_port), m_reactor(reactor), m_arFunc(ar_func),
      m_callback_request(boost::bind(&MasterCommunicator::ReadRequest, this, _1)), m_callback_broadcast(boost::bind(&MasterCommunicator::ReadBroadcast, this, _1))
{
    m_reactor.Add(make_pair(READ, m_udpConnector.GetFD()), &m_callback_request);
    m_reactor.Add(make_pair(READ, m_masterudpConnector.GetFD()), &m_callback_broadcast);

    // nil_generator will initialize all uid struct to zero's
    boost::uuids::nil_generator uid_zero;
    m_master_uid = uid_zero();
    assert(m_master_uid.is_nil() == true);

    boost::uuids::random_generator uuid;
    m_minion_uid = uuid();

    LOG_INFO("Finished Ctor of MasterCommunicator\n");
}

////////////////////////////////////////////////////////////////////////////////

MasterCommunicator::~MasterCommunicator()
{
    m_reactor.Remove(make_pair(READ, m_udpConnector.GetFD()));
    LOG_INFO("Finished Dtor of MasterCommunicator\n");
}

////////////////////////////////////////////////////////////////////////////////

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
        LOG_ERROR(
            __FILE__ +
            std::string("::ReadRequest(): error in read request (recvfrom())"));
        throw runtime_error("error in read request (recvfrom())");
    }

    Request* request = (Request*)buffer;
    request->m_index =
        htobe64(request->m_index); // switch endianess to network endianess

    m_arFunc(*request);

    LOG_INFO(
        __FILE__ +
        std::string("::ReadRequest(): Request read from MasterCommunicator "
                    "and was sent to Request() | m_mode =" +
                    request->m_mode));

    delete request;
}

////////////////////////////////////////////////////////////////////////////////

void MasterCommunicator::ReadBroadcast(int fd)
{
    size_t size = sizeof(BroadcastFrom);
    char* buffer = (char*)operator new(size);

    socklen_t addr_len = sizeof(m_master_address);

    int num_bytes_received = 0;

    if (0 > (num_bytes_received =
                 recvfrom(fd, buffer, size, MSG_WAITALL,
                          (struct sockaddr*)&m_master_address, &addr_len)))
    {
        LOG_ERROR(
            __FILE__ +
            std::string("::ReadRBroadcast(): error in read request (recvfrom())"));
        throw runtime_error("ReadRBroadcast(): error in read request (recvfrom())");
    }

    BroadcastFrom* broadcast = (BroadcastFrom*)buffer;

    // m_arFunc(*broadcast);

    LOG_INFO(
        __FILE__ +
        std::string("::ReadRBroadcast(): Broadcast request read from Master (master uid variant = " + broadcast->m_uid_from.variant() + std::string("), of type ") + broadcast->m_type));

    // if true - this is a BroadcastFrom. if false - this is an AssigmentRequest:
    if (broadcast->m_uid_not_relevant.is_nil()) 
    {
        // Check if this Minion is connected to any Master, and if so - is it to this master. If not - do nothing, if yes - send back BroadcastFrom response
        if (m_master_uid.is_nil() ||
            m_master_uid == broadcast->m_uid_from)
        {
            broadcast->m_uid_from = m_minion_uid;

            Reply(*broadcast);
        }
    }
    else // this is an AssigmentRequest
    {
        // Connect to this master - add it's uid to m_master_uid
        AssigmentRequest *assignment_req = (AssigmentRequest*)broadcast;
        AssigmentResponse* response = new AssigmentResponse;

        if (assignment_req->m_type == 'a')
        {
            m_master_uid = assignment_req->m_uid_master;

            response->m_uid_minion = m_minion_uid;
            response->m_type = 'a';
            response->m_status = 0x06; // ACK            
        }
        else // (assignment_req->m_type == 'd')
        {
            // set m_master_uid to zero
            boost::uuids::nil_generator uid_zero;
            m_master_uid = uid_zero();
            assert(m_master_uid.is_nil() == true);

            response->m_uid_minion = m_minion_uid;
            response->m_type = 'd';
            response->m_status = 0x06; // ACK
        }

            Reply(*response);

            delete assignment_req;
            delete response;
    }

    delete broadcast;
}

////////////////////////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////////////////////////

void MasterCommunicator::Reply(const BroadcastFrom& result) const
{
    if (0 >
        (sendto(m_masterudpConnector.GetFD(), &result, sizeof(BroadcastFrom), MSG_CONFIRM, (struct sockaddr*)&m_master_address, sizeof(m_master_address))))
    {
        throw runtime_error("error in master communicator (Reply())");
    }

    LOG_INFO(
        __FILE__ +
        std::string("::Reply(): BroadcastFrom reply was sent back to the Master (minion uid variant = " + result.m_uid_from.variant()));
}

////////////////////////////////////////////////////////////////////////////////

void MasterCommunicator::Reply(const AssigmentResponse& response) const
{
    if (0 >
        (sendto(m_masterudpConnector.GetFD(), &response, sizeof(AssigmentResponse), MSG_CONFIRM, (struct sockaddr*)&m_master_address, sizeof(m_master_address))))
    {
        throw runtime_error("error in master communicator (Reply())");
    }

    LOG_INFO(
        __FILE__ +
        std::string("::Reply(): BroadcastFrom reply was sent back to the Master (minion uid variant = " + response.m_uid_minion.variant()));
}