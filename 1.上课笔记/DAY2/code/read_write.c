/*
	现在有一个文件4.txt:aaabbbccc 
	先打开文件 读取这个文件3个字节的数据:aaa 
	接着写入3字节的数据"111" 
	请问这个文件里面内容会变成？
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	//1.打开文件  
	int fd = open("./4.txt",O_RDWR);
	if(-1 == fd)
	{
		printf("open 4.txt failed!!\n");
		return -1;
	}
	//2.读取数据 
	char read_buf[1024]={0};
	int num1 = read(fd,read_buf,3);
	if(num1 == -1)
	{
		printf("read error!!\n");
		return -1;
	}
	//3.打印数据 
	printf("从文件中读取了%d个字节，内容:%s\n",num1,read_buf);
	//4.写入数据  
	int num2 = write(fd,"111",3);
	if(num2 == -1)
	{
		printf("write error!!\n");
		return -1;
	}
	
	return 0;
}

