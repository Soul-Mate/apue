#include "apue.h"
#include <signal.h>
#include <setjmp.h>

static void sig_int(int),sig_usr(int);

static sigjmp_buf jmpbuf;

static volatile sig_atomic_t canjump;


int
main(int argc, char const *argv[])
{
	struct sigaction act, oact, saveusr1, osaveusr1;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = sig_int;
	if (sigaction(SIGINT, &act, &oact) < 0)
		err_sys("sigaction SIGINT error");
	saveusr1.sa_flags = 0;
	saveusr1.sa_handler = sig_usr;
	sigemptyset(&saveusr1.sa_mask);
	if (sigaction(SIGUSR1, &saveusr1, &osaveusr1) < 0)
		err_sys("sigaction SIGUSR error");
	if(sigsetjmp(jmpbuf, 1)){
		puts("sigsetjmb ending main");
		exit(0);
	}
	canjump = 1;
	for(;;)
		pause();
	return 0;
}

static void
sig_int(int signo)
{
	puts("");
	puts("signal caught SIGINT");
}

static void
sig_usr(int signo)
{
	if (canjump == 0)
		return;
	if (signo == SIGUSR1){
		printf("signal caught SIGUSR1\n");
		siglongjmp(jmpbuf,1);
		canjump = 0;
	}
}