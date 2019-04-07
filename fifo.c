#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    char *file = "./test.fifo";
    umask(0);
    int ret = mkfifo(file, 0664);
    if (ret < 0) {
        if (errno != EEXIST) {
            perror("mkfifo error");
            return -1;
        }
    }
    printf("open file\n");
    int fd = open(file, O_RDWR);
    if (fd < 0) {
        perror("open error");
        return -1;
    }
    printf("open success!!\n");
    while(1) {
        char buf[1024] = {0};
        int ret = read(fd, buf, 1023);
        if (ret > 0) {
            printf("read buf:[%s]\n", buf);
        }else if (ret == 0) {
            printf("write closed~~~\n");
        }else {
            perror("read error");
        }
        printf("----------\n");
    }
    close(fd);
    return 0;
}
