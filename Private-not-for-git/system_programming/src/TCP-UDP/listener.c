#define _DEFAULT_SOURCE

#include <arpa/inet.h>
#include <assert.h> /* assert */
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in */
#include <netinet/in.h>
#include <stdio.h> /* printf */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcmp */
#include <string.h>
#include <sys/socket.h> /* socket */
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE (100)
#define PORT ("4950")
#define SERVERPORT 4950

int main()
{
    int socket_fd;
    char buffer[MAXLINE];
    const char *pong_message = "Pong from server";
    struct addrinfo hints, *server_info, *p;
    struct sockaddr_storage their_addr;
    int retval;

    int num_of_bytes_received = 0;
    socklen_t addr_len = sizeof(their_addr);

    printf("server loading...\n");

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; /* set to AF_INET to force IPv4 */
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; /* use my IP */

    if ((retval = getaddrinfo(NULL, PORT, &hints, &server_info)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(retval));
        exit(EXIT_FAILURE);
    }

    /* loop through all the results and bind to the first we can */
    for (p = server_info; p != NULL; p = p->ai_next)
    {
        if ((socket_fd = socket(p->ai_family, p->ai_socktype,
                                p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (bind(socket_fd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(socket_fd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind socket\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(server_info);

    while (1)
    {
        printf("server is listening...\n");

        if ((num_of_bytes_received = recvfrom(socket_fd,
                                              buffer,
                                              MAXLINE - 1,
                                              0,
                                              (struct sockaddr *)&their_addr,
                                              &addr_len)) == -1)
        {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }

        buffer[num_of_bytes_received] = '\0';
        printf("server: packet contains \"%s\"\n", buffer);
    }

    close(socket_fd);

    return (0);
}
