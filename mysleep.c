
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void sigcb2(int signo){
    sleep(10);
}
void sigcb(int signo){
}
int mysleep(int nsec){
    signal(SIGALRM, sigcb);
    sigset_t set, old;
    sigemptyset(&set);
    sigprocmask(SIG_BLOCK, &set, &old);
    alarm(nsec);

    sigprocmask(SIG_UNBLOCK, &set, &old);
    //int sigsuspend(const sigset_t *mask);
    //临时使用mask替换阻塞集合，陷入休眠,被唤醒之后阻塞集合还原
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGALRM);//除了SIGALRM所有信号
    //这时候除了SIGALRM，所有信号都被阻塞，陷入休眠,只有SIGALRM能够唤醒这个休眠
    sigsuspend(&mask);
    sigprocmask(SIG_SETMASK, &old, NULL);
    signal(SIGALRM, SIG_DFL);
}

int main(){
    signal(SIGQUIT, sigcb2);
    mysleep(3);
    printf("------\n");
    return 0;
}
