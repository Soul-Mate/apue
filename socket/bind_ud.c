#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

int
main()
{
    const char  *SOCKNAME = "/tmp/mysock";
    struct      sockaddr_un addr;
    struct      sockaddr_un *paddr = &addr;
    int         sockfd,ret;
    sockfd = socket(AF_UNIX,SOCK_STREAM,0);
    if (sockfd == -1) {
        perror("socket error");
    }
    /* init sockaddr  */
    paddr = (struct sockaddr_un *)malloc(sizeof(struct sockaddr_un));
    if (paddr == NULL) {
        perror("malloc error");
    }
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,SOCKNAME,sizeof(addr.sun_path)-1);
    /* bind socket */
    ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un));
    if (ret !=0 ) {
        perror("bind error");
    }
    ret = unlink(SOCKNAME);
    if (ret !=0 ){
        perror("unlink error");
    }
    return 0;
}
