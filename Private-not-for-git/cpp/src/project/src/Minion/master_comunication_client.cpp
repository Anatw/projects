/*******************************************************************************
Master communicator (Minion)
Written by Anat Wax, anatwax@gmail.com
Created: 6.8.20
Reviewer: Haim Sa'adia

to compile:
pd master_comunication_client.cpp udp_connector.cpp ../Reactor/reactor.cpp -I
../../include  -o client.out
*******************************************************************************/
#include <cstring>
#include <iostream>
#include <new> // operator new

#include <netinet/in.h> /* socket, htons, sendto, recvfrom */
#include <stdio.h>      /* printf */
#include <unistd.h>     /* close , sleep */

#include "master_communicator.hpp"
#include "protocol.hpp"

using namespace std;
using namespace ilrd;

#define PORT (8765)
#define MAX_BLOCK_SIZE (4096)

int main()
{
    int sockfd = 0;
    struct sockaddr_in servaddr;
    int len = sizeof(servaddr);
    size_t msg_size = MAX_BLOCK_SIZE + Request().RequestSize();
    // size_t msg_size = Request().RequestSize();

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        perror("error in socket()");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    Request* request = (Request*)operator new(msg_size);

    std::cout << request->RequestSize() << std::endl;

    request->m_mode = '1';
    request->m_index = 3;
    request->m_uid = 123456;
    const char* msg = "hello world";
    memcpy(request->m_data, msg, strlen(msg));

    char* buffer = new char(msg_size);
    int nbytes = 0;

    nbytes = sendto(sockfd, request, msg_size, MSG_CONFIRM,
                    (const struct sockaddr*)&servaddr, len);
    if (0 > nbytes)
    {
        perror("error in sendto()");
        exit(1);
    }
    printf("ping message sent\n");

    delete request;

    nbytes =
        recvfrom(sockfd, buffer, MAX_BLOCK_SIZE + Response().ResponseSize(),
                 MSG_WAITALL, (struct sockaddr*)&servaddr, (socklen_t*)&len);
    if (0 > nbytes)
    {
        perror("error in recvfrom()");
        exit(1);
    }

    Response* response = (Response*)buffer;
    std::cout << response->m_mode << std::endl;
    std::cout << response->m_status << std::endl;
    std::cout << response->m_uid << std::endl;
    std::cout << response->m_data << std::endl;

    close(sockfd);

    delete buffer;

    return 0;
}
