#include<stdio.h>
#include<sys/socket.h>

int main()
{
    int i = 0;
    for(;;) {
        printf("%d\n",++i);
    }
}