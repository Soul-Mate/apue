#include "apue.h"
#include <signal.h>

static sig_atomic_t sigflag;

sigset_t sigmask, osigmask, zeromask;

static void sig_usr();

void TELL_WAIT();

void TELL_PARENT(pid_t pid);

void WAIT_PARENT();

void TELL_CHILD(pid_t pid);

void WAIT_CHILD();


int
main(int argc, const char * argv[])
{

	pid_t pid;
	int i;
	TELL_WAIT();
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	}else if(pid == 0) {
		/* child */
		for (i=0;i<5;i++) {
			printf("i = %d\n",i);
			sleep(1);
		}
		TELL_PARENT(pid);
		WAIT_PARENT();
		printf("child process done\n");
	}else {
		WAIT_CHILD();
		TELL_CHILD(pid);
		printf("parent process done\n");
	}
	return 0;
}

static void
sig_usr(int signo)
{
	if (signo == SIGUSR1 || signo == SIGUSR2)
		sigflag = 1;
}

void TELL_WAIT()
{
    struct sigaction act1,act2,oact1,oact2;
    act1.sa_flags = 0;
    act1.sa_handler = sig_usr;
    /* 捕捉SIGUSR1信号 */
	if (sigaction(SIGUSR1,&act1,&oact1) < 0)
		err_sys("sigprocmask (SIGUSR1)");
    act2.sa_flags = 0;
    act2.sa_handler = sig_usr;
    /* 捕捉SIGUSR2 */
	if (sigaction(SIGUSR2,&act2,&oact2) < 0)
		err_sys("sigprocmask (SIGUSR2)");
    sigemptyset(&sigmask);
    sigaddset(&sigmask,SIGUSR1);
    sigaddset(&sigmask,SIGUSR2);
	/* 阻塞SIGUSR1 SIGUSR2 */
    if (sigprocmask(SIG_BLOCK,&sigmask,&osigmask) < 0)
    	err_sys("sigprocmask (SIG_BLOCK)");
}

void TELL_PARENT(pid_t pid)
{
	/* 向子进程发送SIGUSR2信号 */
	kill(pid, SIGUSR2);
}


void TELL_CHILD(pid_t pid)
{
	/* 向子进程发送SIGUSR1信号 */
	kill(pid, SIGUSR1);
}

void WAIT_PARENT()
{
	/* 轮询等待期间产生的其他信号 */
	while(sigflag == 0){
		sigsuspend(&zeromask);
	}
	sigflag = 0;
	/* 还原进程阻塞期间接收到的信号 */
	if (sigprocmask(SIG_SETMASK,&osigmask,NULL) < 0)
		err_sys("sigprocmask error");
}

void WAIT_CHILD()
{
	while(sigflag == 0) {
		sigsuspend(&zeromask);
	}
	sigflag = 0;
	if (sigprocmask(SIG_SETMASK,&osigmask,NULL) < 0)
		err_sys("sigprocmask error");
}