#ifndef ILRD_RD8586_LIBSERVER_HPP
#define ILRD_RD8586_LIBSERVER_HPP

int NewSocketFD(int sock_type);
int NewUDPBroadSocket();
struct sockaddr_in UpdateServerInfo(int server_port);
int RetRand();

#endif /* ILRD_RD8586_LIBSERVER_HPP */
