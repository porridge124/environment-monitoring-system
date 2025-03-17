#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	//1.打开文件 
	int fd = open("./1.txt",O_RDWR);
	if(fd == -1)
	{
		printf("open 1.txt error!!\n");
		
		return -1;
	}
	
	printf("OK!\n");

	//2.关闭文件 
	close(fd);
	
	return 0;
}

