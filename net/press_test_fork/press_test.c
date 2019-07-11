#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#define unused(x) (void)x
#define IP_BUF_SIZE 20
static int exit_flag;
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


void do_fork_func(void *arg)
{
    servinfo_t *svr_info = (servinfo_t*)arg;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    inet_pton(AF_INET, svr_info->svr_ip, &sa.sin_addr);
    sa.sin_port = htons(svr_info->svr_port);
    
    if(connect(fd, (struct sockaddr*)&sa, sizeof(sa)) == -1){
        perror("connect");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("client [%d] connect to svr..\n", fd);
    char buf[128] = {0};
    while(1) {
        memset(buf, 0, 128);
        sprintf(buf, "hello, i am client[%d]", fd);
        send(fd, buf, strlen(buf), 0);
        memset(buf, 0, 128);
        recv(fd, buf, 128, 0);
        printf("recv %s\n", buf);
    }
    close(fd);
}

void sig_handler(int sig)
{
    unused(sig);
    pid_t pid;
    while((pid = waitpid(-1, NULL, WNOHANG)) > 0){
        printf("child %d exit\n", pid);
    }
    exit_flag = 1;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_SUCCESS);
    }
    if (argc == 2) {
        if(!strcmp(argv[1], "?") ||
           !strcmp(argv[1], "--help") ||
           !strcmp(argv[1], "-h"))
        {
            print_help(argv[0]);
            exit(EXIT_SUCCESS);
        }
    }

    int ch = 0;
    char svr_ip_buf[IP_BUF_SIZE] = {0};
    int proc_count = 0;
    int svr_port = 0;
    while((ch = getopt(argc, argv, "s:p:c:")) != -1) {
        switch(ch){
        case 'c':
            proc_count = atoi(optarg); 
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
    }
    signal(SIGCHLD, sig_handler);
    servinfo_t sv_info;
    sv_info.svr_port = svr_port;
    strncpy(sv_info.svr_ip, svr_ip_buf, strlen(svr_ip_buf)+1);

    pid_t fork_array[proc_count];
    bzero(fork_array, proc_count);
    for(int i = 0; i < proc_count; i++) {
        pid_t tid;
        switch(tid = fork()){
        case 0:{
                    do_fork_func(&sv_info);
                    exit(0);
               }
        case -1:{
                    perror("fork error");
                    break;
                }
        default:{
                    continue;
                }
        }
        
        fork_array[i] = tid;
    }

    while(!exit_flag){
        sleep(1);
    }
    return 0;
}

