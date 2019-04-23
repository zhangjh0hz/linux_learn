#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    close(0);
    //close(1);
    close(2);

    int x = open("/dev/null", O_RDWR);
    printf("x = %d\n", x);
    x = open("/dev/null", O_RDWR);
    printf("x = %d\n", x);
    x = open("/dev/null", O_RDWR);
    printf("x = %d\n", x);
    return 0;
}

