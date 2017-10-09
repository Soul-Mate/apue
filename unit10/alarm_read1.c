#include "apue.h"

static void sig_alrm(int signo);

int
main(int argc, char const *argv[])
{
	int read_num;
	char buf[4096];
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal alarm");
	alarm(5);
	if ((read_num = read(STDIN_FILENO, buf,4096)) < 0)
		err_sys("read error");
	alarm(0);
	write(STDOUT_FILENO,buf,read_num);
	return 0;
}

static void
sig_alrm(int signo)
{
	/* nothing to do */
	return;
}
