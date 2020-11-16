/*******************************************************************************
Master communicator (Minion)
Each Minion's MasterCommunicator will have two file descriptors for two ports - one as a udp broadcast channel to communitcate with Masters broadcasts, and one for udp communication by read/write requests with his master.

Written by Anat Wax, anatwax@gmail.com
Created: 6.8.20
Reviewer: Haim Sa'adia
Version: II (27.10.20)
*******************************************************************************/
#ifndef __ILRD_RD8586_MASTER_COMMUNICATOR_HPP__
#define __ILRD_RD8586_MASTER_COMMUNICATOR_HPP__

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators

#include "logger.hpp"
#include "protocol.hpp"
#include "../Master/master_protocol.hpp"
#include "reactor.hpp"
#include "udp_connector.hpp"

namespace ilrd
{
class MasterCommunicator : private boost::noncopyable
{
public:
    typedef boost::function< void(const Request&) > ActionRequest;

    explicit MasterCommunicator(int port, int master_port, Reactor& reactor,
                                ActionRequest ar_func);
    ~MasterCommunicator();

    // These methods will be called by the reactor when the FDs are ready
    void ReadRequest(int fd) const;
    void ReadBroadcast(int fd);

    void Reply(const Response& result) const;
    void Reply(const BroadcastFrom& result) const;
    void Reply(const AssigmentResponse& result) const;

private:
    UDPConnector m_udpConnector;
    // m_masterudpConnector - For broadcasting communication with Master:
    UDPConnector m_masterUDPConnector;
    Reactor& m_reactor;
    ActionRequest m_arFunc;
    Callback< SimpleSrc< int > > m_callback_request;
    Callback< SimpleSrc< int > > m_callback_broadcast;

    struct sockaddr_storage m_master_address;
    UID m_minion_uid;
    UID m_master_uid;
    socklen_t m_address_len;
};
} // namespace ilrd

#endif /* __ILRD_RD8586_STORAGE_HPP__ */
