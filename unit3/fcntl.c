/*fcntl可更改打文件的属性
#include <fcntl.h>
int fcntl(int fd,int cmd, int arg);
cmd = F_DUPFD 或 F_DUPFD_CLOEXEC 复制一个已有的文件描述符
cmd = F_GETFD 或 F_SETFD 获取或设置文件描述符
cmd = F_GETFL 或 F_SETFL 获取文件状态标志
*/

#include <fcntl.h>
#include "apue.h"


int
main(int argc, char const *argv[])
{
	int fd,flag;
	/* 模仿dup */
	fd = fcntl(STDOUT_FILENO,F_DUPFD,0);
	write(fd,"hello\n",6);
	/* 获取文件状态 */
	flag = fcntl(STDOUT_FILENO,F_GETFL,0);
	switch(flag & O_ACCMODE) {
	case O_RDONLY:
		puts("read only");
		break;
	case O_WRONLY:
		puts("write only");
		break;
	case O_RDWR:
		puts("read write");
		break;
	default:
		puts("unknown access mode");
	}
	puts("\n");
	/* 设置文件状态 */
	fd = open("open.c",O_RDWR);
	flag = fcntl(fd,F_GETFL,0);
	flag |= O_RDONLY | O_APPEND | O_NONBLOCK;
	fcntl(fd,F_SETFL,flag);
	flag = fcntl(fd,F_GETFL,0);
	switch(flag & O_ACCMODE) {
	case O_RDONLY:
		puts("read only");
	case O_WRONLY:
		puts("write only");
	case O_RDWR:
		puts("read write");
	case O_NONBLOCK:
		puts("no block");
	case O_APPEND:
		puts("append");
		break;
	default:
		puts("unknown access mode");
	}
	return 0;
}