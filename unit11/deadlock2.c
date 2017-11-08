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

	lock_list * locks;
	locks = locks_alloc();
	if (locks == NULL) {
		printf("%s\n", "locks_alloc error");
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