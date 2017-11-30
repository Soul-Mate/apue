#include "apue.h"

int main(int argc, char *argv[])
{
    char *buf;
    int  pid,pfd[2];
    
    if (pipe(pfd) < 0) {
        err_sys("pipe eror");
    }
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        close(pfd[1]);
        buf = (char *)malloc(5);
        if (read(pfd[0],buf,5) != 5) {
            err_sys("read error");
        } else {
            printf("%s\n",buf);
        }
        sleep(3);
    }
    close(pfd[0]);
    write(pfd[1],"hello",5);
    waitpid(pid,NULL,0); 
    return 0;
}
