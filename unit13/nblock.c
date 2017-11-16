#include "apue.h"
#include <fcntl.h>
#include <errno.h>
#define BUFSIZE 1024
#define AGAIN_COUNT 5
int
main(void)
{
    char *buf;
    int  rn, flag, count;
    buf = (char *)malloc(BUFSIZE);
    flag = fcntl(STDIN_FILENO,F_GETFL,0);
    flag |= O_NONBLOCK;
    fcntl(STDIN_FILENO,F_SETFL,flag);
    for(;;) {
        errno = 0;
        rn = read(STDIN_FILENO,buf,BUFSIZE);
        if (errno == EAGAIN) {
            count++;
            if (count == AGAIN_COUNT) {
                printf("read timeout\n");
                exit(1);
            }
            printf("again: %d count\n",count);
            sleep(1);
            continue;
        }
    }
    return 0;
}
