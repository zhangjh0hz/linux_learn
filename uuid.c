/*************************************************************************
    > File Name: uuid.c
# Author: ZJH
# mail: 1098706006@qq.com
    > Created Time: 2018年11月12日 星期一 14时44分14秒
 ************************************************************************/

#include<stdio.h>
#include<uuid/uuid.h>

int main()
{
	uuid_t uuid;
	char str[36];

	uuid_generate(uuid);
	uuid_unparse(uuid, str);

	printf("%s\n",str);
	return 0;
}
