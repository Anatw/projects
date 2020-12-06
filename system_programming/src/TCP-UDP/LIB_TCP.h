#ifndef LIB_TCP_H
#define LIB_TCP_H

#include <sys/types.h>  /* getaddrinfo() */
#include <sys/socket.h> /* getaddrinfo() */
#include <netdb.h>      /* getaddrinfo() */

typedef struct connectionInfo portInfo_t;

portInfo_t *InitAddrInfo(struct addrinfo *hints, const char *port,
                         struct addrinfo *servinfo);

int GetSockfd(portInfo_t *ret);

void CloseAndFree(struct addrinfo *info, int sockfd);

#endif /* LIB_TCP_H */
