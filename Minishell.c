/*    
 * minishell的实现    
*/    
#include <stdio.h>    
#include <stdlib.h>    
#include <unistd.h>    
#include <ctype.h>                                                                     
#include <wait.h>    
    
int main(){    
  while(1){    
    //1. 读入数据    
        
    printf("[lu@localhost]$ ");    
    fflush(stdout); //刷新到缓冲区，直接显示    
    char buf[1024] = {0};    
    if(scanf("%[^\n]%*c",buf) != 1){//正则：遇到换行为止，%*c表示之后的内容抛弃    
      getchar();//获取一个回车    
    }    
    //scanf是从缓冲区读入数据，如果输入ls -l\n，就会死循环    
    printf("%s\n",buf);    
    
    //2. 解析数据,去除空白字符，获取程序名称和参数
        char *ptr = buf;
    char *argv[32];
    int argc = 0;
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
    int pid = fork();
    if(pid < 0){
      exit(-1);
    }
    else if(pid == 0){
      execvp(argv[0],argv);
      //防止子进程替换失败
      exit(0);
    }
    wait(NULL);
  }
  return 0;                                                                            
}
