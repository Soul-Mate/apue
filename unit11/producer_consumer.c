/*
 * =====================================================================================
 *
 *       Filename:  producer_consumer.c
 *
 *    Description: 生产者消费者线程模型
 *
 *        Version:  1.0
 *        Created:  11/11/2017 05:07:29 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
/*************************************************************************
    > File Name: producer_consumer.c
  > Author: 
  > Mail: 
  > Created Time: Sat 11 Nov 2017 05:07:28 AM UTC
 ************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

struct msg {
    int el;
    struct msg *next;
};

struct msg *pmsg = NULL;

struct msg *head = NULL;

void * producer(void *);

void * consumer(void *);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int
main(void)
{
    void *rval;
    int err;
    /*创建生产者线程*/
    pthread_t producer_tid, consumer_tid;;
    err = pthread_create(&producer_tid, NULL, producer, NULL);
    if (err != 0) {
        perror("pthread_create error");
    }
    /*创建消费者线程*/
    err = pthread_create(&consumer_tid, NULL, consumer, NULL);
    /*阻塞线程*/
    err = pthread_join(producer_tid, &rval);
    if (err != 0) {
        perror("pthread_join producer error");
    }
    err = pthread_join(consumer_tid, &rval);
    if (err != 0) {
        perror("pthread_join consumer error");
    }
    srand(time(NULL));
    return 0;
}

void *
producer(void *arg)
{
    int err;
    for(;;) {
        pmsg = (struct msg *)malloc(sizeof(struct msg));
        pmsg->el = rand() % 400 + 1;
        printf("producer: %d\n", pmsg->el);
        err = pthread_mutex_lock(&lock);
        if (err != 0) {
            perror("producer thread pthread_mutex_lock error");
        }
        pmsg->next = head;
        head = pmsg;
        err = pthread_mutex_unlock(&lock);
        if (err != 0 ) {
            perror("producer thread pthread_mutex_unlock error");
        }
        pthread_cond_signal(&cond);
        sleep(rand() % 5);
    }
    return (void *)NULL;
}

void *
consumer(void *arg)
{
    int err;
    for(;;) {
        err = pthread_mutex_lock(&lock);
        if (err != 0) {
            perror("consumer thread pthread_mutex_lock error");
        }
        while(head == NULL) {
            pthread_cond_wait(&cond,&lock);
        }
        pmsg = head;
        head = pmsg->next;
        err = pthread_mutex_unlock(&lock);
        if (err != 0) {
            perror("consumer thread pthread_mutex_unlock error");
        }
        printf("consumer: %d\n",pmsg->el);
        free(pmsg);
        sleep(rand() % 5);
    }
    
    return (void *)NULL;
}
