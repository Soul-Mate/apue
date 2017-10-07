#include "apue.h"
#include <sys/wait.h>
#include <errno.h>

int 
my_system(char *cmdstring)
{
	pid_t pid;

	int status;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {
		if (execl("/bin/sh","sh","-c",cmdstring,(char *)NULL) < 0)
			err_sys("execl error");
	}

	while(waitpid(pid,&status,0) < 0) {
		if (errno != EINTR){
			status = -1;
			break;
		}
	}
	return status;
}


int
main(int argc, char const *argv[])
{
	
	if (my_system("date") < 0)
		err_sys("system error");
	return 0;
}