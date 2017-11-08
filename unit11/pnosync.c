#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

int i;

void * start_routine1(void *);

void * start_routine2(void *);

int
main(int argc, char const *argv[])
{
	pthread_t tid1, tid2;
	void *ret;
	if (pthread_create(&tid1, NULL,start_routine1,NULL) != 0)
		perror("pthread_create");
	if (pthread_create(&tid2, NULL,start_routine2,NULL) != 0)
		perror("pthread_create");
	if (pthread_join(tid1, &ret) !=0 )
		perror("pthread_join");
	printf("thread 1 exit code %ld\n",(long)ret);
	if (pthread_join(tid2, &ret) !=0 )
		perror("pthread_join");
	printf("thread 2 exit code %ld\n",(long)ret);
	return 0;
}

void *
start_routine1(void *arg)
{
	printf("thread 1 start\n");
	i = 2; 
	printf("thread 1 i: %d\n", i);
	sleep(1);
	i++;
	printf("thread 1 i: %d\n", i);
	return (void *)1;
}

void *
start_routine2(void *arg)
{
	printf("thread 2 start\n");
	printf("thread 2 i: %d\n", i);
	i = 0;
	sleep(1);
	return (void *)2;
}