/*
有两个进程A和B,A和B进程都对同一文件进行追加写操作,每个进程都已打开了该文件但未使用O_APPEND标志
假设进程A调用了lseek 将文件偏移量设置为1500,并写入了数据后文件偏移量为1600
这时内核切换进程B,并从当前偏移量写入数据(1500),这样实际上覆盖了B进程写入的数据
*/

/*
原子操作指由多步组成的一草操作,如果该操作原子性的执行,那么要么执行完全部操作,要么一个也不执行.
*/

#include "apue.h"
#include <fcntl.h>
#include<sys/wait.h>

int
main(int argc, char const *argv[])
{

	int fd;
	
	int pid;

	if (argc !=2 )
		err_exit(0,"path");


	fd = open(argv[1],O_RDWR|O_CREAT|O_EXCL|O_TRUNC,0644);

	if (fd < 0)
		err_sys("open");

	pid = fork();

	if (pid > 0) {
		if (lseek(fd,1500,SEEK_CUR) < 0)
			err_sys("parent process lseek");
		
		printf("parent  process write\n");

		if (write(fd,"abcde",strlen("abcde")) != strlen("abcde"))
			err_sys("parent process write");
		
		wait(NULL);
	}else if (pid == 0) {
		if (lseek(fd,1500,SEEK_CUR) < 0)
			err_sys("child process lseek");
		
		printf("child process write\n");
		if (write(fd,"ABCDE",strlen("ABCDE")) != strlen("ABCDE"))
			err_sys("child process write");
	}else
		err_sys("fork");

	if (close(fd) < 0)
		err_sys("close");

	return 0;
}