#include "apue.h"
#include <signal.h>

unsigned int sleep1(unsigned int seconds);

static void sig_alrm(int signo);

int
main(int argc, char const *argv[])
{
	unsigned int uslept;
	printf("sleep 3 second\n");
	uslept = sleep1(3);
	printf("%d\n", uslept);
	return 0;
}


unsigned int
sleep1(unsigned int seconds)
{
	if (signal(SIGALRM, sig_alrm) == SIG_ERR){
		return seconds;
	}
	alarm(seconds);
	pause();
	/* 返回剩余的秒数 */
	return (alarm(0));
}

static void
sig_alrm(int signo)
{
	/* nothing to do*/

	return;
}