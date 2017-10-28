#include <pthread.h>
#include <apue.h>
#include <string.h>

void * start_func(void * arg)
{
	char *s = (char *)arg;
	printf("%s", s);
	return (void *)strlen(s);
}

int
main(int argc, const char * argv[])
{
	pthread_t tid;
	void *res;
	int err;
	/* 创建一个线程 */
	err = pthread_create(&tid, NULL, start_func, "Hello World\n");
	if (err !=0 )
		err_sys("pthread err");
	printf("main start");
	/* 等待线程  */
	err = pthread_join(tid, &res);
	if (err !=0 )
		err_sys("pthread_join err");
	printf("thread returned %ld", (long)res);	

	return 0;
}
