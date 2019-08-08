

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
using namespace std;

#if 0
//阻塞等待
int main(){
  pid_t pid = fork();
  if(pid < 0)
    perror("fork error");
  else if(pid == 0){
    cout << "child:" << "[" << getpid() << "]" << "is running\n";
    sleep(5);
    exit(257);
  }
  else{
    int status = 0;
    pid_t pid = waitpid(-1,&status,0);    //阻塞式接收
    cout << "i am waiting" << endl;

    if(WIFEXITED(status) == pid)
      cout << "wait child 5s success,child return code is: " << WEXITSTATUS(status) << endl;
    else{
      cout << "wait child failed,return\n";
      return -1;
    }
  }
  return 0;
}
#endif

//非阻塞等待
int main(){
  pid_t pid = fork();
  if(pid < 0){
    perror("fork error");
    exit(1);
  }
  else if(pid == 0){
    cout << "child:" << "[" << getpid() << "]" << "is running\n";
    sleep(5);
    exit(257);
  }
  else{
    int status = 0;
    pid_t ret;
    do{
      ret = waitpid(-1,&status,WNOHANG);
      if(ret == 0)
        cout << "child is running\n";
      sleep(1);
    }while(ret == 0);

    if(WIFEXITED(status) && ret == pid)
      cout << "wait child success,child return code is " << WEXITSTATUS(status) << endl;
    else{
      cout << "wait child failed" << endl;
      return -1;
    }
  }
  return 0;
}
