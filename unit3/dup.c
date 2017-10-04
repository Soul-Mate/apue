/*
#include<unistd.h>
int dup(int fd);
int dup2(int fd, int fd2);
*/

#include "apue.h"
#include <fcntl.h>

int
main(int argc, char const *argv[])
{
	int fd;
	int newfd;
	puts("call dup1");

	newfd = dup(STDOUT_FILENO);
	if (newfd < 0) {
		err_sys("dup");
	}

	if (write(newfd,"hello\n",6) != 6) {
		err_sys("write");
	}

	puts("call dup2");

	fd = open("dup.c",O_RDONLY);


	if (fd < 0) {
		err_sys("open");
	}

	newfd = dup2(fd,10);

	if (newfd < 0) {
		err_sys("dup2");
	}

	printf("dup2 newfd: %d\n", newfd);

	return 0;
}