#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int main()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    printf("%ld,  %ld",t.tv_sec, t.tv_usec);

    printf("Hello world\n");
    return 0;
}

