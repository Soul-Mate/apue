/*
#include <sys/wait.h>
pid_t wait(int *statloc);
pid_t waitpid(pid_t pid, int *statloc, int options);
成功返回进程id,出错返回0或-1

wait使调用者阻塞,waipid有选项可使调用者不阻塞
statloc是一个整形指针,如果statloc不是一个空指针,则进程结束状态保存在其中
*/

#include <sys/wait.h>
#include "apue.h"

int
main(int argc, char const *argv[])
{
	
	pid_t pid;

	int status;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)	/* 子进程 */
		exit(7);
	if (wait(&status) != pid) /* 打印进程结束装填 */
		err_sys("wait error");
	pr_exit(status);

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0)	/*子进程 */
		abort();		/* 生成信号SIGABRT */
	if (wait(&status) != pid)
		err_sys("wait error");
	pr_exit(status);

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)	/* 子进程 */
		status /=0;		/* 生成信号SIGFPE */
	if (wait(&status) != pid) /* 打印进程结束状态 */
		err_sys("wait error");
	pr_exit(status);
	return 0;
}