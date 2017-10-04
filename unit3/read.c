/*
size_t read(int fd,char *buf,unsigned bytes);
调用成功返回读取到的字节数(某些情况下读取到的字节数会低于预期值) 调用失败返回-1
*/

#include "apue.h"
#include <fcntl.h>
int
main(int argc, char const *argv[])
{
	int fd,buf_size = 4096;

	size_t read_num;
	
	char *buf;
	
	if (argc !=2 )
		err_exit(1,"path");
	
	fd = open(argv[1],O_RDONLY);
	
	if (fd < 0)
		err_sys("open");
	buf = (char *)malloc(buf_size);
	while((read_num = read(fd,buf,buf_size)) != 0) {
		if (write(STDOUT_FILENO,buf,read_num) != read_num)
			err_sys("write");
	}
	if (read_num < 0)
		err_sys("read");
	
	if (close(fd) < 0)
		err_sys("close");
	
	free(buf);
	return 0;
}
