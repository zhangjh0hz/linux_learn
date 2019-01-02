/*************************************************************************
    > File Name: sigsuspend_test.c
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年12月04日 星期二 18时50分33秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>


int main()
{
	sigset_t blockMask, emptyMask;
	sigemptyset(&blockMask);
	sigaddset(&blockMask, SIGINT);
	sigprocmask(SIG_SETMASK, &blockMask, NULL);

	printf("suspend..\n");
	sigsuspend(&blockMask);

	printf("exit..\n");

}
