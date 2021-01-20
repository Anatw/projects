/*******************************************************************************
stdin client (Ping Pong Server)

Please note: getaddrinfo() is not competible for c99.

Written by Anat Wax, anatwax@gmail.com
Created: 25.6.20
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
    int n = 0;
    int num_pings = RetRand();
    int interval = 0;
    char buffer[BUF_SIZE] = {0};

    while (TRUE)
    {
        bzero(buffer, sizeof(buffer));
        printf("Enter a string:\n");
        scanf("%s", buffer);

        printf("Sending to server '%s':\n", buffer);
        write(sockfd, buffer, sizeof(buffer)); /* Sending ping */

        if (0 == strcmp(buffer, "ping"))
        {
            bzero(buffer, sizeof(buffer));
            read(sockfd, buffer, sizeof(buffer));

            printf("Client received: %s\n", buffer);

            interval = RetRand();
            printf("about to sleep for %d\n\n", interval);
            sleep(interval);
        }
        else if (0 == strcmp(buffer, "quit") ||
                 0 == strcmp(buffer, "exit"))
        {
            printf("Exiting the stdin client\n");
            exit(0);
        }
    }
}

int main()
{
    int sockfd = 0;
    int connfd = 0;
    struct sockaddr_in servaddr;
    struct sockaddr_in cli;

    system("clear");

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
