/*************************************************************************
    > File Name: signal_test.c
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年11月28日 星期三 15时14分07秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handle_func(int sig)
{
	switch(sig){
		case SIGINT:
			printf("you press Ctrl-c\n");
			break;
		case SIGQUIT:
			printf("get quit signal\n");
			break;
		default:
			printf("signal id = %d\n", sig);
			break;
	}
}

int main()
{
	signal(SIGINT, handle_func);
	signal(SIGABRT, handle_func);
	signal(SIGQUIT, handle_func);
	signal(SIGTERM, handle_func);
	signal(SIGHUP, handle_func);
	signal(SIGUSR1, handle_func);

	int i = 0;
	while(1){
		printf("running----%d\n", ++i);
		usleep(1*1000*100);
	}
	return 0;
}
