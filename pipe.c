#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    int pipefd[2];
    int ret = pipe(pipefd);
    if (ret < 0) {
        perror("pipe error");
        return -1;
    }
    int pid1 = fork();
    if (pid1 == 0) {
        //child1 ps -ef
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        execlp("ps", "ps", "-ef", NULL);
    }
    int pid2 = fork();
    if (pid2 == 0) {
        //child2 grep ssh
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        execlp("grep", "grep", "ssh", NULL);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
