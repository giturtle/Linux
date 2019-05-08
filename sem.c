/*===============================================================
*   描    述：实现线程安全的环形队列 （线性表实现的环形队列）
*	使用信号量实现队列操作的同步与互斥
================================================================*/
#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>

class RingQueue{
    public:
	RingQueue(int cap = 10):_queue(10), _capacity(cap),
	    _write_step(0), _read_step(0){
	    //int sem_init(sem_t *sem, int pshared, unsigned int value);
	    //	sem:	信号量变量
	    //	pshared：选项标志-决定信号量用于进程间还是线程间同步互斥
	    //	    0	线程间
	    //	    !0	进程间
	    //	value：	信号量初始计数
	    sem_init(&_sem_data, 0, 0);
	    sem_init(&_sem_idle, 0, cap);
	    sem_init(&_sem_lock, 0, 1);
	}
	~RingQueue(){
	    //int sem_destroy(sem_t *sem);
	    //	sem:	信号量变量
	    sem_destroy(&_sem_data);
	    sem_destroy(&_sem_idle);
	    sem_destroy(&_sem_lock);
	}
	bool  QueuePush(int data){
	    ProductorWait();
	    QueueLock();
	    _queue[_write_step] = data;
	    _write_step = (_write_step + 1) % _capacity;
	    QueueUnLock();
	    ConsumerWakeUp();
	    return true;
	}
	bool  QueuePop(int *data){
	    ConsumerWait();
	    QueueLock();
	    *data = _queue[_read_step];
	    _read_step = (_read_step + 1) % _capacity;
	    QueueUnLock();
	    ProductorWakeUp();
	    return true;
	}
    private:
	void QueueLock(){
	    //通过计数判断是否有资源可操作 （计数-1 + 等待）
	    //int sem_wait(sem_t *sem);
	    //	若计数<=0;则阻塞
	    //int sem_trywait(sem_t *sem);
	    //	若计数<=0;则报错返回
	    //int sem_timedwait(sem_t*sem, struct timespec*abs_timeout);
	    //	若计数<=0;则限时阻塞,超时则报错返回
	    sem_wait(&_sem_lock);
	}
	void QueueUnLock(){
	    //计数+1 ，并唤醒等待
	    //int sem_post(sem_t *sem);
	    sem_post(&_sem_lock);
	}
	void ProductorWait(){
	    sem_wait(&_sem_idle);
	}
	void ProductorWakeUp(){
	    sem_post(&_sem_idle);
	}
	void ConsumerWait(){
	    sem_wait(&_sem_data);
	}
	void ConsumerWakeUp(){
	    sem_post(&_sem_data);
	}
    private:
	std::vector<int> _queue;
	int  _capacity;
	int  _write_step;
	int  _read_step;
	sem_t _sem_data;//数据资源计数
	sem_t _sem_idle;//空闲空间计数
	sem_t _sem_lock;//实现互斥
};
void *thr_consumer(void *arg){
    RingQueue *q = (RingQueue*)arg;
    while(1) {
	int data;
	q->QueuePop(&data);
	std::cout<<"consumer thread get data:"<<data<<std::endl;
    }
    return NULL;
}
void *thr_productor(void *arg){
    RingQueue *q = (RingQueue*)arg;
    int i = 0;
    while(1) {
	q->QueuePush(i);
	std::cout<<"productor thread put data:"<<i<<std::endl;
	i++;
    }
    return NULL;
}
int main (int argc, char *argv[]){
    pthread_t ctid[4], ptid[4];
    int ret, i;
    RingQueue q;

    for (i = 0; i < 4; i++) {
	ret = pthread_create(&ctid[i], NULL, thr_consumer, (void*)&q);
	if (ret != 0) {
	    std::cout<<"thread create error\n";
	    return -1;
	}
    }
    for (i = 0; i < 4; i++) {
	ret = pthread_create(&ptid[i], NULL, thr_productor, (void*)&q);
	if (ret != 0) {
	    std::cout<<"thread create error\n";
	    return -1;
	}
    }
    for (i = 0; i < 4; i++) {
	pthread_join(ctid[i], NULL);
    }
    for (i = 0; i < 4; i++) {
	pthread_join(ptid[i], NULL);
    }
    return 0;
}
