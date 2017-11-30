#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void * start_routine1(void *);

void * start_routine2(void *);

int
main(int argc, char const *argv[])
{
	int            detachstate;
	pthread_t 	   tid1,tid2;
	pthread_attr_t attr1,attr2;
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_attr_setdetachstate(&attr1,PTHREAD_CREATE_JOINABLE);
	pthread_attr_setdetachstate(&attr2,PTHREAD_CREATE_DETACHED);
	pthread_attr_getdetachstate(&attr1,&detachstate);
	if (detachstate == PTHREAD_CREATE_JOINABLE) {
		printf("%s\n", "pthread join state");
	}
	pthread_attr_getdetachstate(&attr2,&detachstate);
	if (detachstate == PTHREAD_CREATE_DETACHED) {
		printf("%s\n", "pthread detach state");
	}
	pthread_create(&tid1,&attr1,start_routine1,NULL);
	pthread_create(&tid2,&attr2,start_routine2,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}


void *
start_routine1(void *arg)
{
	printf("%s\n", "state joinable");
	printf("thread (0x%lu)\n", pthread_self());
	return (void *)NULL;
}

void *
start_routine2(void *arg)
{
	printf("%s\n", "state detached");
	printf("thread (0x%lu)\n", pthread_self());
	return (void *)NULL;
}