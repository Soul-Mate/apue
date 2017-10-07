#include "apue.h"
#include <signal.h>
#include <sys/wait.h>

static void sig_usr(int signo);

int 
main(int argc, char const *argv[])
{
	pid_t pid;

	
	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0){
		if (signal(SIGUSR1, sig_usr) == SIG_ERR)
			err_sys("signal error");
		/* child kill self */
		if (kill(pid,SIGUSR1) < 0)
			err_sys("kill error");
	}
	/* parent no wait child process */
	return 0;
}

static void
sig_usr(int signo)
{
	if (signo == SIGUSR1){
		puts("");
		puts("received SIGUSR1\n");
		printf("PID = %d\n",getpid());
	}
}
