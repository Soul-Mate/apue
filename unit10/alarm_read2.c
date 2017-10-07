#include "apue.h"
#include <signal.h>
#include <setjmp.h>

static jmp_buf alrm_buf;

static void sig_alrm(int signo);

int
main(int argc, char const *argv[])
{
	char buf[1024];

	int n;

	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal (SIGALRM) error");
	if (setjmp(alrm_buf) != 0)
		err_quit("read timeout");
	alarm(5);
	if ((n = read(STDIN_FILENO, buf, 1024)) < 0)
		err_sys("read error");
	write(STDOUT_FILENO, buf, n);
	alarm(0);
	return 0;
}

static void
sig_alrm(int signo)
{
	longjmp(alrm_buf, 1);
	/* nothing to do */
	return;
}
