/*******************************************************************************
Master communicator (Minion)
Written by Anat Wax, anatwax@gmail.com
Created: 6.8.20
Reviewer: Haim Sa'adia
*******************************************************************************/
#ifndef __ILRD_RD8586_MASTER_COMMUNICATOR_HPP__
#define __ILRD_RD8586_MASTER_COMMUNICATOR_HPP__

#include <boost/noncopyable.hpp> // boost::noncopyable

#include "protocol.hpp"
#include "reactor.hpp"
#include "udp_connector.hpp"

namespace ilrd
{
class MasterCommunicator : private boost::noncopyable
{
public:
    typedef boost::function< void(const Request&) > ActionRequest;

    explicit MasterCommunicator(int port, Reactor& reactor,
                                ActionRequest ar_func);
    ~MasterCommunicator();

    // This method will be called by the reactor when the fd is ready
    void ReadRequest(int fd) const;

    void Reply(const Response& result) const;

private:
    UDPConnector m_udpConnector;
    Reactor& m_reactor;
    ActionRequest m_arFunc;
    Callback< SimpleSrc< int > > m_callback;

    struct sockaddr_storage m_master_address;
    socklen_t m_address_len;
};
} // namespace ilrd

#endif /* __ILRD_RD8586_STORAGE_HPP__ */
