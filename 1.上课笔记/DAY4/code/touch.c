#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
//画点函数
void Lcd_draw_point(int x,int y,int color);
void lcd_clear(int color);
int *plcd = NULL;



int main()
{
	//打开LCD文件 打开映射

	//1.打开触摸屏设备文件 
	int tc_fd = open("/dev/input/event0",O_RDWR);
	if(tc_fd == -1)
	{
		printf("open touch fail\n");
		return -1;
	}

	//2.创建一个事件结构体来保存信息
	struct input_event ev;
	int x,y;//需要获取的x和y的坐标

	//3.不停的来获取并且解析触摸屏事件
	while(1)
	{
		//读取输入事件 
		read(tc_fd,&ev,sizeof(ev));
		
		//获取x的坐标值 
		if(ev.type == EV_ABS && ev.code == ABS_X)
		{
			x = ev.value*800/1024;
		}

		//获取y的坐标值 
		if(ev.type == EV_ABS && ev.code == ABS_Y)
		{
			y = ev.value*480/600;
		}

		
		printf("(%d,%d)\n",x,y);
	}

	
	close(tc_fd);

	return 0;
}


//画点函数
void Lcd_draw_point(int x,int y,int color)
{
	if(x>=0&&x<800&&y>=0&&y<480)
	{
		*(plcd+y*800+x) = color;
	}	
}


//lcd清屏函数
void lcd_clear(int color)
{
	int x,y;
	for(y = 0;y < 800;y++)
	{
		for(x = 0;x < 480;x++)
		{
			Lcd_draw_point(x,y,color);
		}
	}
}











