#include <stdio.h>                                                                     
  2 #include <unistd.h>
  3 #include <stdlib.h>
  4 
  5 int main(){
  6   printf("parent pid:%d\n",getpid());
  7   pid_t pid = fork();
  8   if(pid < 0){
  9     return -1;
 10   }
 11   else if(pid == 0){
 12     printf("child![%d]\n",pid);
 13     exit(0);
 14   }
 15   else{
 16     printf("parent![%d]\n",getpid());
 17   }
 18   return 0;
 19 }
