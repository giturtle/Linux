/*************************************************************************
*> Describe: 线程等待与线程分离的认识
    int pthread_join(pthread_t thread, void **retval);
	thread:	    指定的线程ID
	retval：    用于获取线程的退出返回值
    返回值: 0	    失败： !0 - errno
    功能：等待线程退出，获取返回值，回收线程资源
    前提：这个被等待的线程必须处于joinable状态

    int pthread_detach(pthread_t thread);
	thread:	要被分离的线程ID
    功能：分离一个线程（设置线程的属性从joinable->detach属性）
	  线程退出后系统将自动回收资源；
	  被分离的线程无法被等待，若是非要pthread_join则会直接报错返回
    注意：
	线程被分离的前提是用户不关心 线程的退出返回值
*************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg){
    pthread_detach(pthread_self());
    pthread_exit("giturtle");
    while(1) {
	    printf("i am thread!!\n");
    	sleep(1);
    }
    return NULL;
}
int main(int argc, char *argv[])
{
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thr_start, NULL);
    if (ret != 0) {
	    printf("thread create error\n");
    	return -1;
    }

    sleep(1);
    char *retval = NULL;
    int err = pthread_join(tid, (void**)&retval);
    if (err == EINVAL) {
    	printf("thread can not be waited\n");
    }
    printf("retval:%s\n", retval);
    while(1) {
	    printf("i am main thread\n");
	    sleep(1);
    }
    return 0;
}
