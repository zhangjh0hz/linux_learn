#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
int fd = -1;
int i = 0;

void end(int s)
{
    // 关闭管道
    close(fd);
    exit(-1);
}

int main()
{
    signal(SIGINT, end);
    // 建立管道
    mkfifo("my.pipe", 0666);
    // 打开管道
    fd = open("my.pipe", O_RDWR);
    // 每隔1秒写数据
    while(1) {
        read(fd, &i, 4);
        printf("%d\n", i);
    }
    return 0;
}

