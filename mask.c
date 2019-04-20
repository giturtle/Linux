/*  信号的阻塞认识
 *  int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
 *      how：   
 *          SIG_BLOCK       阻塞set中的信号  mask = mask | set
 *          SIG_UNBLOCK     对set中的信号解除阻塞   mask = mask & (~set)
 *          SIG_SETMASK     将set中的信号设置为阻塞信号 mask = set
 *      阻塞set集合中的信号，将原来阻塞的信号保存到oldset中（不关心-置空）
 *  返回值：0       失败：-1
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigcb(int signo)
{
    printf("recv signo:%d\n", signo);
}
int main()
{
    signal(SIGINT, sigcb);
    signal(SIGRTMIN+5, sigcb);
    //先阻塞所有信号，当按下回车，恢复原先的阻塞信号
    sigset_t set, oldset;

    sigemptyset(&set);
    //int sigfillset(sigset_t *set);
    //将所有信号添加到set集合中
    //int sigaddset(sigset_t *set, int signum);
    //将指定信号signum添加到set中
    sigfillset(&set);
    sigprocmask(SIG_BLOCK, &set, &oldset);
    printf("press ENTER to unblock\n");
    getchar();

    sigset_t pending;
    //int sigpending(sigset_t *set);
    //获取当前进程的未决信号
    sigpending(&pending);
    int i;
    for (i = 1; i < 64; i++) {
        //int sigismember(const sigset_t *set, int signum);
        //判断信号signum是否在信号集合set中
        if (sigismember(&pending, i)) {
            printf("1 ");
        }else {
            printf("0 ");
        }
    }
    printf("\n");
    //sigprocmask(SIG_SETMASK, &oldset, NULL);
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    return 0;
}
