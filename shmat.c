#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#define IPC_KEY 0x12345678
#define PROJ_ID 12345
#define SHM_SIZE    4096

int main()
{
    int shmid;
    
    //1. 创建共享内存
    //key_t key = ftok(".", PROJ_ID);
    shmid = shmget(IPC_KEY, SHM_SIZE, IPC_CREAT|0666);
    if (shmid < 0) {
        perror("shmget error");
        return -1;
    }
    
    //2. 将共享内存映射到虚拟地址空间
    char *shm_start = (char *)shmat(shmid, NULL, 0);
    if (shm_start == (void*)-1) {
        perror("shmat error");
        return -1;
    }
    
    //3. 内存基本操作
    int i = 0;
    while(1) {
        printf("%s\n", shm_start);
        sleep(1);
    }
    
    //4. 解除映射
    shmdt(shm_start);
    
    //5. 删除共享内存
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
