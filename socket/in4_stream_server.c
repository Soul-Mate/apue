#include "readline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
int
main(int argc, const char *argv[])
{
    struct sockaddr_in server_addr,client_addr;
    char ip[128];
    char *p_ip = ip;
    int sfd,cfd;
    socklen_t addrlen;
    #ifndef SERVER_PORT
    #define SERVER_PORT 4000
    #endif
    sfd = socket(AF_INET,SOCK_STREAM,0);
    if (sfd < 0) {
        perror("socket error");
        exit(0);
    }
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);
    bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    listen(sfd,128); 
    for(;;) {
        addrlen = sizeof(client_addr);
        cfd = accept(sfd,(struct sockaddr *)&client_addr,&addrlen);
        p_ip = inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,p_ip,sizeof(ip));
        printf("connect client ip: %s,  port: %d\n",p_ip,ntohs(client_addr.sin_port));
        sleep(1);
    }
}
