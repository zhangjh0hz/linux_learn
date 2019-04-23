#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>
int main()
{
    int port = 0;
    char *hostname = "192.168.33.226";
    struct addrinfo hints = { 0 }, *res = 0, *cur;
    int error;
    char sport[16];
    const char *node = 0, *service = "0";

    if (port > 0) {
        snprintf(sport, sizeof(sport), "%d", port);
        service = sport;
    }
    if ((hostname) && (hostname[0] != '\0') && (hostname[0] != '?')) {
        node = hostname;
    }
    hints.ai_socktype = 2;
    hints.ai_family   = 0;
    hints.ai_flags    = 0;
    if ((error = getaddrinfo(node, service, &hints, &res))) {
        res = NULL;
    }

    cur = NULL;
    char ipbuf[24];
    memset(ipbuf, 0, sizeof(ipbuf));
    for (cur = res;cur!=NULL;cur=cur->ai_next){
        struct sockaddr_in * addr=(struct sockaddr_in*)cur->ai_addr;
        printf("%s\n",inet_ntop(AF_INET,&addr->sin_addr,ipbuf,16));
    }

    return 0;
}

