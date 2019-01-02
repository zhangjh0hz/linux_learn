/*************************************************************************
    > File Name: sigabort.c
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年12月05日 星期三 14时46分15秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

volatile int quitflag = 0;
void sighandler(int sig)
{
	if(sig == SIGABRT)
		printf("caught SIGABRT\n");
	else if (sig == SIGQUIT)
		quitflag = 1;
}

void main()
{
	signal(SIGABRT, sighandler);
	signal(SIGQUIT, sighandler);
	sigset_t emptyMask, newMask, oldMask;
	sigemptyset(&emptyMask);
	sigemptyset(&newMask);
	sigaddset(&newMask, SIGINT);
	if(sigprocmask(SIG_BLOCK, &newMask, &oldMask) == -1)
		exit(-1);
	

	printf("begin sigsuspend..\n");
	while(quitflag == 0)
		sigsuspend(&emptyMask);

	printf("end sigsuspend..and mask Ctrl-C\n");
	while(1){
		usleep(1000*1000*10);
	}
}
