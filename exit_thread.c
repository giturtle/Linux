/*************************************************************************
*> File Name: exit.c
*> Author: giturtle
*> Describe: 线程终止的几种方式
*************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg){
    while(1) {
	    printf("child thread-------\n");
	    sleep(1);
	//void pthread_exit(void *retval)
	//  退出调用线程，retval作为返回值
	//pthread_exit(NULL);
    }
    return NULL;
}
int main(int argc, char *argv[]){
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thr_start, NULL);
    if (ret != 0) {
    	printf("thread create error\n");
	    return -1;
    }
    //int pthread_cancel(pthread_t thread);
    //	取消一个指定线程tid == thread
    pthread_cancel(pthread_self());
    while(1) {
	    printf("main thread-------\n");
	    sleep(1);
    }
    return 0;
}
