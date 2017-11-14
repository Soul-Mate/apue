#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

void * start_routine1(void *);

void * start_routine2(void *);


typedef  struct lock_list {
	pthread_mutex_t lock1;
	pthread_mutex_t lock2;
}lock_list;

lock_list * locks_alloc();

int
main(int argc, char const *argv[])
{	

	int err;
	pthread_t tid1, tid2;
	lock_list * locks;
	locks = locks_alloc();
	if (locks == NULL) {
		printf("%s\n", "locks_alloc error");
		exit(1);
	}
	/* create thread 1 */
	err = pthread_create(&tid1, NULL, start_routine1, (void *)locks);
	if (err != 0) {
		printf("%s\n", "pthread_create error");
		exit(1);
	}
	/* create thread 2 */
	err = pthread_create(&tid2, NULL, start_routine2, (void *)locks);
	if (err != 0) {
		printf("%s\n", "pthread_create error");
		exit(1);
	}
	err = pthread_join(tid1,NULL);
	if (err != 0) {
		printf("%s\n", "pthread_detach error");
		exit(1);
	}
	err = pthread_join(tid2,NULL);
	if (err != 0) {
		printf("%s\n", "pthread_detach error");
		exit(1);
	}
	return 0;
}

lock_list *
locks_alloc()
{
	lock_list *locks;
	locks = (lock_list *)malloc(sizeof(lock_list));
	if (pthread_mutex_init(&locks->lock1, NULL) != 0) {
		return NULL;
	}
	if (pthread_mutex_init(&locks->lock2, NULL) != 0) {
		return NULL;
	}
	return locks;
}

void *
start_routine1(void *arg)
{
	int err;
	lock_list * locks = (lock_list *)arg;
	/* hold mutex1 lock mutex 2 */
	printf("%s\n", "thread 1 lock mutex1");
	err = pthread_mutex_lock(&locks->lock1);
	if (err != 0) {
		printf("%s\n", "pthread_mutex_lock error");
		exit(1);
	}
	printf("%s\n", "thread 1 lock mutex2");
	err = pthread_mutex_lock(&locks->lock2);
	if (err != 0) {
		printf("%s\n", "pthread_mutex_lock error");
		exit(1);
	}
	return (void *)NULL;
}

void *
start_routine2(void *arg)
{
	int err;
	lock_list * locks = (lock_list *)arg;
	/* hold mutex1 lock mutex 2 */
	printf("%s\n", "thread 2 lock mutex2");
	err = pthread_mutex_lock(&locks->lock2);
	if (err != 0) {
		printf("%s\n", "pthread_mutex_lock error");
		exit(1);
	}
	printf("%s\n", "thread 2 lock mutex1");
	err = pthread_mutex_lock(&locks->lock1);
	if (err != 0) {
		printf("%s\n", "pthread_mutex_lock error");
		exit(1);
	}
	return (void *)NULL;
}