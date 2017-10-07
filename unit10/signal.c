#include "apue.h"
#include <signal.h>

static void sig_usr(int signo);

int
main(int argc, char const *argv[])
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("signal error");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("signal error");
	if (signal(SIGFPE, sig_usr) == SIG_ERR)
		err_sys("signal error");
	if (signal(SIGINT, sig_usr) == SIG_ERR)
		err_sys("signal error");
	for(;;)
		pause();

	return 0;
}

static void
sig_usr(int signo)
{
	if (signo == SIGUSR1)
		puts("recevied SIGUSR1");
	else if (signo == SIGUSR2)
		puts("recevied SIGUSR2");
	else if (signo == SIGFPE) {
		puts("recevied SIGFPE");
		exit(0);
	}else if(signo == SIGINT){
		puts("recevied SIGINT");
		int i;
		for (i=0;i<5;i++){
			printf("%d\n",i+1);
			sleep(1);
		}
		exit(0);
	}
	else
		err_dump("recevied signal %d\n", signo);
	return;
}
