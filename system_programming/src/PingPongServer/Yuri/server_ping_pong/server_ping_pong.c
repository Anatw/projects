#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>

#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h> /* select */
#include <string.h>     /* strlen */
#include <stdio.h>      /* perror, printf*/
#include "common_func.h"

#define PORT 4050
#define MAXLINE 1024
#define TRUE 1

int max(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

int main()
{
    /*  int master_socket_tcp = 0;
    int new_socket = 0;
    int client_socket_tcp[30];
    int udp_socket = 0;
    int max_client = 30;
    int index = 0;
    int socket_descriptor = 0;
    int max_descriptor = 0;
    int activity = 0;
    struct timeval tv;
    char buffer[MAXLINE] = {0};
    fd_set rset;*/

    struct sockaddr_in servaddr;

    /* initialise TCP Client sockets to 0 so not checked   */
    for (index = 0; index < max_client; ++index)
    {
        client_socket_tcp[index] = 0;
    }

    /* create listening TCP Master socket */
    master_socket_tcp = TCPNewSocket();
    bzero(&servaddr, sizeof(servaddr));
    servaddr = TCPServerInfo(PORT);
    BindSocket(master_socket_tcp, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    if (listen(master_socket_tcp, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    /* create UDP socket */
    udp_socket = UDPNewSocket();
    BindSocket(udp_socket, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    FD_ZERO(&rset);

    printf("socket_descriptor = %d", socket_descriptor);
    while (TRUE)
    {
        FD_SET(master_socket_tcp, &rset);
        FD_SET(udp_socket, &rset);
        FD_SET(STDIN_FILENO, &rset);
        max_descriptor = master_socket_tcp;

        for (index = 0; index < max_client; ++index)
        {
            socket_descriptor = client_socket_tcp[index];
            if (socket_descriptor > 0)
            {

                FD_SET(socket_descriptor, &rset);
            }
            max_descriptor = max(max_descriptor, socket_descriptor);
        }

        max_descriptor = max(max_descriptor, udp_socket);
        max_descriptor = max(max_descriptor, STDIN_FILENO) + 1;
        tv.tv_sec = 7;
        tv.tv_usec = 0;
        activity = select(max_descriptor, &rset, NULL, NULL, &tv);
        if ((activity < 0) && (errno != EINTR))
        {
            printf("select error");
            exit(EXIT_FAILURE);
        }
        if (0 == activity)
        {
            printf("no action in 7 seconds\n");
            return 0;
        }

        if (FD_ISSET(STDIN_FILENO, &rset))
        {
            scanf("%s", buffer);
            if (0 == strcmp("q", buffer))
            {
                return 0;
            }
            printf("%s\n", buffer);
        }

        if (FD_ISSET(udp_socket, &rset))
        {
            UDP_Pong(udp_socket, servaddr);
        }

        if (FD_ISSET(master_socket_tcp, &rset))
        {
            new_socket = AcceptData(master_socket_tcp, servaddr);
            TCP_Pong(new_socket);

            /* add new socket to array of sockets  */
            for (index = 0; index < max_client; ++index)
            {
                /* if position is empty   */
                if (client_socket_tcp[index] == 0)
                {
                    client_socket_tcp[index] = new_socket;
                    break;
                }
            }
        }
        else
        {
            for (index = 0; index < max_client; ++index)
            {
                socket_descriptor = client_socket_tcp[index];
                if (FD_ISSET(socket_descriptor, &rset) && client_socket_tcp[index] != 0)
                {
                    if ((read(socket_descriptor, buffer, 1024)) == 0)
                    {
                        close(socket_descriptor);
                        client_socket_tcp[index] = 0;
                        FD_CLR(socket_descriptor, &rset);
                    }
                    else
                    {
                        char *pong = "Pong";
                        printf("%s \n", buffer);
                        if (-1 == send(socket_descriptor, pong, strlen(pong), 0))
                        {
                            perror("send");
                            exit(0);
                        }
                    }
                }
            }
        }
    }
}
