#ifndef ILRD_RD8586_UDP_CONNECTOR_HPP
#define ILRD_RD8586_UDP_CONNECTOR_HPP
/*******************************************************************************
Storage class (part of project Minion)
Written by Anat Wax, anatwax@gmail.com
Created: 5.8.20
Reviewer: Daria Korotkova
*******************************************************************************/
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "boost/core/noncopyable.hpp"

namespace ilrd
{

class UDPConnector : private boost::noncopyable
{
public:
    explicit UDPConnector(int port);
    ~UDPConnector();

    inline int GetFD() const
    {
        return m_fd;
    }

private:
    int m_fd;
};

} // namespace ilrd

#endif // ILRD_RD8586_UDP_CONNECTOR_HPP
