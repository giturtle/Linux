/*  竞态条件
 * */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int a = 0;
int b = 0;

int add()
{
    a++;
    sleep(10);
    b++;
    return a+b;
}
void sigcb(int signo)
{
    printf("signal-----%d\n", add());
}
int main()
{
    signal(SIGINT, sigcb);
    printf("main---%d\n", add());
    return 0;
}
