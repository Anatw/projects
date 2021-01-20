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
#include <arpa/inet.h>

#define PORT "3490"
#define BACKLOG (5)
#define BUF_SIZE (256)

int main()
{
    int status = 0;
    struct addrinfo hints;
    struct addrinfo *servinfo = NULL;
    struct addrinfo *iter = NULL;
    int bytes_recv = 0;
    int sockfd = 0;
    /* for accept(): */
    socklen_t addr_size;
    struct sockaddr_storage their_addr;
    int new_fd = 0;
    /* for recv(): */
    char buffer[BUF_SIZE] = {0};

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; /* TCP stream socket */
    hints.ai_flags = AI_PASSIVE;

    if (0 != (status = getaddrinfo(NULL, PORT, &hints, &servinfo)))
    {
        return (1);
    }

    for (iter = servinfo; iter != NULL; iter = iter->ai_next)
    {
        sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                        servinfo->ai_protocol);
        if ((-1) == sockfd)
        {

            freeaddrinfo(servinfo);
            perror("client: socket");
            continue;
            return (1);
        }
        if ((-1) == (connect(sockfd, iter->ai_addr, iter->ai_addrlen)))
        {
            freeaddrinfo(servinfo);
            close(sockfd);
            perror("client: ERROR in connect function");
            continue;
        }
        break;
    }
    if (NULL == iter)
    {
        printf("error in iter);");
        return 1;
    }

    inet_ntop(iter->ai_family, get_in_addr((struct sockaddr *)iter->ai_addr, buffer, BUF_SIZE));

    printf("connecting to suffer\n");

    freeaddrinfo(servinfo);
    if ((-1) == (bytes_recv = recv(sockfd, buffer, BUF_SIZE - 1, 0)))
    {
        perror("ERROR in recv functions\n");
        exit(EXIT_FAILURE);
    }
    buffer[bytes_recv] = '\0';

    printf("srever received massage:\n%s\n", buffer);

    close(sockfd);

    return (0);
}
