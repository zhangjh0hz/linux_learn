/*************************************************************************
    > File Name: signal_mask.c
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年11月29日 星期四 11时28分56秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void sig_handler(int sig)
{
	printf("get a sig = %d\n", sig);
}

void main()
{
	signal(SIGINT, sig_handler);
	sigset_t blockSet, preMask;
	sigemptyset(&blockSet);
	sigaddset(&blockSet, SIGINT);

	if (sigprocmask(SIG_BLOCK, &blockSet, &preMask) == -1){
		perror("sigprocmask");
		exit(-1);
	}

	usleep(1000*1000* 5);
	
	if (sigprocmask(SIG_SETMASK, &preMask, NULL) == -1){
	perror("sigprocmask");
		exit(-1);
	}
	while(1){
		usleep(1000*100);
	}
}
