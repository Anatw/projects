/******************************************************************************
 *	Title:		Common func header
 *	Authour:	Yurri Yashchuk
 *	Reviewer: 	Lior Cohen
 *	Version:	22.06.2020.0
 ******************************************************************************/
#ifndef __TCP_UDP_RD8586_H__
#define __TCP_UDP_RD8586_H__

/* Create a new UDP socket */
int UDPNewSocket();

/* Create a new TCP socket */
int TCPNewSocket();

/* Initilize UDP Server  sockaddr_in*/
struct sockaddr_in UDPServerInfo(int port);

/* Initilize TCP Server  sockaddr_in*/
struct sockaddr_in TCPServerInfo(int port);

/* Initilize TCP Client  sockaddr_in*/
struct sockaddr_in TCPClientServerInfo();

/* Binding the socket to a server address */
int BindSocket(int socket_fd, const struct sockaddr *server_addr, size_t length);

/* Connect the server socket to client address */
int ConnectToServer(int sock, const struct sockaddr *serv_addr, size_t length);

/* Data packet from TCP client to server */
int AcceptData(int sock, struct sockaddr_in address);

/* UPD send ping */
void UDP_Ping(int sockfd, struct sockaddr_in address);

/* UPD send pong*/
void UDP_Pong(int sockfd, struct sockaddr_in address);

/* TCP send ping*/
void TCP_Ping(int sock);

/* TCP send pong*/
void TCP_Pong(int sock);

/* UDP broadcast ping*/
void UDP_Broadcast(int sockfd, struct sockaddr_in address);

#endif /* __TCP_UDP_RD8586_H__ */
