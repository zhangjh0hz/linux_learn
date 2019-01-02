#ifndef _BASE_SOCKET_H
#define _BASE_SOCKET_H

#include <error.h>
#include <unistd.h>

#define FAIL -1
#define SUCCESS 0

#define err_exit(p) \
    do { \
        perror(p); \
        return FAIL; \
    }while(0);

int init_socket(int *listenfd);
int close_socket(int fd);
#endif

