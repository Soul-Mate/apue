#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

void * start_routine(void *);



int
main(int argc, char const *argv[])
{
	pthread_t tid;
	void *ret;
	pthread_create(&tid, NULL, start_routine, NULL);
	pthread_join(tid, &ret);
	return 0;
}

void *
start_routine(void *arg)
{
	pthread_mutex_t lock;
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	sleep(1);
	printf("%s\n", "deadlock");
	pthread_mutex_lock(&lock); /* deadlock */
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
	return (void *)NULL;
}