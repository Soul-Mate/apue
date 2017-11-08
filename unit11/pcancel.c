#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void * start_routine1(void *);

void * start_routine2(void *);

int
main(int argc, char const *argv[])
{
	int err;
	void *ret;
	pthread_t tid1, tid2;
	err = pthread_create(&tid1,NULL,start_routine1,NULL);
	if (err != 0)
		perror("pthread_create");
	else
		printf("pthread1: %lu\n", (long)tid1);
	err = pthread_create(&tid2,NULL,start_routine2,(void *)tid1);
	if (err != 0)
		perror("pthread_create");
	else
		printf("pthread2: %lu\n", (long)tid2);
	err = pthread_join(tid1, &ret);
	if (err != 0)
		perror("pthread_join");
	if ((int)ret == PTHREAD_CANCELED) {
		printf("thread: %lu cancel\n", (long)tid1 );
	}
	err = pthread_join(tid2, &ret);
	if (err != 0)
		perror("pthread_join");
	return 0;
}

void *
start_routine1(void *arg)
{
	sleep(3);
	printf("pthread 1: %lu\n", (long)pthread_self());
	return (void *)NULL;
}

void *
start_routine2(void *arg)
{
	int err;
	pthread_t tid = (long)arg;
	printf("pthread 2: %lu\n", (long)pthread_self());
	err = pthread_cancel(tid);
	if (err != 0) {
		printf("%s\n", "pthread_cancel error");
	}
	printf("pthread 2 cancel %lu thread\n",tid);
	return (void *)NULL;
}