#include <netinet/in.h> /* sockaddr_in */
#include <unistd.h> /* close */
#include <unistd.h>
#include "common_func.h"
  
int main() 
{ 
    int i = 10;
    int sock = 0;
    struct sockaddr_in address;

    sock = UDPNewSocket();

    address = TCPServerInfo(8080);

    for (i = 0; i < 10; ++i)
    {
    	UDP_Ping(sock, address);
        sleep(1);
    }

    close(sock); 

    return 0; 
} 
