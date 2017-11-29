#include "apue.h"
#include <signal.h>
#include <fcntl.h>
#include <aio.h>

void sig_usr1(int);

int
main (int argc,const char *argv[])
{
    int             fd1,fd2,err;
    struct          aiocb read_aiocb,write_aiocb;
    struct          sigevent sigevent;
    struct          sigaction act,oact;
    unsigned char   buf[1024];
    /* 设置信号  */
    act.sa_handler = sig_usr1;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1,&act,&oact);
   /* 设置异步I/O完成后的事件 */ 
    sigevent.sigev_notify = SIGEV_SIGNAL;
    sigevent.sigev_signo = SIGUSR1;
    /* 打开文件描述符 */
    fd1 = open(argv[1],O_RDONLY);
    printf("%d\n",fd1);
    /* 初始化AIO结构 */
    read_aiocb.aio_fildes = fd1;
    read_aiocb.aio_buf = buf;
    read_aiocb.aio_nbytes = 1024;
    err = aio_read(&read_aiocb);
    printf("%d\n",err);
}

void
sig_usr1(int signo)
{
    if (signo == SIGUSR1) {
        printf("aio success");
    }
}
