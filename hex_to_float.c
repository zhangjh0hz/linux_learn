/*************************************************************************
    > File Name: hex_to_float.c
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年09月19日 星期三 23时20分57秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main()
{
	char *hex_buf = "430B0000";
	long long x = strtoll(hex_buf, NULL, 16);
	printf("%lld\n", x);
	//float f = atof(hex_buf);
	//int i = strtoll(hex_buf, NULL, 16);
	float *f = (float*)&x;
	printf("%f\n", *f);
}
