/*******************************************************************************
Storage class (part of project Minion)
Written by Anat Wax, anatwax@gmail.com
Created: 5.8.20
Reviewer: Daria Korotkova
*******************************************************************************/
#include <iostream>

#include <arpa/inet.h>  //sockaddr_in, htons()
#include <strings.h>    //bzero()
#include <sys/socket.h> //socket()
#include <sys/types.h>  //socket()

#include "udp_connector.hpp"

using namespace ilrd;

int main()
{
    UDPConnector udp_connector(8002);

    int fd = udp_connector.GetFD();

    char buffer[100] = {0};
    char* massage = "hello :)";
    struct sockaddr_in cliaddr;
    socklen_t len = 0;
    bzero(&cliaddr, sizeof(struct sockaddr_in));
    (fd, (char*)massage, 100, MSG_WAITALL, (struct sockaddr*)&cliaddr, len);
    recvfrom(fd, (char*)buffer, 100, MSG_WAITALL, (struct sockaddr*)&cliaddr,
             &len);
    std::cout << "Client :" << buffer << std::endl;

    return (0);
}
