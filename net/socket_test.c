#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "base_socket.h"
int main()
{
    int listenfd = -1;
    int rt = init_socket(&listenfd);
    if (rt == FAIL){
        printf("init_socket failed\n");
        return -1;
    }

    printf("init_socket success\n");
    return 0;
}

