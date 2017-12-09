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
    char    buf1[1024],buf2[1024];
    int     sfd,ret;
    ssize_t readn,readu;
    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if (sfd < 0) 
        perror("socket");
    bzero(&addr,sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX; 
    strncpy(addr.sun_path,SOCKNAME,sizeof(addr.sun_path) - 1);
    ret = connect(sfd,(struct sockaddr *)&addr, sizeof(struct sockaddr));
    if (ret == -1) 
        perror("connect");
    while((readu = read(STDIN_FILENO,&buf1,sizeof(buf1))) > 0) {
        write(sfd,&buf1,readu);
        bzero(&buf1,sizeof(buf1));
        while((readn = read(sfd,&buf2,sizeof(buf2))) > 0) {
            printf("%s\n",buf2);
            bzero(&buf2,sizeof(buf2));
            break;
        }
    }
    return 0;
}
