/******************************************************************************
 *	Title:		Common func
 *	Authour:	Yurri Yashchuk
 *	Reviewer: 	Lior Cohen
 *	Version:	19.06.2020.0
 ******************************************************************************/


#include <string.h>     /* strlen, memset */
#include <strings.h>    /* bzero */
#include <unistd.h>     /* read, write*/
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>  /* in_addr_t */ 
#include <netinet/in.h> /* sockaddr_in */
#include <stdio.h>      /* printf,  perror */
#include <stdlib.h>     /* sizeof, exit */

#include "common_func.h"

#define PORT    8080 

int UDPNewSocket()
{
    int sock = 0;

	if (-1 == (sock = socket(AF_INET, SOCK_DGRAM, 0))) 
	{ 
		perror("Can't create a socket"); 
		return EXIT_FAILURE;
	} 

    return sock;
}

int TCPNewSocket()
{
    int sock = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        perror("Socket creation error"); 
        return EXIT_FAILURE;
    } 
   
    return sock;
}

struct sockaddr_in UDPServerInfo(int port)
{
    struct sockaddr_in address;

    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    return address;
}

struct sockaddr_in TCPServerInfo(int port)
{
    struct sockaddr_in address;

    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    return address;
}


struct sockaddr_in TCPClientServerInfo()
{
    struct sockaddr_in server;

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);


    return server;
}


int BindSocket(int socket_fd, const struct sockaddr *server_addr, size_t length)
{
    if (-1 == bind(socket_fd, server_addr, length)) 
    { 
        perror("bind failed"); 
		return EXIT_FAILURE;
    } 

    return 0;
}

int ConnectToServer(int sock, const struct sockaddr *serv_addr, size_t length)
{
    if (connect(sock, serv_addr, length) < 0) 
    { 
        perror("Connection Failed"); 
        return EXIT_FAILURE;
    } 

    return 0;
}

int AcceptData(int sock, struct sockaddr_in address)
{
    int length = sizeof(address);

    int new_socket = 0;
    
    if ((new_socket = accept(sock, (struct sockaddr *)&address,  
                       (socklen_t*)&length))<0) 
    { 
        perror("accept"); 
		return EXIT_FAILURE;
    } 

    return new_socket;
}

void UDP_Ping(int sockfd, struct sockaddr_in address)
{
    char buffer[1024] = {0}; 
    char *pong = "Ping"; 
    socklen_t length = 0;
    int pos = 0;

    length = sizeof(address);

    if (-1 == sendto(sockfd, (const char *)pong, strlen(pong),  
    MSG_CONFIRM, (const struct sockaddr *) &address, length))
    {
        perror("sendto failed"); 
        exit(0);
    } 

    if (-1 == (pos = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, 
        ( struct sockaddr *) &address, &length)))
    {
        perror("recvfrom failed"); 
        exit(0);
    }
    
    buffer[pos] = '\0';
    printf("%s\n", buffer); 
    bzero(buffer, sizeof(buffer));
}

void UDP_Pong( int sockfd, struct sockaddr_in address)
{
    char buffer[1024] = {0}; 
    char *ping = "Pong"; 
    int pos = 0;
    socklen_t length = sizeof(address);

    
    if (-1 == (pos = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, 
        ( struct sockaddr *) &address, &length)))
    {
        perror("recvfrom failed"); 
        exit(0);
    }

    buffer[pos] = '\0';

    printf("%s\n", buffer); 
    bzero(buffer, sizeof(buffer));

    if (-1 == sendto(sockfd, (const char *)ping, strlen(ping),  
    MSG_CONFIRM, (const struct sockaddr *) &address, length))
    {
        perror("sendto failed"); 
        exit(0);
    } 
}

void UDP_Broadcast( int sockfd, struct sockaddr_in address)
{
    char *ping = "Pong"; 
    socklen_t length = sizeof(address);
    
    if (-1 == sendto(sockfd, (const char *)ping, strlen(ping),  
    MSG_CONFIRM, (const struct sockaddr *) &address, length))
    {
        perror("sendto failed"); 
        exit(0);
    } 
}




void TCP_Ping(int sock)
{
    char buffer[1024] = {0}; 
    char *ping = "Ping"; 

    if (-1 == send(sock , ping , strlen(ping) , 0)) 
    {
        perror("send");
        exit(0);
    }
    if (-1 == read( sock , buffer, sizeof(buffer)))
    {
        perror("read");
        exit(0);
    }

    printf("%s\n", buffer); 
}



void TCP_Pong(int sock)
{
    char buffer[1024] = {0}; 
    char *pong = "Pong"; 

    if (-1 == read( sock , buffer, sizeof(buffer)))
    {
        perror("read");
        exit(0);
    }

    printf("%s \n", buffer); 

    if (-1 == send(sock , pong , strlen(pong) , 0)) 
    {
        perror("send");
        exit(0);
    }
}


