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
#include <unistd.h>     /* close() */
#include <netinet/in.h>
#include <sys/types.h>

#define BUF_SIZE (256)
#define PORT (8080)
#define TRUE (1)
#define SA struct sockaddr

void ConnectToServer(int sockfd)
{
    char buffer[BUF_SIZE];
    int n;
    int bytes_recv = 0;
    struct sockaddr_in client_address;
    socklen_t client_length = 0;

    /* Ping/pong will continue until program is exited: */
    while (TRUE)
    {
        bzero(buffer, BUF_SIZE);

        /* read the message from client into the buffer 
        read(sockfd, buff, sizeof(buff));*/
        bytes_recv = recvfrom(sockfd, buffer, BUF_SIZE, MSG_WAITALL,
                              (struct sockaddr *)&client_address, &client_length);

        buffer[bytes_recv] = '\0';

        /* print buffer which contains the client's message */
        printf("From client: %s\t To client : ", buffer);

        bzero(buffer, BUF_SIZE);
        n = 0;
        /* copy server message in the buffer */
        while ((buffer[n++] = getchar()) != '\n')
        {
            ;
        }

        sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM,
               (const struct sockaddr *)&client_address, sizeof(client_address));

        /* exit the program if "exit" is typed */
        if (strncmp("exit", buffer, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}

int main()
{
    int sockfd = 0;
    int connfd = 0;
    int len = 0;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("ERROR socket creation\n");
        exit(EXIT_FAILURE);
    }

    bzero(&server_address, sizeof(server_address));

    /* Specify an adderss to connect to: */
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    /* Binding newly created socket to given IP and verification: */
    if ((-1) == (bind(sockfd, (SA *)&server_address, sizeof(server_address))))
    {
        perror("ERROR in bind\n");
        exit(EXIT_FAILURE);
    }

    // Now server is ready to listen and verification
    if (0 != (listen(sockfd, 5)))
    {
        perror("ERROR in listen function\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Server listening..\n");
    }

    len = sizeof(client_address);

    // Accept the data packet from client and verification
    if ((-1) == (connfd = accept(sockfd, (SA *)&client_address, &len)))
    {
        perror("ERROR in server accept\n");
        exit(EXIT_FAILURE);
    }

    /* Exchange messages with the client side: */
    ConnectToServer(connfd);

    close(sockfd);
}
