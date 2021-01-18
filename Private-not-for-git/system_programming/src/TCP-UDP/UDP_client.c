/*******************************************************************************
compile with GCC (and not gd! - getaddrinfo() is not competible for c99).

TCP/UDP PingPong (Exercise 1)
Written by Anat Wax, anatwax@gmail.com
Created: 18.6.20
Reviewer: Yaacov Evenchik
*******************************************************************************/
#include <stdio.h>      /* printf(), size_t */
#include <stdlib.h>     /* EXIT_STATUS */
#include <string.h>     /* memset(), strlen() */
#include <sys/wait.h>   /* wait() */
#include <sys/types.h>  /* getaddrinfo() */
#include <sys/socket.h> /* socket API functions */
#include <netdb.h>      /* getaddrinfo() */
#include <unistd.h>     /* close() */

#include <netinet/in.h>

#define PORT (9002)
#define BUF_SIZE (256)
#define NUM_OF_PORTS (5)

int main()
{
    int sockfd = 0;
    struct sockaddr_in server_address;
    socklen_t client_length = 0;
    int bytes_recv = 0;
    char buffer[BUF_SIZE] = {0};

    char *massage = "This massage was sent from the client process";

    if ((-1) == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("ERROR in socket creation\n");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    sendto(sockfd, massage, strlen(massage), MSG_CONFIRM,
           (const struct sockaddr *)&server_address, sizeof(server_address));

    bytes_recv = recvfrom(sockfd, buffer, BUF_SIZE, MSG_WAITALL,
                          (struct sockaddr *)&server_address, &client_length);

    buffer[bytes_recv] = '\0';

    printf("massage received from server:\n%s", buffer);

    close(sockfd);

    return (0);
}
