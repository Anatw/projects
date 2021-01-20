/*******************************************************************************
TCP/UDP PingPong (Exercise 2 - TCP)

Please note: getaddrinfo() is not competible for c99.

Written by Anat Wax, anatwax@gmail.com
Created: 21.6.20
*******************************************************************************/
#include <netdb.h>      /* getaddrinfo() */
#include <stdio.h>      /* printf(), size_t */
#include <stdlib.h>     /* EXIT_STATUS, srand(), rand() */
#include <string.h>     /* bzero(), strlen() */
#include <sys/socket.h> /* socket API functions */
#include <unistd.h>     /* read(), write (), sleep() */
#include <arpa/inet.h>  /* inet_addr() */
#include <time.h>       /* time() */

#include "libserver.h"

#define BUF_SIZE (5)
#define PORT (4050)
#define TRUE (1)
#define SA struct sockaddr

void ConnectToServer(int sockfd)
{
    char buff[BUF_SIZE] = {0};
    int n = 0;
    int num_pings = RetRand();
    int interval = 0;
    char *message = "Ping";

    for (; num_pings > 0; --num_pings)
    {
        printf("There are %d 'pings' left\n", num_pings);

        write(sockfd, message, sizeof(buff)); /* Sending ping */

        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));

        printf("Client received: %s\n", buff);

        interval = RetRand();
        printf("about to sleep for %d\n", interval);
        sleep(interval);
    }
}

int main()
{
    int sockfd = 0;
    int connfd = 0;
    struct sockaddr_in servaddr;
    struct sockaddr_in cli;

    sockfd = NewSocketFD(SOCK_STREAM);

    /* Specify an adderss to connect to: */
    servaddr = UpdateServerInfo(PORT);

    /* connect client socket to server socket: */
    if ((-1) == (connect(sockfd, (SA *)&servaddr, sizeof(servaddr))))
    {
        perror("ERROR in connect function\n");
        exit(EXIT_FAILURE);
    }

    /* Exchange messages with the server side: */
    ConnectToServer(sockfd);

    close(sockfd);
}
