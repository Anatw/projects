
#include <stdlib.h>     /* exit */
#include <string.h>     /* strlen */

#include <netinet/in.h> /* sockaddr_in */
#include <unistd.h>     /* close */
#include <stdio.h>      /* printf, perror */

#include "common_func.h"


#define MYPORT "8080"


int main()
{
    int i = 10;
    int sock = 0;
    struct sockaddr_in address;
    char *ping = "Ping Broadcast"; 
    int enable = 1;
    socklen_t length = 0;

    sock = UDPNewSocket();

    address = TCPServerInfo(8080);

    if (-1 == setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &enable,
                   sizeof enable))
    {
        perror("setsockopt"); 
		return EXIT_FAILURE;
    }

    length = sizeof(address);
    for (i = 0; i < 10; ++i)
    {
        if (-1 == sendto(sock, (const char *)ping, strlen(ping),  
            MSG_CONFIRM, (const struct sockaddr *) &address, length))
        {
            perror("sendto failed"); 
            return EXIT_FAILURE;
        } 
        sleep(1);
    }

    close(sock); 

    return 0; 
}