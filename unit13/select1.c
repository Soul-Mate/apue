#include "apue.h"
#include <fcntl.h>
#include <sys/select.h>

int
main(int argc, const char *argv[])
{
    char   buf[1024];
    int    nfds,readnum;
    fd_set readset,writeset;
    FD_ZERO(&readset);
    FD_ZERO(&writeset);
    FD_SET(STDIN_FILENO,&readset);
    FD_SET(STDOUT_FILENO,&writeset);
    for(;;){
        nfds = select(3,&readset,&writeset,NULL,NULL);
        printf("nfds = %d\n",nfds);
        if (nfds == 2) {
            if (FD_ISSET(STDIN_FILENO,&readset)) {
                readnum = read(STDIN_FILENO,buf,1024);
                write(STDOUT_FILENO,buf,readnum);
            }
        }
        sleep(1);
    }
    return 0;
}
