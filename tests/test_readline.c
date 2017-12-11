#include "readline.h" 
#include <unistd.h>
#include <fcntl.h>
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, const char *argv[])
{
    if (argc != 2 ) {
        printf("useage readline file\n");
        exit(0);
    }
    int  fd,read_num;
    void *buf;
    fd = open(argv[1],O_RDONLY);
    if (fd == -1) {
        printf("open [%s] error \n",argv[1]);
        exit(0);
    }
    while(1) {
        buf = malloc(BUF_SIZE);
        read_num = readline(fd,buf,BUF_SIZE);
        if (read_num <= 0) {
            break;
        }
        printf("%s\n",(char *)buf);
        free(buf);
    }
    return 0;
}
