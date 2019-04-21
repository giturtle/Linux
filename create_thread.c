/*************************************************************************
*> File Name: create.c
*> Author: giturtle
*> Describe: 线程创建的基本认识
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine) (void *), void *arg);
    thread: 输出型参数，获取新创建的线程id
    attr：  设置线程属性，通常置空
    start_routine： 线程入口函数
    arg：   通过线程入口函数传递给线程的参数
    返回值：0	    失败：errno > 0
*************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg){
    //pthread_t pthread_self(void);
    //	返回调用线程id
    pthread_t tid = pthread_self();
    while(1) {
	    printf("i am child~~~%s-%p\n", (char*)arg, tid);
    	sleep(1);
    }
    return NULL;
}
int main(int argc, char *argv[]){
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thr_start, (void*)"nihao");
    if (ret != 0) {
    	printf("thread create error\n");
    	return -1;
    }
    printf("main tid:%p\n", pthread_self());
    printf("child tid:%p\n", tid);
    while(1) {
    	printf("hello world~~~\n");
    	sleep(1);
    }
    return 0;
}
