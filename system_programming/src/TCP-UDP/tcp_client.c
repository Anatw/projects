/*******************************************************************************
TCP/UDP PingPong (Exercise 2) - TCP

Written by Anat Wax, anatwax@gmail.com
Created: 18.6.20
*******************************************************************************/
#include <stdio.h>      /* printf(), size_t */
#include <stdlib.h>     /* malloc(), free(), abs(), size_t */
#include <string.h>     /* size_t, atoi(), memset() */
#include <sys/wait.h>   /* wait() */
#include <sys/types.h>  /* getaddrinfo() */
#include <sys/socket.h> /* getaddrinfo() */
#include <netdb.h>      /* getaddrinfo() */
#include <unistd.h>     /* close() */

#include "LIB_TCP.h"

#define PORT (3490)

struct connectionInfo
{
    int status;
    int sockfd;
} /* portInfo_t */;

portInfo_t *InitAddrInfo(struct addrinfo *hints, const char *port,
                         struct addrinfo *servinfo)
{
}

int GetSockfd(portInfo_t *ret)
{
    return (ret->sockfd);
}

void CloseAndFree(struct addrinfo *info, int sockfd)
{
    close(sockfd);
    freeaddrinfo(info);
}

int main()
{
    struct addrinfo hints;
    portInfo_t *port_info = 0;
    struct addrinfo *servinfo = NULL;
    int sockfd = 0;
    char *massage = "Hello from ping!!\n";
    int status = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; /* TCP stream socket */
    hints.ai_flags = AI_PASSIVE;

    if (0 != (status = getaddrinfo(NULL, PORT, (const struct addrinfo *)&hints, &servinfo)))
    {
        freeaddrinfo(servinfo);
    }

    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                    servinfo->ai_protocol);
    if ((-1) == sockfd)
    {
        perror("an error has occured in socket function\n");

        freeaddrinfo(servinfo);
        exit(EXIT_FAILURE);
    }

    if ((-1) == (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen)))
    {
        perror("an error has occured in bind function\n");

        freeaddrinfo(servinfo);
        exit(EXIT_FAILURE);
    }

    connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

    send(sockfd, massage, strlen(massage), 0);

    CloseAndFree(servinfo, sockfd);

    return (0);
}
