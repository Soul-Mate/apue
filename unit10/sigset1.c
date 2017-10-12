#include <signal.h>
#include "apue.h"

static void sig_int(int signo);

int
main(int argc, char const *argv[])
{

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");
	sigset_t newmask, oldmask, pendmask;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("sigprocmask error");
	
	sleep(5);

	if (sigpending(&pendmask) < 0)
		err_sys("sigpending error");
	if (sigismember(&pendmask,SIGINT))
		/* SIGINT未决 */
		printf("\nSIGQUIT pending\n");
	
	/* 恢复sigsetmask */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
	printf("SIGINT unblocked\n");
	sleep(5);
	exit(0);
}

static void 
sig_int(int signo)
{
	printf("caught SIGINT\n");
	/* SIGQUIT信号执行默认动作 */
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		err_sys("signal error\n");
}