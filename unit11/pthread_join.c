#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

#ifndef THREAD_NUM
#define THREAD_NUM 10
#endif

void * start_routine(void *);

int
main(int argc, char const *argv[])
{
	void *ret;
	int i,err;
	pthread_t tids[THREAD_NUM];

	for (i = 0; i < THREAD_NUM; i++) {
		err = pthread_create(&tids[i],NULL,start_routine,(void *)(&i));
		if (err !=0 ) {
			printf("%s\n", "pthread_create error");
			exit(1);
		}
	}
	for (i = 0; i < THREAD_NUM; i++) {
		err = pthread_join(tids[i], &ret);
		printf("%d\n", (*(int *)ret));
		if (err != 0) {
			printf("%s\n", "pthread_join error");
			exit(1);
		}
	}
	return 0;
}

void * 
start_routine(void *arg)
{
	pthread_t tid = pthread_self();
	printf("%d thread: %lu (0x%lu)\n", *((int *)arg), tid, tid);
	return arg;
}

