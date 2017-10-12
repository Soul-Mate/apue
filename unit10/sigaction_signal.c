#include "apue.h"
#include <signal.h>
/*
 * 
 * int sigaction(int signo, struct sigaction *, struct sigaction *);
 * sigaction检查或修改与指定信号关联的处理动作，可以替代signal函数
 * 返回值：成功返回0,失败返回-1
 * struct sigaction {
 *	void (*sa_handler)();  信号捕捉函数 也可以是 SIG_DEF SIG_ERR
 *	sigset_t  sa_mask;   信号屏蔽字
 *	int sa_flags;    信号选项  SA_RESTART
 * }
 */
Sigfunc * my_signal(int signo,Sigfunc *func);

static void sig_int(int signo);

static void sig_alrm(int signo);

int
main(int argc, char const *argv[])
{
	if (my_signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("my_signal error");
	if (my_signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("my_signal error");
	alarm(5);
	pause();
	for(;;)
		pause();
	return 0;
}

static void
sig_alrm(int signo)
{
	puts("signal caught SIGALRM");
}

static void
sig_int(int signo)
{
	int i = 0;
	if (signo == SIGINT){
		puts("");
		puts("signal caught SIGINT");
		for (;i< 10;i++){
			printf ("i = %d\n",i+1);
			sleep(1);
		}
		/* SIGINT default */
		if (my_signal(SIGINT, SIG_DFL) == SIG_ERR)
			err_sys("my_signal error");
	}
}

Sigfunc * 
my_signal(int signo, Sigfunc *func)
{
	struct sigaction act, oact;
	act.sa_flags = 0;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	if (signo == SIGALRM){
		#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
		#endif
	}
	if (sigaction(signo,&act,&oact) < 0)
		return SIG_ERR;
	return oact.sa_handler;

}
