/*
size_t write(int fd,const void *buff,size_t bytes);
调用成功返回写入的字节,失败返回-1
*/

#include "apue.h"
#include <fcntl.h>
int
main(int argc, char const *argv[])
{
	int fd;

	size_t read_num;

	char *buf;

	if (argc != 2)
		err_exit(1,"path");

	fd = open(argv[1],O_RDONLY);
	
	if (fd < 0)
		err_sys("open");

	buf = (char *)malloc(4096);

	while((read_num = read(fd,buf,4096)) != 0)
		if (write(STDOUT_FILENO,buf,read_num) != read_num)
			err_sys("write");
	
	if (read_num < 0)
		err_sys("read");

	if (close(fd) < 0)
		err_sys("close");

	free(buf);

	return 0;
}