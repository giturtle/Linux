/*
 * 系统调用接口使用
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
  umask(0);
  int fd = open("./env.c",O_RDWR | O_CREAT | O_APPEND,0777);//此时env.c已被截断，清空了
  //如果不给定0777，创建的文件没有权限,如果不加0，容易导致向前进位，进而变成非用户指定的权限码
  if(fd < 0){
    perror("open error");
    return -1;
  }
  char buf[1024] = "giturtle";
  int ret = write(fd,buf,strlen(buf));
  if(ret < 0){
    perror("write error");
    return -1;
  }
  lseek(fd,0,SEEK_SET);
  memset(buf,0x00,1024); //将buf清空
  ret = read(fd,buf,1023);
  if(ret < 0){
    perror("read error");
    return -1;
  }
  printf("read buf:[%s]\n",buf);
  close(fd);
  return 0;
}
