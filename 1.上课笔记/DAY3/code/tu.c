#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	//1.打开屏幕 
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd == -1)
	{
		printf("open lcd failed!!\n");
		return -1;
	}
	//2.刷点 
	unsigned int RED = 0xFF0000;
	unsigned int white = 0x00;
	int x,y;
	for(y=0;y<480;y++)
	{
		for(x=0;x<800;x++)
		{
			if(x>200&&x<600&&y>120&&y<360)
			{
				write(lcd_fd,&RED,4);
			}
			else
			{
				write(lcd_fd,&white,4);
			}
		}
	}
	//3.关闭屏幕
	close(lcd_fd);

	return 0;
}

