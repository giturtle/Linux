/*************************************************************************
*> Describe: 线程的创建
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine) (void *), void *arg);
	thread:	输出型参数，用于获取新创建的线程id
	attr：	线程属性，通常置NULL
	start_routine：	线程入口函数
	arg：	传递给线程的参数
    返回值：0	    失败：非0----errno 
*************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg){
    //void pthread_exit(void *retval);
    //	retval:	线程的退出返回值
    //	退出调用线程
    //sleep(5);
    //pthread_exit(NULL);
    while(1) {
		  printf("i am child thread-------%s\n", (char*)arg);
		  sleep(1);
    }
    return NULL;
}
int main(int argc, char *argv[]){
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thr_start, (void*)"yundonghui~");
    if (ret != 0) {
		  printf("thread create error\n");
		  return -1;
    }
    sleep(5);
    //int pthread_cancel(pthread_t thread);
    //	退出指定的线程
    //	thread：    线程id
    pthread_cancel(tid);
    //printf("i am main thread --------%p\n", tid);
    while(1) {
		  printf("i am main thread --------%p\n", tid);
		  sleep(1);
    }
    return 0;
}
