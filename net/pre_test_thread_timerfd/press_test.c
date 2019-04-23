#include <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>

#define IP_BUF_SIZE 20

struct servinfo{
    char svr_ip[IP_BUF_SIZE];
    int svr_port;
};
typedef struct servinfo servinfo_t;

void print_help(char *proj)
{
    printf("%s usage.\n", proj);
    printf("eg:\n");
    printf("%s -s 127.0.0.1 -p 7788 -c 1024\n", proj);
}

void connect_fun(union sigval arg)
{
    //servinfo_t *svr_info = (servinfo_t*)arg;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    //set linger to avoid time_wait
    struct linger l;
    l.l_onoff = 1;
    l.l_linger = 0;
    if(setsockopt(fd, SOL_SOCKET, SO_LINGER, (void*)&l, sizeof(l)) < 0){
        perror("setsockopt");
        close(fd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);
    sa.sin_port = htons(7788);
    
    if(connect(fd, (struct sockaddr*)&sa, sizeof(sa)) == -1){
        perror("connect");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("client [%d] connect to svr..\n", fd);
    char buf[128] = {0};
    sprintf(buf, "hello, i am client[%d]", fd);
    send(fd, buf, strlen(buf), 0);
    //sleep(20); 

    close(fd);
}

int init_timer(timer_t *timeid)
{
    struct sigevent sigeve;
    memset(&sigeve, 0, sizeof(sigeve));
    sigeve.sigev_notify = SIGEV_THREAD;
    sigeve.sigev_value.sival_int = 11;
    sigeve.sigev_notify_function = connect_fun;

    if(timer_create(CLOCK_REALTIME, &sigeve, timeid) == -1){
        perror("timer_create");
        return -1;
    }

    struct itimerspec it;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_nsec = 1000*1000;
    it.it_value.tv_sec = 3;
    it.it_value.tv_nsec = 0;

    if(timer_settime(*timeid, 0, &it, NULL) == -1){
        perror("timer_settime failed");
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        if(!strcmp(argv[1], "?") ||
           !strcmp(argv[1], "--help") ||
           !strcmp(argv[1], "-h"))
        {
            print_help(argv[0]);
            exit(EXIT_SUCCESS);
        }
    }

    /*
    int ch = 0;
    char svr_ip_buf[IP_BUF_SIZE] = {0};
    int thread_count = 0;
    int svr_port = 0;
    while((ch = getopt(argc, argv, "s:p:c:")) != -1) {
        switch(ch){
        case 'c':
            thread_count = atoi(optarg); 
            break;
        case 's':
            sprintf(svr_ip_buf, "%s", optarg);
            break;
        case 'p':
            svr_port = atoi(optarg);
            break;
        default:
            print_help(argv[0]);
            exit(EXIT_FAILURE);
        }
    }*/

    timer_t timeid;
    init_timer(&timeid);

    pause();
    timer_delete(timeid);
    
    return 0;
}

