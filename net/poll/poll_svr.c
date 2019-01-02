#include <stdio.h>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include "base_socket.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s port", argv[0]);
        exit(FAIL);
    }
    
    int port = atoi(argv[1]);
    if(port < 1024 || port > 65535)

}

