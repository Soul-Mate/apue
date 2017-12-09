#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

int
main()
{
    const char * SOCKNAME = "/tmp/mysock";
    struct  sockaddr_un addr;
    char    buf[1024];
    int     sfd,cfd,ret;
    ssize_t readn;
    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if (sfd < 0) 
        perror("socket");
    bzero(&addr,sizeof(struct sockaddr_un));
    unlink(SOCKNAME);
    addr.sun_family = AF_UNIX; 
    strncpy(addr.sun_path,SOCKNAME,sizeof(addr.sun_path) - 1);
    ret = bind(sfd,(struct sockaddr *)&addr, sizeof(struct sockaddr));
    if (ret == -1) 
        perror("bind");
    ret = listen(sfd,0);
    if (ret == -1)
        perror("listen");
    for(;;) {
        cfd = accept(sfd,NULL,NULL);
        if (cfd == -1) 
            perror("accept");
        printf("%s\n","连接成功");
        while((readn = read(cfd,&buf,sizeof(buf))) > 0) {
            write(cfd,&buf,readn);
            printf("%s\n",buf);
            bzero(&buf,sizeof(buf));
        }
    }
    return 0;
}
