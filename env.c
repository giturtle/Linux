/*获取环境变量的demo*/	/*打印环境变量*/

//方法一
#include <stdlib.h>
#include <stdio.h>
int main(int argc,int *argv[],char *env[]){
	int i;
	for(i = 0;env[i] != NULL;i++){
		printf("env[%d] = [%s]\n",i,env[i]);
	}
	return 0;
}


//方法二

int main(int argc,int *argv[],char *env[]){
	extern char **environ;		//在头文件中没有包含，但在库中包含
	int i;
	for(i = 0;environ[i] != NULL;i++){
		printf("environ[%d] = [%s]\n",i,environ[i]);
	}
	return 0;
}

//方法三    getenv()接口,需要包含头文件 <stdlib.h> 
	printf("PATH:[%s]\n",getenv("PATH"));
