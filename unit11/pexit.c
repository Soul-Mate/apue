#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void * start_routine(void *arg);

int
main(int argc, char const *argv[])
{
	pthread_t tid;
	void *ret;
	pthread_create(&tid, NULL, start_routine, NULL);
	if (pthread_join(tid, &ret) != 0) {
		perror("pthread_join error");
	}
	printf("thread exit: %ld\n", (long)ret);
	return 0;
}

void *
start_routine(void *arg)
{
	printf("new thread: %lu\n",pthread_self());
	pthread_exit(NULL);
}