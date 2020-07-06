/*******************************************************************************
libserver (ping pong server)
Written by Anat Wax, anatwax@gmail.com
Created: 25.6.20
Reviewer: Yoni Naor
*******************************************************************************/
#include <stdio.h>    /* printf(), size_t */
#include <stdlib.h>   /* malloc(), free(), abs(), size_t, rand(), srand() */
#include <assert.h>   /* assert() */
#include <stddef.h>   /* offsetof(), size_t */
#include <time.h>     /* time, size_t, srand() */
#include <string.h>   /* size_t, atoi(), memset() */
#include <sys/wait.h> /* wait() */
#include <fcntl.h>    /* For O_* constants */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> /* for the sockaddr_in struct */
#include <time.h>       /* time() */

#include "libserver.h"

/* New socket fd creations: */
int NewSocketFD(int sock_type)
{
    int sockfd = socket(AF_INET, sock_type, 0);
    if (0 > sockfd)
    {
        perror("ERROR in socket creation\n");
        exit(EXIT_FAILURE);
    }

    return (sockfd);
}

int NewUDPBroadSocket()
{
    int yes = 1;
    int sockfd = NewSocketFD(SOCK_DGRAM);
    /*int status = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));
    

    if (0 > status)
    {
        perror("ERROR in NewUDPBroadSocket\n");
        exit(EXIT_FAILURE);
    }*/

    return (sockfd);
}

/* */

struct sockaddr_in UpdateServerInfo(int server_port)
{
    /*struct sockaddr_in *new_server = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));*/
    struct sockaddr_in new_server;
    bzero(&new_server, sizeof(new_server));
    new_server.sin_family = AF_INET;
    new_server.sin_addr.s_addr = htonl(INADDR_ANY);
    new_server.sin_port = htons(server_port);

    return (new_server);
}

int RetRand()
{
    srand(time(NULL));

    return ((rand() % 8) + 3);
}
