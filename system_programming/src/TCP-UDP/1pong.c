/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

compile with GCC (and not gd! - getaddrinfo() is not competible for c99).

TCP/UDP PingPong (Exercise 1)
Written by Anat Wax, anatwax@gmail.com
Created: 18.6.20
Reviewer: 
*******************************************************************************/
#include <stdio.h>      /* printf(), size_t */
#include <stdlib.h>     /* malloc(), free(), abs(), size_t */
#include <string.h>     /* size_t, atoi(), memset() */
#include <sys/wait.h>   /* wait() */
#include <sys/types.h>  /* getaddrinfo() */
#include <sys/socket.h> /* getaddrinfo() */
#include <netdb.h>      /* getaddrinfo() */

#define BUF_SIZE (256)

int main()
{
    int status = 0;
    struct addrinfo hints;
    struct addrinfo *servinfo = NULL;
    char buffer[BUF_SIZE] = {0};

    printf("starting pong:\n");

    int sockfd = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM; /* UDP stream socket */
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, "3490", &hints, &servinfo);

    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

    recv(sockfd, buffer, 10, 0);

    printf("%s\n", buffer);

    return (0);
}
