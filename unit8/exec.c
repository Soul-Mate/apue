#include "apue.h"
#include <sys/wait.h>


int
main(int argc, char const *argv[])
{
	pid_t pid;
	
	const char *envp[] = {"USER=xyc","PATH=/usr/bin",NULL};

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0) { /* child process */
		if (execle("/mnt/d/Code/c/apue/unit8/echo","echo","argv1","argv2",(char *)NULL,envp) < 0) 
			err_sys("execle error");
	}
	sleep(3);
	if (waitpid(pid,NULL,0) < 0)
		err_sys("wait error");

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {
		if (execlp("echo","echo","only argv1",(char *)NULL) < 0)
			err_sys("execlp error");
	}
	exit(0);
	return 0;
}