#include <stdio.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include "base_socket.h"

#define E_IN    1
#define E_OUT   2
#define E_ERR   3
#define E_HUP   4
#define E_ET    5

static int listenfd;
//FIXME:epoll_event 改为动态指针，目前先用数组
#define MAX_EVENT_NUMBER 1024
struct epoll_event ev, events[MAX_EVENT_NUMBER];

int init_epollfd()
{
    int efd = epoll_create1(EPOLL_CLOEXEC);
    if (efd == -1) {
        printf("epoll create failed\n");
        return -1;
    }    
    return efd;
}

void set_noblocking(int fd)
{

    int flags = 0;
    if((flags = fcntl(fd, F_GETFL)) == -1) {
        perror("fcntl get failed\n");
        exit(EXIT_FAILURE);
    }
    flags |= O_NONBLOCK;
    if(fcntl(fd, F_SETFL, flags) == -1) {
        perror("fcntl setfl failed\n");
        exit(EXIT_FAILURE);
    }
}

int add_fd(int epollfd, int fd, int event)
{
    ev.data.fd = fd;
    if (event & E_IN)
        ev.events |= EPOLLIN;
    if (event & E_OUT)
        ev.events |= EPOLLOUT;
    if (event & E_ERR)
        ev.events |= EPOLLERR;
    if (event & E_HUP)
        ev.events |= EPOLLHUP;
    if (event & E_ET)
        ev.events |= EPOLLET;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1){
        perror("epoll_ctl: add_fd failed");
        return EXIT_FAILURE;
    }
    set_noblocking(fd);
    return EXIT_SUCCESS;
}

int del_fd(int epollfd, int fd)
{
        
    return SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s -p port\n", argv[0]);
        exit(-1);
    }

    int ch;
    char sport[6] = {0};
    while((ch = getopt(argc, argv, "p:")) != -1) {
        switch(ch) {
        case 'p':
            sprintf(sport, "%s", optarg);
            break;
        default:
            printf("unknown option: %c\n",(char)optopt);
            return -1;
        }
    }

    int port = atoi(sport);
    if(port < 1024 || port > 65535) {
        printf("error!!!port must be in 1024~65535\n");
        exit(-1);
    }
    if(init_socket(port, &listenfd) != SUCCESS){
        printf("init_sock failed\n");
        exit(-1);
    }

    printf("svr starting\n");

    int epollfd = init_epollfd();
    if( epollfd == -1 ){
        close(listenfd);
        return -1;
    }

    add_fd(epollfd, listenfd, E_IN);

    while(1){
        int nfds = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, 1000);
        if (nfds < 0){
            if(errno == EINTR){
                printf("get interupt by a signal\n");
                continue;
            }else if(errno == EINVAL){
                printf("get invalid error\n");
                break;
            }
        }else if( nfds == 0 ){
            printf("epoll timeout\n ");
            continue;
        }else{
            for( int i = 0; i < nfds; i++ ){
                if(events[i].data.fd == listenfd)
                {
                    while(1){
                        struct sockaddr_in clientaddr;
                        int client_len = sizeof(struct sockaddr);
                        bzero(&clientaddr, sizeof(clientaddr));
                        int acceptfd = accept(listenfd, (struct sockaddr*)&clientaddr, (socklen_t*)&client_len);
                        if(acceptfd < 0) {
                            perror("accept error");
                            break;
                        }  
                        char client_ip[32] = {0};
                        inet_ntop(AF_INET, &clientaddr.sin_addr, client_ip, sizeof(client_ip));
                        printf("client[%d] %s:%d connected\n", acceptfd, client_ip, ntohs(clientaddr.sin_port));
                        add_fd(epollfd, acceptfd, E_IN|E_ET);
                    }
                }else {
                    if(events[i].events & EPOLLIN) {
                        int fd = events[i].data.fd;
                        char buf[128] = {0};
                        int nread = 0;
                        for(;;) {
                            bzero(buf, 128);
                            nread = read(fd, buf, sizeof(buf));
                            if(nread < 0) {
                                if(errno == EAGAIN || errno == EWOULDBLOCK){
                                    printf("read get EAGAIN\n");
                                    break;
                                }else if(errno == EINTR) {
                                    printf("read get EINTR\n");
                                    continue;
                                }else if(errno == ECONNRESET){
                                    printf("get reset\n");
                                    del_fd(epollfd, fd);
                                    close(fd);
                                    break;
                                }
                            }else if( nread == 0 ) {
                                printf("client closed\n");
                                del_fd(epollfd, fd);
                                close(fd);
                                break;
                            }else {
                                printf("recv from client[%d]: %s\n", fd, buf);
                            }
                        }
                    }
                }
            }

        }
    }
    return 0;
}
