/*
lseek会导致文件空洞问题
*/

#include "apue.h"

int
main(int argc, char const *argv[])
{
	int fd;

	char *buf1,*buf2;

	/* 创建一个具有文件空洞的文件 */
	if (argc !=2 )
		err_exit(1,"path");

	fd = creat(argv[1],0644);
	
	buf1 = "abcde";

	if (write(fd,buf1,strlen(buf1)) != strlen(buf1))
		err_sys("write");

	if (fd < 0)
		err_sys("open");

	lseek(fd,4096,SEEK_CUR);

	buf2 = "ABCDE";

	if (write(fd,buf2,strlen(buf2)) != strlen(buf2))
		err_sys("write");
	
	if (close(fd) < 0)
		err_sys("close");
	return 0;
}