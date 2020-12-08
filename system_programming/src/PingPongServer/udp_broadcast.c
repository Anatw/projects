/*******************************************************************************
udp_broadcast (Ping Pong Server)
Written by Anat Wax, anatwax@gmail.com
Created: 25.6.20
Reviewer: Yoni Naor
*******************************************************************************/
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in */
#include <stdio.h>      /* printf */
#include <stdlib.h>
#include <string.h>     /* strcmp */
#include <sys/socket.h> /* socket */
#include <sys/types.h>
#include <unistd.h> /* close() */

#include "libserver.h"

#define MAXLINE (100)
#define PORT (4050)
#define BUF_SIZE (5)

int main()
{
    int sockfd;
    struct sockaddr_in their_addr; /* connector's address information */
    struct hostent *he;
    int numbytes;
    int broadcast = 1;
    const char *message = "Ping";
    char buffer[BUF_SIZE] = {0};
    int len = 0;

    system("clear");

    if ((he = gethostbyname("255.255.255.255")) == NULL)
    { /* get the host info */
        perror("gethostbyname");
        exit(1);
    }

    sockfd = NewSocketFD(SOCK_DGRAM);

    /* this call is what allows broadcast packets to be sent: */
    if (setsockopt(sockfd,
                   SOL_SOCKET,
                   SO_BROADCAST,
                   &broadcast,
                   sizeof broadcast) == -1)
    {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }

    their_addr.sin_family = AF_INET;   /* host byte order */
    their_addr.sin_port = htons(PORT); /* short, network byte order */
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

    if ((numbytes = sendto(sockfd,
                           message,
                           strlen(message),
                           0,
                           (struct sockaddr *)&their_addr,
                           sizeof their_addr)) == -1)
    {
        perror("ERROR in sendto inside udp broadcast\n");
        exit(EXIT_FAILURE);
    }

    printf("sent %d bytes to %s\n", numbytes, inet_ntoa(their_addr.sin_addr));

    len = sizeof(their_addr);
    if (0 > (recvfrom(sockfd,
                      buffer,
                      BUF_SIZE, 0,
                      (struct sockaddr *)&their_addr,
                      &len)))
    {
        perror("ERROR in recvfrom - inside udo broadcast\n");
        exit(EXIT_FAILURE);
    }
    printf("string inet-ntoa: %s\n", inet_ntoa(their_addr.sin_addr));
    printf("udp broadcast client recieved %s\n", buffer);

    close(sockfd);

    return (0);
}
