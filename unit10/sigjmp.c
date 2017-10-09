#include "apue.h"
#include <signal.h>
#include <setjmp.h>

static void sig_int(int),sig_usr(int);

static sigjmp_buf jmpbuf;

static volatile sig_atomic_t canjump;


int
main(int argc, char const *argv[])
{
	struct sigaction act, oact;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = sig_int;
	if (sigaction(SIGINT, &act, &oact) < 0)
		err_sys("sigaction error");
	for(;;)
		pause();
	return 0;
}

static void
sig_int(int signo)
{
	puts("signal caught SIGINT");
}

static void
sig_usr(int signo)
{

}