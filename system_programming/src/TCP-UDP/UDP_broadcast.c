/*******************************************************************************
compile with GCC (and not gd! - getaddrinfo() is not competible for c99).

If you want to enter your own message for broadcast - enter it as the second
argument when running the executable from the terminal.

TCP/UDP PingPong (Exercise 3 - UCP broadcast)
Written by Anat Wax, anatwax@gmail.com
Created: 21.6.20
Reviewer: Yaacov Evenchik
*******************************************************************************/
#include <stdio.h>      /* printf(), fprintf() */
#include <sys/socket.h> /* socket(), bind() */
#include <arpa/inet.h>  /* sockaddr_in */
#include <stdlib.h>     /* atoi(), exit() */
#include <string.h>     /* memset() */
#include <unistd.h>     /* close() */
#include <netdb.h>      /* gethostbyname() */

#define TRUE (1)
#define PORT (8002)

int main(int argc, char *argv[])
{
    int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
    char *broadcastIP;                /* IP broadcast address */
    unsigned short broadcastPort;     /* Server port */
    char *sendString;                 /* String to broadcast */
    int broadcastPermission = 1;      /* Socket opt to set permission to broadcast */
    unsigned int sendStringLen;       /* Length of string to broadcast */
    struct hostent *host_name;
    char *message = "This message was send through broadcasting\n";
    int bytes_sent = 0;
    struct hostent *host_port;

    /* Inistiate sendString - string to broadcast: */
    if (argc < 2)
    {
        sendString = message;
    }
    else
    {
        sendString = argv[1];
    }

    broadcastIP = "255.255.255.255"; /* 255 = reserved broadcasting address */

    if (NULL == (host_name = gethostbyname(broadcastIP)))
    {
        perror("ERROR on gethostbyname");
        exit(EXIT_FAILURE);
    }

    if (NULL == (host_port = gethostbyname(broadcastIP)))
    { /* get the host info */
        perror("gethostbyname");
        exit(1);
    }

    /* Create socket for sending/receiving datagrams */
    if (0 > (sock = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("ERROR in socket()\n");
        exit(EXIT_FAILURE);
    }

    /* Set socket to allow broadcast */
    if (0 > (setsockopt(sock,
                        SOL_SOCKET,
                        SO_BROADCAST,
                        &broadcastPermission,
                        sizeof(broadcastPermission))))
    {
        perror("ERROR in setsockopt()\n");
        exit(EXIT_FAILURE);
    }

    /* Construct local address structure: */
    /* Zero out structure: */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    /* Internet address family: */
    broadcastAddr.sin_family = AF_INET;
    /* Broadcast IP address: */
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);
    broadcastAddr.sin_addr = *((struct in_addr *)host_port->h_addr);
    broadcastAddr.sin_port = htons(PORT); /* Broadcast port */

    sendStringLen = strlen(sendString); /* Find length of sendString */
    while (TRUE)                        /* Run forever */
    {
        /* Broadcast sendString in datagram to clients */
        bytes_sent = (sendto(sock,
                             sendString,
                             sendStringLen,
                             0,
                             (struct sockaddr *)&broadcastAddr,
                             sizeof(broadcastAddr)));

        if (sendStringLen != bytes_sent)
        {
            printf("sendto() sent a different number of bytes than expected");
        }

        sleep(3);
        printf("%d bytes sent!\n", bytes_sent);
    }

    close(sock);

    return (0);
}
