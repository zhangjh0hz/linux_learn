/*************************************************************************
    > File Name: dlopen_test.c
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年12月06日 星期四 17时21分38秒
 ************************************************************************/

#include<stdio.h>
#include<dlfcn.h>
#include<unistd.h>
#include<stdlib.h>

typedef int (*add)(int,int);

int main()
{
	void *handle = dlopen("lib/libtest.so.1.0.1", RTLD_NOW);
	if (!handle) {
		printf("dlopen failed\n");
		exit(-1);
	}

	add addfunc = NULL;

	*(void **)(&addfunc) = dlsym(handle, "add");
	if (!addfunc){
		printf("get address failed.\n");
		exit(-1);
	}
	int ret = addfunc(111, 4);
	printf("ret = %d\n", ret);
	dlclose(handle);
}
