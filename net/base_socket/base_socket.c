#include "base_socket.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>

int init_socket(int *listenfd)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        err_exit("socket");
    }

    int flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(7788);
    if (bind(fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        close(fd);
        err_exit("bind");
    }
    
    if (listen(fd, SOMAXCONN) < 0){
        close(fd);
        err_exit("listen");
    }
    
    *listenfd = fd;

    return SUCCESS;
}


