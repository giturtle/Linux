#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace std;
int main(){
  int a = 100;
  pid_t pid = fork();
  if(pid < 0){
    perror("fork error");
  }
  if(pid == 0){
    cout << "child :" << getpid() << endl;
    cout << "a :" << &a << endl;
    cout << "a :" << a << endl;
  }
  else{
    a = 200;
    cout << "parent :" << getpid() << endl;
    cout << "a :" << &a << endl;
    cout << "a :" << a << endl;
  }
  return 0;
}
