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
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (0 > bind(m_fd, (const struct sockaddr*)&server_address,
                 sizeof(server_address)))
    {
        close(m_fd);

        char log_msg[MSG_SIZE] = {0};
        sprintf(log_msg, "%s: inside UDPConnector(): Error in bind()",
                __FILE__);
        LOG_ERROR(log_msg);

        throw runtime_error("error in bind function");
    }

    char log_msg[MSG_SIZE] = {0};
    sprintf(log_msg,
            "%s: inside UDPConnector(): Finished binding process with port no. "
            "%d. m_fd = %d",
            __FILE__, port, m_fd);
    LOG_INFO(log_msg);
}

UDPConnector::~UDPConnector()
{
    char log_msg[MSG_SIZE] = {0};
    sprintf(log_msg, "%s: inside ~UDPConnector(): Dtor activated", __FILE__);
    LOG_INFO(log_msg);

    close(m_fd);
}
