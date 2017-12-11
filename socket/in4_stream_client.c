#include "readline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

int
main(int argc, const char *argv[])
{
    const  int SERVER_PORT = 4000; 
    int    sfd;
    char   *ip = "172.17.0.1";
    struct sockaddr_in server_addr;
    /* 初始化 */
    bzero(&server_addr,sizeof(server_addr));
    /* 初始化socket */
    sfd = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    /* 将ip转换为网络字节序  */
    inet_pton(AF_INET,ip,&server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(SERVER_PORT);
    connect(sfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr_in));
    close(sfd);
    return 0;
}
