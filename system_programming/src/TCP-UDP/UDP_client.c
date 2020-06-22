/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

compile with GCC (and not gd! - getaddrinfo() is not competible for c99).

TCP/UDP PingPong (Exercise 1)
Written by Anat Wax, anatwax@gmail.com
Created: 18.6.20
Reviewer: Yaacov Evenchik
*******************************************************************************/
#include <stdio.h>      /* printf(), size_t */
#include <stdlib.h>     /* malloc(), free(), abs(), size_t, EXIT_STATUS */
#include <string.h>     /* size_t, atoi(), memset() */
#include <sys/wait.h>   /* wait() */
#include <sys/types.h>  /* getaddrinfo() */
#include <sys/socket.h> /* getaddrinfo() */
#include <netdb.h>      /* getaddrinfo() */
#include <unistd.h>     /* close() */

#include <netinet/in.h>

#define PORT ("8002")
#define BUF_SIZE (256)

int main()
{
    int socket_fd;
    char buffer[BUF_SIZE];
    struct addrinfo hints, *server_info, *i;
    struct sockaddr_storage their_addr;
    int retval;

    int num_of_bytes_received = 0;
    socklen_t addr_len = sizeof(their_addr);

    printf("server loading...\n");

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; /* AF_INET will use IPv4 protocol */
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; /* use my IP */

    if ((retval = getaddrinfo(NULL, PORT, &hints, &server_info)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(retval));
        exit(EXIT_FAILURE);
    }

    /* loop through all the results and bind to the first we can */
    for (i = server_info; i != NULL; i = i->ai_next)
    {
        if ((socket_fd = socket(i->ai_family, i->ai_socktype,
                                i->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (bind(socket_fd, i->ai_addr, i->ai_addrlen) == -1)
        {
            close(socket_fd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (i == NULL)
    {
        fprintf(stderr, "ERROR in server: failed to bind socket\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(server_info);

    while (1)
    {
        printf("server is listening...\n");

        if ((num_of_bytes_received = recvfrom(socket_fd,
                                              buffer,
                                              BUF_SIZE - 1,
                                              0,
                                              (struct sockaddr *)&their_addr,
                                              &addr_len)) == -1)
        {
            perror("ERROR in recvfrom");
            exit(EXIT_FAILURE);
        }

        buffer[num_of_bytes_received] = '\0';
        printf("server: packet contains \"%s\"\n", buffer);
    }

    close(socket_fd);
}
