#define _GNU_SOURCE
#include <stdio.h>
#include <sys/poll.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <signal.h>
#include "base_socket.h"

#define IN  1
#define OUT 2
#define ERR 3
#define HUP 4

struct pollop {
    int totle_con;
    int used;
    int unused_index;
    struct pollfd *pfd;
};

typedef struct pollop POLLOP;
static POLLOP fds;
static int listenfd;
int init_pollfds()
{
    fds.totle_con = 5;
    fds.used = 0;
    fds.unused_index = 0;
    fds.pfd = (struct pollfd*)malloc(sizeof(struct pollfd) * fds.totle_con);
    for (int i = 0; i < fds.totle_con; i++) {
        fds.pfd[i].fd = -1;
        fds.pfd[i].events = 0;
    }
    return SUCCESS;
}

static int add_pollfd(int fd, int pollevent)
{
    //判断，不够要扩容
    if (fds.used >= fds.totle_con) {
        int more_con = fds.totle_con << 2;
        fds.pfd = realloc(fds.pfd, sizeof(struct pollfd)*more_con);
        for (int i = fds.totle_con; i< more_con; i++) {
            fds.pfd[i].fd = -1;
            fds.pfd[i].events = 0;
        }
        fds.totle_con = more_con;
    }

    assert(fds.totle_con > fds.used);
    fds.pfd[fds.unused_index].fd = fd;
    fds.pfd[fds.unused_index].events = 0;

    if (pollevent & IN)
        fds.pfd[fds.unused_index].events |= POLLIN;
    if (pollevent & OUT)
        fds.pfd[fds.unused_index].events |= POLLOUT;
    if (pollevent & ERR)
        fds.pfd[fds.unused_index].events |= POLLERR;
    if (pollevent & HUP)
        fds.pfd[fds.unused_index].events |= POLLRDHUP;
    
    fds.used++;
    fds.unused_index++;
    //loop to find next unused_index
    /*for(int i = 0; i < fds.totle_con; i++) {
        if(fds.pfd[i].fd == -1) {
            fds.unused_index = i;
            break;
        }
    }*/

    return SUCCESS;
}

static int del_pollfd(int fd)
{
    for (int i = 0; i < fds.used; i++) {
        if (fds.pfd[i].fd == fd) {
            fds.pfd[i].fd = -1;
            fds.pfd[i].events = 0;
            fds.unused_index = i;
            --fds.used;
            break;
        }
    }

    return SUCCESS;
}

int un_init()
{
    close(listenfd);
    for (int i = 0; i < fds.totle_con; i++) {
        if(fds.pfd[i].fd != -1){
            close(fds.pfd[i].fd);
        }

    }

    free(fds.pfd);
    return SUCCESS;
}

void signal_proc(int sig)
{
    if (sig == SIGINT) {
        //Ctrl-C 退出处理
        un_init();       
        exit(0);
    }
}

void print_usage(char *arg)
{
    printf("usage: %s -p port.\n", arg);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        print_usage(argv[0]);
        exit(FAIL);
    }
    
    int ch = 0;
    int port = 0;
    while((ch = getopt(argc, argv, "p:")) != -1){
        switch(ch){
        case 'p':
            port = atoi(optarg);
            break;
        default:
            print_usage(argv[0]);
            break;
        }
    }

    if(port < 1024 || port > 65535) {
        printf("error!!! port must be in 1024~65535\n");
        exit(-1);
    }

    int rc = init_socket(port, &listenfd);
    if (rc != SUCCESS)
        exit(-1);
    
    printf("poll server started...\n");
    init_pollfds();
    add_pollfd(listenfd, IN);
    signal(SIGINT, signal_proc);
    signal(SIGQUIT, signal_proc);
    signal(SIGPIPE, SIG_IGN);
    int timeout = 1000;
    while(1) {
        int rc = poll(fds.pfd, fds.used, timeout);
        if(rc == 0)
            continue;
        if(rc < 0) {
            if (errno == EINTR || errno == EINVAL)
                continue; 
        }else {
            for (int i = 0; i < fds.used;i++) {
                if (fds.pfd[i].revents > 0) {
                    if(fds.pfd[i].revents & POLLIN) {
                        int fd = fds.pfd[i].fd;
                        if (fd == listenfd) {
                            struct sockaddr_in clientaddr;
                            bzero(&clientaddr, sizeof(struct sockaddr_in));
                            int addr_len = sizeof(struct sockaddr);
                            int acceptfd = accept(fds.pfd[i].fd, (struct sockaddr*)&clientaddr, (socklen_t*)&addr_len);
                            if (acceptfd == -1) {
                                perror("accept failed\n");
                                continue;
                            }
                            char client_ip[32] = {0};
                            inet_ntop(AF_INET, &clientaddr.sin_addr, client_ip, sizeof(client_ip));
                            printf("client[%d] connected: %s:%d\n", acceptfd, client_ip, ntohs(clientaddr.sin_port));
                            add_pollfd(acceptfd, IN);
                        }else {
                            char buf[128] = {0};
                            int rc = recv(fd, buf, 128, 0);
                            if(rc <= 0){
                                printf("client is closed\n");                                
                                close(fd);
                                del_pollfd(fd);
                            }else{
                                printf("recv client[%d]: %s\n", fd, buf);
                                send(fd, buf, strlen(buf), 0);
                            }
                        }
                    }                    
                }
            }
        }
    }
}


