#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
  char a[10] = {0};
  int i = 0;
  for(i = 0; i < 10;i++){
    a[i] = '-';
    printf("%s",a);
    fflush(stdout);
    usleep(100000);
  }
}
