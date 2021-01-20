/*******************************************************************************
TCP/UDP PingPong (Exercise 2 - TCP)

Please note: getaddrinfo() is not competible for c99.

Written by Anat Wax, anatwax@gmail.com
Created: 21.6.20
*******************************************************************************/
#include <netdb.h>      /* getaddrinfo() */
#include <stdio.h>      /* printf(), size_t */
#include <stdlib.h>     /* EXIT_STATUS */
#include <string.h>     /* bzero(), strlen() */
#include <sys/socket.h> /* socket API functions */
#include <unistd.h>     /* read(), write () */
#include <arpa/inet.h>  /* inet_addr() */

#define BUF_SIZE (256)
#define PORT (8080)
#define TRUE (1)
#define SA struct sockaddr

void ConnectToServer(int sockfd)
{
    char buff[BUF_SIZE] = {0};
    int n = 0;

    while (TRUE)
    {
        bzero(buff, sizeof(buff));
        printf("Enter a string: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
        {
            ;
        }

        write(sockfd, buff, sizeof(buff));

        bzero(buff, sizeof(buff));

        read(sockfd, buff, sizeof(buff));

        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0)
        {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main()
{
    int sockfd = 0;
    int connfd = 0;
    struct sockaddr_in servaddr;
    struct sockaddr_in cli;

    /* Creating a socket: */
    if ((-1) == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("ERROR in socket creation\n");
        exit(EXIT_FAILURE);
    }

    bzero(&servaddr, sizeof(servaddr));

    /* Specify an adderss to connect to: */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

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
