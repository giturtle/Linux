/*  信号的捕捉初识
 *      typedef void (*sighandler_t)(int);
 *
 *      sighandler_t signal(int signum, sighandler_t handler);
 *      signum: 信号编号
 *      handler：   函数指针
 *              SIG_DFL     默认处理方式
 *              SIG_IGN     忽略处理方式
 *      使用handler函数替换signum信号的处理方式
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

struct sigaction act, oldact;

void sigcb(int signo){
    printf("recv signo:%d\n", signo);
    sigaction(signo, &oldact, NULL);
}
int main(){
    //int sigaction(int signum,struct sigaction *act,struct sigaction *oldact);
    //使用act动作替换signum原有的处理动作，并且将原有处理动作拷贝到oldact中
    act.sa_handler = sigcb;
    act.sa_flags = 0;
    //int sigemptyset(sigset_t *set);
    //清空信号集合set
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, &oldact);

    //signal(SIGINT, sigcb);
    //signal(SIGQUIT, sigcb);
    //signal(SIGKILL, sigcb);
    while(1) {
        printf("-----------\n");
        sleep(1);
    }
    return 0;
}
