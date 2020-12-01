/*******************************************************************************
Storage class (part of project Minion) - udp server
Written by Anat Wax, anatwax@gmail.com
Created: 5.8.20
Reviewer: Daria Korotkova
*******************************************************************************/
#include <arpa/inet.h>
#include <iostream>     // cout, cin, cerr
#include <string.h>     // memset()
#include <sys/socket.h> /* getaddrinfo() */
#include <sys/types.h>  /* getaddrinfo() */
#include <unistd.h>

#include "udp_connector.hpp"

using namespace std;
using namespace ilrd;

UDPConnector::UDPConnector(int port)
{
    m_fd = socket(AF_INET, SOCK_DGRAM, 0); // creating a udp socket

    if (0 > m_fd)
    {
        throw runtime_error("error in fd creation");
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET; /* address family: AF_INET */
    /* port in network byte order - this is why the "htons" is there...: */
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY; /* internet address */

    if (0 > bind(m_fd, (const struct sockaddr*)&server_address,
                 sizeof(server_address)))
    {
        close(m_fd);

        LOG_ERROR(__FILE__ + std::string("::UDPConnector(): Error in bind()"));

        throw runtime_error("error in bind function");
    }

    LOG_INFO(__FILE__ +
             std::string(
                 "::UDPConnector(): FINISHED binding process with port no. " +
                 port + std::string(". m_fd = " + m_fd)));
}

UDPConnector::~UDPConnector()
{
    LOG_INFO(__FILE__ + std::string("::~UDPConnector(): Dtor activated"));

    close(m_fd);
}
