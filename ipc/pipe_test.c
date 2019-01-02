#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    int pipefd[2] = {0};
    if (pipe2(pipefd, O_CLOEXEC) == -1){
        printf("error info = %s", strerror(errno));
        return -1;
    }

    pid_t pid = 0;
    switch(pid = fork()){
    case -1:
        printf("fork error\n");
        break;
    case 0:
        printf("child process\n");
        close(pipefd[0]);
        char buf[25] = "hello father";
        while(1){
            write(pipefd[1], buf, strlen(buf));
            sleep(1);
        }
        exit(0);
    default:
        printf("parent process\n");
        close(pipefd[1]);
        while(1){
            char buf2[25] = {0};
            read(pipefd[0], buf2, sizeof(buf2));
            printf("read %s\n",  buf2);
        }
        int wait_status = 0;
        wait(&wait_status);
        exit(0);

    }


    return 0;
}

