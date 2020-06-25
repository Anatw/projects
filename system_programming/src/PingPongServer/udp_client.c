#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>     /* system() */
#include <unistd.h>     /* sleep() */
#include <netinet/in.h> /* struct sockaddr_in */
#include <string.h>     /* memset() */

#include "libserver.h"

#define PORT (4050)
#define BUF_SIZE (5)

static void SendRecieveFunc(int socket_fd, struct sockaddr_in server_addr);

int main()
{
    int socket_fd = 0;
    struct sockaddr_in server_addr;

    socket_fd = NewSocketFD(SOCK_DGRAM);

    /*printf("Enter port\n");
    scanf("%d", &port);*/

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    SendRecieveFunc(socket_fd, server_addr);

    printf("Exiting the UDP client\n");

    return (0);
}

static void SendRecieveFunc(int socket_fd, struct sockaddr_in server_addr)
{
    int counter = 0;
    int sleep_interval = 0;
    char input[BUF_SIZE];
    int length = 0;
    int input_length = 0;

    counter = RetRand();

    system("clear");

    printf("counter = %d\n", counter);

    for (; 0 != counter; --counter)
    {
        length = sizeof(server_addr);

        sleep_interval = RetRand();
        printf("Waiting %d seconds before sending a ping\n", sleep_interval);
        sleep(sleep_interval);
        sendto(socket_fd,
               "Ping",
               BUF_SIZE,
               MSG_CONFIRM,
               (const struct sockaddr *)&server_addr,
               sizeof(server_addr));

        if (0 > (input_length = recvfrom(socket_fd,
                                         (char *)input,
                                         BUF_SIZE,
                                         MSG_WAITALL,
                                         (struct sockaddr *)&server_addr,
                                         &length)))
        {
            perror("ERROR in recvfrom in udp client\n");
            exit(EXIT_FAILURE);
        }

        input[input_length] = '\0';

        printf("From the server: %s\n\n", input);
    }
}
