/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer: 
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
    /* UDP broadcasting variables */
    int udp_broad_fd = 0;
    /* std input variables */
    int tcp_stdin_fd = 0;
    int bits_written = 0;

    fd_set list_set;
    fd_set primary_list_set;
    int max_fd = 0;
    int ready_fd = 0;
    char buffer[BUF_SIZE];
    char *message = "Pong";
    socklen_t len;
    int i = 0;
    /* Variables to log if nothing specific happened for amount of time: */
    int need_check_timer = 0;
    clock_t timer_start_t = 0;
    clock_t timer_end_t = 0;
    struct timespec timer_start;
    struct timespec timer_finish;
    double timer_elapsed = 0;

    /************************** socket initiating: ********************************/

    /* Initializing the TCP address socket: */
    tcp_fd = NewSocketFD(SOCK_STREAM);
    server_address = UpdateServerInfo(PORT);

    if (0 > (bind(tcp_fd, (const struct sockaddr *)&server_address, sizeof(server_address))))
    {
        perror("ERROR in tcp bind\n");
        exit(EXIT_FAILURE);
    }

    listen(tcp_fd, TCP_BACKLOG);

    /* Initializing the UDP address socket: */
    udp_fd = NewSocketFD(SOCK_DGRAM);
    if (0 > (bind(udp_fd, (const struct sockaddr *)&server_address, sizeof(server_address))))
    {
        perror("ERROR in udp bind\n");
        exit(EXIT_FAILURE);
    }

    /* Initializing the UDP broadcasting address socket: */
    /*udp_broad_fd = NewUDPBroadSocket();
    int yes = 1;
    int status = setsockopt(udp_broad_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (0 > (bind(udp_broad_fd, (const struct sockaddr *)&server_address, sizeof(server_address))))
    {
        perror("ERROR in udp broadcast bind\n");
        exit(EXIT_FAILURE);
    }*/

    /* Initializing the input (TCP) address socket: */
    /*tcp_stdin_fd = NewSocketFD(SOCK_STREAM);

    if (0 > (bind(tcp_fd, (const struct sockaddr *)&server_address, sizeof(server_address))))
    {
        perror("ERROR in input (tcp) bind\n");
        exit(EXIT_FAILURE);
    }*/

    FD_ZERO(&list_set);
    max_fd = max(tcp_fd, udp_fd) + 1;
    system("clear");
    printf("\nServer starts listening...\n");

    while (TRUE)
    {
        /* Listen to all the file descriptor: */
        FD_SET(tcp_fd, &list_set);
        FD_SET(udp_fd, &list_set);
        FD_SET(udp_broad_fd, &list_set);
        FD_SET(tcp_stdin_fd, &list_set);

        if (0 == need_check_timer)
        {
            clock_gettime(CLOCK_MONOTONIC, &timer_start);
            need_check_timer = 1;
        }

        primary_list_set = list_set;

        /* Select a ready file descriptor: */
        if (0 > (select((max_fd + 1), &primary_list_set, NULL, NULL, NULL)))
        {
            perror("ERROR in select\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i <= max_fd; ++i)
        {
            if (FD_ISSET(i, &primary_list_set))
            {
                len = sizeof(server_address);
                /* Reading and writing to the TCP socket: */
                if (tcp_fd == i) /*tcp_fd = 3 */
                {
                    new_fd = accept(tcp_fd, (struct sockaddr *)&server_address, &len);
                    /* FD_SET(new_fd, &primary_list_set);*/
                    FD_SET(new_fd, &list_set);
                    printf("new fd = %d\n", new_fd);

                    if (0 > read(new_fd, buffer, BUF_SIZE))
                    {
                        perror("ERROR in tcp read\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        printf("Inside tcp_fd: server received: %s\n", buffer);
                    }

                    write(new_fd, message, BUF_SIZE);
                    FD_CLR(i, &list_set);

                    need_check_timer = 0;
                }
                /* Reading and writing to the UDP socket: */
                else if (udp_fd == i)
                {
                    recvfrom(udp_fd,
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

                    need_check_timer = 0;
                }
            }
            if (FD_ISSET(i, &primary_list_set))
            {
                if (new_fd == i) /* new_fd = 7 */
                {
                    printf("inside tcp_list - i = %d\n", i);
                    /*    if (0 > (new_fd = accept(tcp_fd, (struct sockaddr *)&server_address, &len)))
                    {
                        perror("ERROR in tcp_list");
                        exit(EXIT_FAILURE);
                    }*/
                    if (0 > read(new_fd, buffer, BUF_SIZE))
                    {
                        perror("ERROR in tcp read\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        printf("Inside tcp_list: server received: %s\n", buffer);
                    }
                    printf("BeFORE WRITE!\n");
                    write(new_fd, message, BUF_SIZE);

                    need_check_timer = 0;
                }
            }

            if (new_fd > max_fd)
            {
                max_fd = new_fd;
            }
        }

        clock_gettime(CLOCK_MONOTONIC, &timer_finish);
        timer_elapsed = (timer_finish.tv_sec - timer_start.tv_sec);

        if (7 <= timer_elapsed)
        {
            printf("Nothing was receieved in server in the past 7+ seconds\n");
            need_check_timer = 0;
        }
    }

    close(new_fd);

    return (0);
}

