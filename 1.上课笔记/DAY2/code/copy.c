#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	//1.打开两个文件 
	int rd_fd = open("1.bmp",O_RDONLY); 
	if(-1 == rd_fd)
	{
		printf("open  failed!!\n");
		return -1;
	}

	int wr_fd = open("2.bmp",O_WRONLY);
	if(-1 == wr_fd)
	{
		printf("open  failed!!\n");
		return -1;
	}
	//2.循环读写 
	char buf[1024]={0};
	int i = 0;
	while(1)
	{
		int num = read(rd_fd,buf,1024);
		if(num == 0)
		{
			break;
		}
		write(wr_fd,buf,num);//读到字节数就是写入的字节数
		printf("第%d次写入了%d个字节的数据\n",++i,num);
	}
	
	//3.关闭文件 
	close(rd_fd);
	close(wr_fd);

	return 0;
}

