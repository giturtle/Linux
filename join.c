/*************************************************************************
*> File Name: join.c
*> Author: giturtle
*> Describe: 线程等待--获取线程退出返回值，允许系统回收线程资源
    int pthread_join(pthread_t thread, void **retval);
	thread：    要等待的线程id
	retval：    输出型参数-用于获取退出线程的返回值
*************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg){
    //int pthread_detach(pthread_t thread);
    //	分离一个指定的线程---自己也可以
    //	线程的分离，对于一个线程来说，任意线程在任意位置调用都可以
    //pthread_detach(pthread_self());
    sleep(3);
    //char buf[10] = "nihao~~";
    return "nihao~~";
}
int main(int argc, char *argv[]){
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thr_start, NULL);
    if (ret != 0) {
	    printf("thread  create error\n");
	    return -1;
    }
    pthread_detach(tid);
    //pthread_cancel(tid);
    char *ptr = NULL;
    ret = pthread_join(tid, (void**)&ptr);
    if (ret == EINVAL) {
	    printf("this thread can not be wait!!\n");
    }
    printf("retval:%d--%d\n", ret, (int)ptr);
    return 0;
}
