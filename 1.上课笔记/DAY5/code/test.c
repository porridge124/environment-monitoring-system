#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *func1(void *arg)
{
	int i = 0;
	while(1)
	{
		i++;
		printf("i=%d\n",i);
		sleep(1);
	}
}


int main()
{
	//先创建一个线程 
	pthread_t id;//申请一个id 
	pthread_create(&id,NULL,func1,NULL); 
	
	while(1)
	{
		printf("hello\n");
		sleep(1);
	}
	
	return 0;
}

