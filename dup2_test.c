/*************************************************************************
    > File Name: dup2_test.c
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年11月02日 星期五 00时15分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd = open("./iofile", O_RDWR | O_CREAT, 0666);
	if (fd < 0) {
		fprintf(stderr, "open failure\n");
		exit(-1);
	}

	printf("-> stdout:\n");
	printf("fd = %d\n",fd);

	int recover_fd = dup(1);
	int new_fd = dup2(fd, 1);
	printf("-> file: \n");
	printf("new_fd = %d\n", new_fd);
	fflush(stdout);

	dup2(recover_fd, 1);
	close(recover_fd);

	printf("-> stdout:\n");
	printf("hello world\n");
	close(fd);
	return 0;

}

