/*
int close(int fd);
调用成功返回0 失败返回-1
close关闭一个文件描述符,并释放进程加在该文件上的所有锁
默认情况下进程结束时自动关闭文件
*/

#include "apue.h"
#include <fcntl.h>

int
main(int argc, char const *argv[])
{
	int fd;

	if (argc != 2)
		err_exit(0,"path");

	fd = open(argv[1],O_RDONLY);

	if (fd < 0){
		err_sys("open");
	} else {
		printf("open %s in fd [%d]\n",argv[1],fd);
		if (close(fd) < 0){
			err_sys("close");
		} else{
			printf("close fd [%d]\n", fd);
		}
	}
	return 0;
}
