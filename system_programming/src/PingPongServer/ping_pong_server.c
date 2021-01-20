/*******************************************************************************
Ping Pong Server

Written by Anat Wax, anatwax@gmail.com
Created: 25.6.20
*******************************************************************************/
#include <stdio.h>      /* printf(), size_t */
#include <stdlib.h>     /* malloc(), free(), abs(), size_t */
#include <assert.h>     /* assert() */
#include <stddef.h>     /* offsetof(), size_t */
#include <time.h>       /* time, size_t, srand() */
#include <string.h>     /* size_t, atoi(), memset() */
#include <sys/wait.h>   /* wait() */
#include <fcntl.h>      /* For O_* constants */
#include <sys/types.h>  /* TCP/UDP functions */
#include <sys/socket.h> /* TCP/UDP functions */
#include <math.h>       /* math functions */
#include <unistd.h>     /* close(), read(), write() */
#include <netinet/in.h> /* sockaddr_in */

#include "libserver.h"

#define BUF_SIZE (5)
#define PORT (4050)
#define TCP_BACKLOG (10)
#define TRUE (1)

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int main()
{
    /* TCP variables */
    int tcp_fd = 0;
    struct sockaddr_in server_address;
    int new_fd = 0;
    /* UDP variables */
    int udp_fd = 0;
    int recieved_bytes = 0;

    fd_set list_set;
    fd_set primary_list_set;
    int max_fd = 0;
    int ready_fd = 0;
    char buffer[BUF_SIZE];
    char message[BUF_SIZE] = "Pong";
    socklen_t len;
    int i = 0;
    /* Variables to log if nothing specific happened for amount of time: */
    struct timeval original_timer;
    struct timeval backup_timer;
    int check_action = 0;

    /************************ socket initiating: ******************************/

    /* Initializing the TCP address socket: */
    tcp_fd = NewSocketFD(SOCK_STREAM);
    server_address = UpdateServerInfo(PORT);

    if (0 > (bind(tcp_fd, (const struct sockaddr *)&server_address, sizeof(server_address))))
    {
        perror("ERROR in tcp bind\n");
        exit(EXIT_FAILURE);
    }

    if (0 > (listen(tcp_fd, TCP_BACKLOG)))
    {
        perror("ERROR in listen\n");
        exit(EXIT_FAILURE);
    }

    /* Initializing the UDP address socket: */
    udp_fd = NewSocketFD(SOCK_DGRAM);
    server_address = UpdateServerInfo(PORT);
    if (0 > (bind(udp_fd, (const struct sockaddr *)&server_address, sizeof(server_address))))
    {
        perror("ERROR in udp bind\n");
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&list_set);
    max_fd = max(tcp_fd, udp_fd);

    /* Listen to all the file descriptor: */
    FD_SET(tcp_fd, &list_set);
    FD_SET(udp_fd, &list_set);

    system("clear");

    backup_timer.tv_sec = 7;
    backup_timer.tv_usec = 0;

    printf("\nServer starts listening...\n");

    while (TRUE)
    {
        primary_list_set = list_set;
        original_timer = backup_timer;

        /* Select a ready file descriptor: */
        check_action = select((max_fd + 1), &primary_list_set, NULL, NULL, &original_timer);
        if (0 > check_action)
        {
            perror("ERROR in select\n");
            exit(EXIT_FAILURE);
        }
        else if (0 == check_action)
        {
            printf("Server reporting: no incomming messages the past 7 seconds\n");
        }

        for (i = 0; i <= max_fd; ++i)
        {
            if (FD_ISSET(i, &primary_list_set))
            {
                /* Reading and writing to the UDP socket: */
                if (udp_fd == i)
                {
                    recieved_bytes = recvfrom(udp_fd,
                                              buffer,
                                              BUF_SIZE,
                                              MSG_WAITALL,
                                              (struct sockaddr *)&server_address,
                                              &len);

                    printf("Inside udp_fd: server received: %s\n", buffer);

                    sendto(udp_fd,
                           message,
                           BUF_SIZE,
                           MSG_CONFIRM,
                           (const struct sockaddr *)&server_address,
                           sizeof(server_address));
                }
                /* Reading and writing to the TCP socket: */
                else if (tcp_fd == i) /*tcp_fd = 3 */
                {
                    len = sizeof(server_address);

                    new_fd = accept(tcp_fd, (struct sockaddr *)&server_address, &len);
                    if (0 > new_fd)
                    {
                        perror("inside tcp_fd connection - ERROR in accept\n");
                        exit(EXIT_FAILURE);
                    }

                    FD_SET(new_fd, &list_set);

                    bzero(buffer, BUF_SIZE);

                    if (0 > read(new_fd, buffer, BUF_SIZE))
                    {
                        perror("ERROR in tcp read\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        printf("Inside tcp_fd: server received: %s\n", buffer);

                        if (0 == (strcmp(buffer, "ping")) ||
                            0 == (strcmp(buffer, "Ping")))
                        {
                            printf("Sending 'pong' to client\n");
                            if (0 > (write(new_fd, message, BUF_SIZE)))
                            {
                                perror("Inside tcp_fd - ERROR in write\n");
                                FD_CLR(i, &list_set);
                                close(i);
                            }
                        }
                        else if (0 == (strcmp(buffer, "quit")) ||
                                 (0 == (strcmp(buffer, "exit"))))
                        {
                            printf("Server exiting...\n");
                            return (0);
                        }
                    }

                    if (max_fd < new_fd)
                    {
                        max_fd = new_fd;
                    }
                }
                else
                {
                    if (0 > read(new_fd, buffer, BUF_SIZE))
                    {
                        perror("ERROR in tcp read\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        printf("Inside tcp_list: server received: %s\n", buffer);

                        if (0 == (strcmp(buffer, "ping")) ||
                            0 == (strcmp(buffer, "Ping")))
                        {
                            printf("Sending 'pong' to client\n");
                            if (0 > (write(new_fd, message, BUF_SIZE)))
                            {
                                perror("Inside tcp_fd - ERROR in write\n");
                                FD_CLR(i, &list_set);
                                close(i);
                            }
                        }
                        else if (0 == (strcmp(buffer, "quit")) ||
                                 (0 == (strcmp(buffer, "exit"))))
                        {
                            printf("Server exiting...\n");
                            return (0);
                        }
                    }
                }
            }
        }
    }

    return (0);
}
