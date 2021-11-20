#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "threadPool.h"

void taskFunc(void* arg) {
	int num = *(int *)arg;
	printf("thread %ld is working , number = %d\n", pthread_self(), num);
	sleep(1);
}

void taskFunc1(void* arg) {
	int num = *(int *)arg;
	printf("taskFunc1 thread %ld is working, number = %d\n", pthread_self(), num);
	sleep(1);
}

int main()
{
    // 创建线程池
	ThreadPool* pool = threadPoolCreate(3, 10, 100);
	for (int i = 0; i < 100; ++i) {
		int* num = (int *)malloc(sizeof(int));
		*num = i + 100;
		threadPoolAdd(pool, taskFunc, num);
	}
	for (int i = 0; i < 100; ++i) {
		int* num = (int *)malloc(sizeof(int));
		*num = i++;
		threadPoolAdd(pool, taskFunc1, num);
	}

	sleep(10);

	threadPoolDestroy(pool);
    return 0;
}