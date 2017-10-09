#include "apue.h"
#include <setjmp.h>

static void sig_alrm(int signo);

static void sig_int(int signo);

unsigned int sleep2(unsigned int seconds);

static jmp_buf alrm_buf;

int
main(int argc, char const *argv[])
{
	unsigned int uslept;
	/* 键入中断 产生SIGINT信号 */
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");
	printf("sleep 10 second\n");
	uslept = sleep2(10);
	printf("sleep residue seconds: %d\n", uslept);
	return 0;
}

unsigned int 
sleep2(unsigned int seconds)
{
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return seconds;

	if (setjmp(alrm_buf) == 0) {
		alarm(seconds);
		pause();
	}
	return alarm(0);
}


static void
sig_alrm(int signo)
{
	longjmp(alrm_buf,1);
}



static void
sig_int(int signo)
{
	int 	i;
	volatile int j;
	printf("\nsignal SIGINT start\n");
	for (i=0;i<200000;i++) {
		j += i * i;
	}
	printf("signal SIGINT finished\n");
}