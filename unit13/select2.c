#include "apue.h"
#include <fcntl.h>
#include <pthread.h>
#include <sys/select.h>
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

char buf[BUF_SIZE];

void *read_routine(void *);

void *write_routine(void *);

pthread_mutex_t lock;

int
main(int argc, char const *argv[])
{
	int            err,fds;
	void           *ravl;
	fd_set         readset,writeset;
	pthread_t      tid1,tid2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	err = pthread_mutex_init(&lock,NULL);
	if (err != 0)
		err_msg("pthread_mutex_init");
	err = pthread_create(&tid1,NULL,read_routine,(void*)argv[1]);
	if (err != 0)
		err_sys("pthread_create error");
	err = pthread_create(&tid2,NULL,write_routine,(void*)argv[2]);
	if (err != 0)
		err_sys("pthread_create error");

	err = pthread_join(tid1,NULL);
	if (err != 0)
		err_sys("pthread_join");
	err = pthread_join(tid2,&ravl);
	if (err != 0)
		err_sys("pthread_join");
	FD_ZERO(&readset);
	FD_ZERO(&writeset);
	FD_SET(3,&readset);
	FD_SET(4,&writeset);
	for(;;) {
		fds = select(5,&readset,&writeset,NULL,NULL);
		sleep(1);
		if (fds == 2) {
			pthread_mutex_lock(&lock);
			write((int)ravl,buf,BUF_SIZE);
			pthread_mutex_unlock(&lock);
			err = pthread_mutex_destroy(&lock);
			if (err != 0)
				err_sys("pthread_mutex_destroy");
			exit(0);
		}
	}
	return 0;
}

void *
read_routine(void *arg)
{
	int  fd;
	char *file;
	file = (char *)arg;
	fd = open(file,O_RDONLY);
	if (fd < 0) 
		err_sys("open");
	pthread_mutex_lock(&lock);
	read(fd,buf,BUF_SIZE);
	pthread_mutex_unlock(&lock);
	return (void *)NULL;
}

void *
write_routine(void *arg)
{
	int fd;
	char *file;
	file = (char *)arg;
	fd = open(file,O_WRONLY|O_CREAT|O_TRUNC|O_EXCL,0644);
	if (fd < 0)
		err_sys("write");
	return (void *)fd;
}