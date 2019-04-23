#include <stdio.h>
#include <string.h>

int main()
{
    char buf[128] = {0};
    memcpy(&buf[0],"hello", 5);
    printf("%s\n",buf);
    return 0;
}

