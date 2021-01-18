/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

compile with GCC (and not gd! - getaddrinfo() is not competible for c99).

TCP/UDP PingPong (Exercise 1)
Written by Anat Wax, anatwax@gmail.com
Created: 18.6.20
Reviewer: Yaacov Evenchik
*******************************************************************************/
#include <stdio.h>      /* printf(), size_t */
#include <stdlib.h>     /* malloc(), free(), abs(), size_t, EXIT_STATUS */
#include <string.h>     /* size_t, atoi(), memset() */
#include <sys/wait.h>   /* wait() */
#include <sys/types.h>  /* getaddrinfo() */
#include <sys/socket.h> /* getaddrinfo() */
#include <netdb.h>      /* getaddrinfo() */
#include <unistd.h>     /* close() */

#include <netinet/in.h>

#define PORT (9002)
#define BUF_SIZE (256)

int main()
{
    int sockfd = 0;
    int network_socket = 0;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int connection_status = 0;
    char buffer[BUF_SIZE] = {0};
    int bytes_recv = 0;
    socklen_t client_length = 0;

    char *massage = "hello from tcp_server\n";

    if ((-1) == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("ERROR in socket creation\n");
        exit(EXIT_FAILURE);
    }

    memset(&client_address, 0, sizeof(client_address));

    /* Specify an adderss to connect to using the socket: */
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if ((-1) == bind(sockfd, (const struct sockaddr *)&server_address, sizeof(server_address)))
    {
        perror("an error has occured in bind function\n");
        exit(EXIT_FAILURE);
    }

    client_length = sizeof(client_address);

    bytes_recv = recvfrom(sockfd, (char *)buffer, BUF_SIZE, MSG_WAITALL,
                          (struct sockaddr *)&client_address, &client_length);

    buffer[bytes_recv] = '\0';

    printf("data receieved:\n%s\n", buffer);

    sendto(sockfd, (const char *)massage, strlen(massage), MSG_CONFIRM,
           (const struct sockaddr *)&client_address, sizeof(client_address));

    /*close(sockfd);*/

    return (0);
}
