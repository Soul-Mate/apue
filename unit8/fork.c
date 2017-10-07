/*
#include <unistd.h>
pid_t fork(void);
返回值：子进程返回0，父进程返回子进程ID; 若出错,返回-1
*/
#include "apue.h"

int globalval = 6;

char buf[] = "a write to stdout\n";

int
main(int argc, char const *argv[])
{
	pid_t pid;
	
	int val;

	val = 88;
	
	if (write(STDOUT_FILENO,buf,strlen(buf)) != strlen(buf))
		err_sys("write error");
	
	puts("before fork");
	
	if ((pid = fork()) == -1) {
		err_sys("fork error");
	}else if(pid == 0) {
		globalval++;
		val++;
	}else{
		sleep(2);
	}
	printf("pid = %ld,globalval = %d, val = %d\n",(long)getpid(),globalval,val);
	return 0;
}