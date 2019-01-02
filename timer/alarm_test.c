/*************************************************************************
    > File Name: alarm_test.c
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年11月30日 星期五 14时54分03秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>


int main()
{
	printf("prev ret = %d\n", alarm(3));
	sleep(5);
	printf("after sleep\n");
	while(1){
		usleep(1000*1000);
	}
}
