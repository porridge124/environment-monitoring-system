#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	//1.打开文件  
	int fd = open("./3.txt",O_RDWR);
	if(-1 == fd)
	{
		printf("open 3.txt failed!!\n");
		return -1;
	}
	//2.写入数据
	char buf[]="1234abcd";
	int num = write(fd,buf,strlen(buf));
	if(num == -1)
	{
		printf("write error!!\n");
		return -1;
	}
	printf("num:%d\n",num);
	
	return 0;
}

