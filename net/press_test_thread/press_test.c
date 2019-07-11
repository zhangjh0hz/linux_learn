#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define IP_BUF_SIZE 20

struct servinfo{
    char svr_ip[IP_BUF_SIZE];
    int svr_port;
    int child_no;
};
typedef struct servinfo servinfo_t;

void print_help(char *proj)
{
    printf("%s usage.\n", proj);
    printf("eg:\n");
    printf("%s -s 127.0.0.1 -p 7788 -t 1024 -f 10\n", proj);
}

void *connect_fun(void *arg)
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

    printf("[p%d] client [%d] connect to svr..\n",svr_info->child_no, fd);
    char buf[128] = {0};
    while(1) {
        memset(buf, 0, 128);
        sprintf(buf, "hello, i am [p%d] client[%d]",svr_info->child_no, fd);
        send(fd, buf, strlen(buf), 0);
        memset(buf, 0, 128);
        recv(fd,buf, 128,0); 
        printf("recv %s\n",buf); 
    }
    sleep(40);
    close(fd);
    return 0;
}

void sig_handle(int sig)
{
    int stat;
    while(waitpid(-1, &stat, WNOHANG) > 0);
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
    int thread_count = 0;
    int svr_port = 0;
    int fork_count = 0;
    while((ch = getopt(argc, argv, "s:p:f:t:")) != -1) {
        switch(ch){
        case 't':
            thread_count = atoi(optarg); 
            break;
        case 's':
            sprintf(svr_ip_buf, "%s", optarg);
            break;
        case 'p':
            svr_port = atoi(optarg);
            break;
        case 'f':
            fork_count = atoi(optarg);
            break;
        default:
            print_help(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    signal(SIGCHLD, &sig_handle);
    for(int k = 0; k < fork_count; k++ ){
        pid_t pid = fork();
        switch(pid){
        case -1:
            perror("fork");
            //exit(EXIT_FAILURE);
            continue;
        case 0:
            {
                servinfo_t sv_info;
                sv_info.svr_port = svr_port;
                sv_info.child_no = k;
                strncpy(sv_info.svr_ip, svr_ip_buf, strlen(svr_ip_buf)+1);
    
                pthread_t thread_array[thread_count];
                bzero(thread_array, thread_count);
                for(int i = 0; i < thread_count; i++) {
                    pthread_t tid;
                    if(pthread_create(&tid, NULL, connect_fun, &sv_info) == -1){
                        perror("pthread_create failed");
                        exit(EXIT_FAILURE);
                    }
                    thread_array[i] = tid;
                }

                for(int i = 0; i < thread_count; i++){
                    pthread_join(thread_array[i], NULL);
                }
                exit(EXIT_SUCCESS);
            }
            
        default:
            continue;
        }
    }
        
    return 0;
}

