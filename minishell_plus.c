/*
 * minishell的实现
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <wait.h>
#include <string.h>

char *argv[32];
int argc = 0;
char buf[1024] = {0};

void do_face(){
  printf("[lu@localhost]$ ");
  fflush(stdout); //刷新到缓冲区，直接显示
  memset(buf,0x00,1024);
  if(scanf("%[^\n]%*c",buf) != 1){//正则：遇到换行为止，%*c表示之后的内容抛弃
    getchar();//获取一个回车
  }
  return;
}
void do_parse(){
  char *ptr = buf;
  argc = 0;
  while(*ptr != '\0'){
    //当前位置非空白字符
    if(!isspace(*ptr)){
      argv[argc++] = ptr;
      while(!isspace(*ptr) && *ptr != '\0'){
        ptr++;
      }
    }
    else{
      *ptr = '\0'; 
      ptr++;
    }
  }
  argv[argc] = NULL;
  return;
}
int main(){
  //ls >> > a.txt文件名
  //int fd = open("a.txt");
  //dup2(fd,1);
  while(1){
    do_face(); 
    int redirect = 0;
    char *file = NULL;
    char *ptr = buf;
    while(*ptr != '\0'){
      if(*ptr == '>'){
        redirect = 1;//清空重定向
        *ptr++ = '\0';
        if(*ptr == '>'){
          redirect = 2; //追加重定向
          *ptr++ = '\0';
        }
        while(isspace(*ptr) && *ptr != '\0'){
          //重定向符号和文件名中间有空格
          ptr++;
        }
        file = ptr;
        //文件名
        while(!isspace(*ptr) && *ptr != '\0'){
          //重定向符号和文件名中间有空格
          ptr++;
        }
        *ptr = '\0';
      }
      ptr++;
    }
    //scanf是从缓冲区读入数据，如果输入ls -l\n，就会死循环
    do_parse();
    int pid = fork();
    if(pid < 0){
      exit(-1);
    }
    else if(pid == 0){
      if(redirect == 1){
        int fd = open(file,O_CREAT | O_WRONLY | O_TRUNC,0664);
        dup2(fd,1);
        //重定向如果在父进程中做了，就无法正确打印了,只能在子进程中完成
      }
      else if(redirect == 2){
        int fd = open(file,O_CREAT | O_WRONLY | O_TRUNC,0664);
        dup2(fd,1);
      }
      execvp(argv[0],argv);
      //防止子进程替换失败
      exit(0);
    }
    wait(NULL);
  }
  return 0;
}
