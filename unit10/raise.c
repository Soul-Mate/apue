#include "apue.h"
#include <sys/wait.h>

static void sig_usr(int signo);

int
main(int argc, char const *argv[])
{
	pid_t pid;

	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("signal error");
	
	if ((pid = fork()) <0 )
		err_sys("fork error");
	else if (pid == 0){
		/* child raise signo */
		raise(SIGUSR1);
	}

	return 0;
}


static void
sig_usr(int signo)
{
	if (signo == SIGUSR1) {
		printf("received SIGUSR1 signal\n");
	}else if(signo == SIGUSR2) {
		printf("received SIGUSR2 signal\n");
	}
	return;
}
