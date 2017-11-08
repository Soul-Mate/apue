#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void printids(const char *s);

void *start_routine(void *arg);

int 
main(int argc, char const *argv[])
{
	pthread_t tid;
	int err;
	err = pthread_create(&tid,NULL,start_routine,NULL);
	if (err != 0) {
		perror("pthread_create error");
	}
	printids("main thread:");
	sleep(1);
	return 0;
}


void *
start_routine(void *arg)
{
	printids("new thread:");
	return (void *)NULL;
}


void 
printids(const char *s)
{
	pid_t 		pid;
	pthread_t 	tid;
	pid = getpid();
	tid = pthread_self();
	printf("%s pid: %u tid: %lu (0x%lx)\n", s, pid, tid, tid);
}
