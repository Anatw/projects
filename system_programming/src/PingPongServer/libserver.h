/*******************************************************************************
libserver (ping pong server)

Written by Anat Wax, anatwax@gmail.com
Created: 25.6.20
*******************************************************************************/
#ifndef ILRD_RD8586_LIBSERVER_HPP
#define ILRD_RD8586_LIBSERVER_HPP

int NewSocketFD(int sock_type);
int NewUDPBroadSocket();
struct sockaddr_in UpdateServerInfo(int server_port);
int RetRand();

#endif /* ILRD_RD8586_LIBSERVER_HPP */
