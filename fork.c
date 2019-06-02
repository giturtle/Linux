#include <stdio.h>                                                                     
#include <unistd.h>
#include <stdlib.h>


int main(){
  printf("parent pid:%d\n",getpid());
  pid_t pid = fork();
  if(pid < 0){
    return -1;
  }
  else if(pid == 0){
    printf("child![%d]\n",pid);
    exit(0);
  }
  else{
    printf("parent![%d]\n",getpid());
  }
  return 0;
}
