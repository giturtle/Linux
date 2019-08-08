#include <unistd.h>    
#include <stdlib.h>    
    
int main(){    
  int status;
  wait(&status);
  int pid = fork();    
  if(pid < 0){    
    perror("fork eror");    
  }    
  else if(pid == 0){    
    exit(0);    
    sleep(1);    
  }    
  while(waitpid(pid,&status,0) == 0){
		perror("waitpid error");
	}
  return 0;    
}    

