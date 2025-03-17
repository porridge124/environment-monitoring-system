#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void Lcd_draw_point(int x,int y,int color);

int *plcd = NULL;

int main()
{
	//1.打开屏幕
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd == -1)
	{
		printf("open lcd failed!!\n");
		return -1;
	}
	//2.映射  
	plcd = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_SHARED,lcd_fd,0);	
	//3.全屏染蓝 
	int x,y;
	for(y=0;y<480;y++)
	{
		for(x=0;x<800;x++)
		{
			Lcd_draw_point(x,y,0xFF);
		}
	}
	//4.解映射 
	munmap(plcd,800*480*4);
	//5.关闭屏幕 
	close(lcd_fd);
	
}
//画点函数
void Lcd_draw_point(int x,int y,int color)
{
	if(x>=0&&x<800&&y>=0&&y<480)
	{
		*(plcd+y*800+x) = color;
	}	
}


