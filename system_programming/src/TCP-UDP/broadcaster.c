#define _DEFAULT_SOURCE

#include <arpa/inet.h>
#include <assert.h> /* assert */
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in */
#include <netinet/in.h>
#include <stdio.h> /* printf */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcmp */
#include <string.h>
#include <sys/socket.h> /* socket */
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE (100)
#define PORT ("4950")
#define SERVERPORT 4950

int main()
{
    int sockfd;
    struct sockaddr_in their_addr; /* connector's address information */
    struct hostent *he;
    int numbytes;
    int broadcast = 1;
    const char *message = "This is a message in a broadcast!";

    if ((he = gethostbyname("255.255.255.255")) == NULL)
    { /* get the host info */
        perror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

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

    their_addr.sin_family = AF_INET;         /* host byte order */
    their_addr.sin_port = htons(SERVERPORT); /* short, network byte order */
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

    if ((numbytes = sendto(sockfd,
                           message,
                           strlen(message),
                           0,
                           (struct sockaddr *)&their_addr,
                           sizeof their_addr)) == -1)
    {
        perror("sendto");
        exit(1);
    }

    printf("sent %d bytes to %s\n", numbytes,
           inet_ntoa(their_addr.sin_addr));

    close(sockfd);

    return (0);
}
