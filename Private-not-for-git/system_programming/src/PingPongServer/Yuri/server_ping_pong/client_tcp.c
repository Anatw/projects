#include <unistd.h> /* close */
#include <netinet/in.h> /* sockaddr_in */
#include <unistd.h>
#include "common_func.h"

#define PORT 8080 
#define MAXLINE 1024 

int main() 
{ 
    int sock = 0;
    int i = 0;
    struct sockaddr_in address;

    sock = TCPNewSocket();

    address = TCPClientServerInfo();

    ConnectToServer(sock, (struct sockaddr *)&address, sizeof(address));

    for (i = 0; i < 10; ++i)
    {
        TCP_Ping(sock);
        sleep(1);
    }

    close(sock); 

	return 0;
} 
