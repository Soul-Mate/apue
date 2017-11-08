#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

void * start_routine1(void *arg);
void * start_routine2(void *arg);

pthread_mutex_t lock;

int i;

int
main(int argc, char const *argv[])
{
	pthread_t tid1, tid2;
	pthread_mutex_init(&lock,NULL);
	if (pthread_create(&tid1, NULL,start_routine1,NULL) != 0)
		perror("pthread_create");
	if (pthread_create(&tid2, NULL,start_routine2,NULL) != 0)
		perror("pthread_create");
	if (pthread_detach(tid1) !=0 )
		perror("pthread_detach");
	if (pthread_detach(tid2) !=0 )
		perror("pthread_detach");
	srand(time(NULL));
	while(1) {
		pthread_mutex_lock(&lock);
		sleep(rand() % 3);
		printf("main thread: i = %d\n", i);
		i++;
		pthread_mutex_unlock(&lock);
		sleep(rand() % 3);
	}
	pthread_mutex_destroy(&lock);
	return 0;
}

void *
start_routine1(void *arg)
{
	while(1) {
		pthread_mutex_lock(&lock);
		sleep(rand() % 3);
		printf("1 thread: i = %d\n", i);
		i++;
		pthread_mutex_unlock(&lock);
		sleep(rand() % 3);
	}
	pthread_mutex_destroy(&lock);
	return (void *)1;
}

void *
start_routine2(void *arg)
{
	while(1) {
		pthread_mutex_lock(&lock);
		sleep(rand() % 3);
		printf("2 thread: i = %d\n", i);
		i++;
		pthread_mutex_unlock(&lock);
		sleep(rand() % 3);
	}
	pthread_mutex_destroy(&lock);
	return (void *)2;
}