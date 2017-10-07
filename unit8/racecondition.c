/*
竞争条件(race condition)是指多个进程都企图对共享数据进行处理,
而最后的结果又取决于进程运行的顺序时,则认为产生了竞争条件

*/

#include "apue.h"
#include <sys/wait.h>

static void charatatime(char *);

int
main(int argc, char const *argv[])
{
	pid_t pid;

	/*int status;*/

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {
		charatatime("child output\n");	
	}else {
		/*if (wait(&status)!= pid){
			err_sys("wait error");
		}*/
		charatatime("parent output\n");
	}

	return 0;
}

static void
charatatime(char *s)
{
	char *sptr;
	int c;
	setbuf(stdout,NULL);
	for (sptr = s;(c = *sptr++)!='\0';) {
		putc(c,stdout);
	}
}