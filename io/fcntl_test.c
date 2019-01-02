/*************************************************************************
    > File Name: fcntl_test.c
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年11月26日 星期一 22时38分52秒
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>

int main()
{
	int flags, accessMode;
	flags = fcntl(1, F_GETFL);
	if (flags == -1)
		perror("fcntl");
	printf("flags = %d\n",flags);
	accessMode = flags & O_ACCMODE;
	printf("accMode = %d\n", accessMode);
}
