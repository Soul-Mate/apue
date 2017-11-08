#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

typedef struct foo{
	int f_count;
	int f_id;
	pthread_mutex_t f_lock;
}foo;

foo * foo_alloc(int id);

void foo_hold(foo *fp);

void foo_free(foo *fp);

void * start_routine(void *);

foo *
foo_alloc(int id)
{
	foo *fp;
	if ((fp = (foo *)malloc(sizeof(foo))) != NULL) {
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
			free(fp);
			return NULL;
		}	
	}
	return fp;
}

void
foo_hold(foo *fp)
{
	if(fp == NULL) {
		printf("fp error");
		exit(1);
	}
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void 
foo_free(foo *fp)
{
	if(fp == NULL) {
		printf("fp error");
		exit(1);
	}
	pthread_mutex_lock(&fp->f_lock);
	if (--fp->f_count == 0) {
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}else {
		pthread_mutex_unlock(&fp->f_lock);
	}
}

int
main(int argc, char const *argv[])
{
	int err;
	pthread_t tid;
	foo *fp;
	fp = foo_alloc(1);
	srand(time(NULL));
	err = pthread_create(&tid, NULL, start_routine, (void *)fp);
	if (err != 0) {
		printf("pthread_create error\n");
		exit(1);
	}
	err = pthread_detach(tid);
	if (err != 0) {
		printf("pthread_detach error\n");
		exit(1);	
	}
	while(1) {
		foo_hold(fp);
		printf("main thread: f_count = %d\n", fp->f_count);
		sleep(rand() % 3);
	}
	return 0;
}

void *
start_routine(void *arg)
{
	foo *fp = (foo *)arg;
	while(1) {
		foo_hold(fp);
		printf("child thread: f_count = %d\n", fp->f_count);
		sleep(rand() % 3);
	}
	return (void *)(NULL);
}