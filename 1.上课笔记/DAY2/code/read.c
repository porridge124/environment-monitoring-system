#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/*
	练习1：从一个1.txt文件中读取出数据并打印  
			1.txt:nanhuadaxue!!!!! 
*/
int main()
{
	//1.打开文件  
	int read_fd = open("./1.txt",O_RDWR);
	if(-1 == read_fd)
	{
		printf("open 1.txt failed!!\n");
		return -1;
	}
	//2.读取数据 
	char read_buf[1024]={0};
	int num = read(read_fd,read_buf,30);
	if(num == -1)
	{
		printf("read error!!\n");
		return -1;
	}
	//3.打印数据 
	printf("从文件中读取了%d个字节，内容:%s\n",num,read_buf);

	//4.关闭文件 
	close(read_fd);
	
	return 0;
}


