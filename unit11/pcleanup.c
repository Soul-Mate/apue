#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void cleanup(void *);

void * start_routine1(void *);

void * start_routine2(void *);

int
main(int argc, char const *argv[])
{
	pthread_t tid1, tid2;
	void *ret;
	if (pthread_create(&tid1, NULL,start_routine1,(void *)1) != 0)
		perror("pthread_create");
	if (pthread_create(&tid2, NULL,start_routine2,(void *)1) != 0)
		perror("pthread_create");
	if (pthread_join(tid1, &ret) !=0 )
		perror("pthread_join");
	printf("thread 1 exit code %ld\n",(long)ret);
	if (pthread_join(tid2, &ret) !=0 )
		perror("pthread_join");
	printf("thread 2 exit code %ld\n",(long)ret);
	return 0;
}

void cleanup(void *arg)
{
	printf("cleanup: %s\n", (char *)arg);
}

void *
start_routine1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 complete\n");
	if (arg)
		pthread_exit((void *)1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)1);
}

void *
start_routine2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 complete\n");
	if (arg)
		return (void *)2;
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return (void *)2;
}