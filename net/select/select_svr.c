#include "base_socket.h"
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <strings.h>
#include <string.h>

static int fd_array[FD_SETSIZE];
static int maxfd = 0;
static int maxi = -1;
int get_maxfd()
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if( maxfd < fd_array[i] )
            maxfd = fd_array[i];
    }

    return maxfd+1;
}

int add_fd_to_fdarray(int fd)
{
    for(int i = 0; i < FD_SETSIZE; i++) {
        if( fd_array[i] == -1 ) {
            fd_array[i] = fd;
            maxi = i;
            return SUCCESS;  
        }
    }

    printf("error!!!fdarray to the max limit\n");
    return FAIL;
}

int main()
{
    int listenfd = -1;
    int rc = init_socket(&listenfd);
    if (rc < 0) {
        printf("init_socket failed\n");
        return -1;
    }

    printf("server started, listenfd = %d\n", listenfd);
    for(int i = 0; i < FD_SETSIZE; i++)
        fd_array[i] = -1;
    add_fd_to_fdarray(listenfd);

    while(1) {
        fd_set readfds, writefds, errfds;
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_ZERO(&errfds);

        for (int i = 0; i < maxi + 1; i++) {
            if(fd_array[i] != -1) {
                FD_SET(fd_array[i], &readfds);
            }
        }

        struct timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        int rc;
        if ((rc = select(get_maxfd(), &readfds, NULL, NULL, &timeout )) <= 0) {
            if (errno == EINTR)
                continue;
            if (errno == EINVAL) {
                printf("select get error\n");
                break;
            }

            if(rc == 0) {
                //printf("select timeout\n");
                continue;            
            }
        }

        for(int i = 0; i < maxfd; i++) {
            int fd = fd_array[i];
            if (FD_ISSET(fd, &readfds) ) {
                if (fd == listenfd) {
                    struct sockaddr_in clientaddr;
                    int clientaddr_len = sizeof(clientaddr);
                    bzero(&clientaddr, sizeof(clientaddr));
                    int clientfd = accept(fd, (struct sockaddr*)&clientaddr, (socklen_t*)&clientaddr_len);
                    if(clientfd < 0) {
                        perror("accept");
                        continue;
                    }
                    char clientip[32] = {0};
                    inet_ntop(AF_INET, &clientaddr.sin_addr, clientip, sizeof(clientip));
                    printf("client %s connected\n", clientip);

                    add_fd_to_fdarray(clientfd);
                }else {
                    char buf[512] = {0};
                    int ret = recv(fd, buf, sizeof(buf), 0);
                    if ( ret <= 0 ) {
                        printf("client is closed\n");
                        close(fd);
                        fd_array[i] = -1;
                        FD_CLR(fd, &readfds);
                    } else {
                        printf("client[%d] send: %s\n", fd, buf);
                        send(fd, buf, strlen(buf)+1, 0); 
                    }
                }
            }

            if (FD_ISSET(fd, &writefds)) {
                ;
            }

            if (FD_ISSET(fd, &errfds)) {
                printf("fd select get error\n");
            }
        }

    }


    return 0;
}



