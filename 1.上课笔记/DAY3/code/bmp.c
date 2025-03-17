#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

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
	//3.打开图片 
	int bmp_fd = open("5.bmp",O_RDWR);
	if(bmp_fd == -1)
	{
		printf("open lcd failed!!\n");
		return -1;
	}
	//4.读出图片的宽、高、色深
	int width = 0;
	lseek(bmp_fd,0x12,SEEK_SET);
	int ret = read(bmp_fd,&width,4);
	if(ret == -1)
	{
		printf("read error!!\n");
		return -1;
	}
	printf("width == %d\n",width);

	int high = 0;
	lseek(bmp_fd,0x16,SEEK_SET);
	ret = read(bmp_fd,&high,4);
	if(ret == -1)
	{
		printf("read error!!\n");
		return -1;
	}
	printf("high == %d\n",high);

	int depth = 0;
	lseek(bmp_fd,0x1C,SEEK_SET);
	ret = read(bmp_fd,&depth,2);
	if(ret == -1)
	{
		printf("read error!!\n");
		return -1;
	}
	printf("depth == %d\n",depth);
	//5.读取出整张图片的像素点 
	char p[abs(width)*abs(high)*(depth/8)];
	lseek(bmp_fd,0x36,SEEK_SET);
	read(bmp_fd,p,abs(width)*abs(high)*(depth/8));
	//6.解析数组 
	unsigned char a,r,g,b;
	int i=0;
	unsigned int color;
	int x,y;
	int x0,y0;//图片刷新的起始坐标 
	x0=0;
	y0=0;
	for(y=0;y<abs(high);y++)
	{
		for(x=0;x<abs(width);x++)
		{
			   b = p[i++];
			   g = p[i++];
			   r = p[i++];
			   if(depth == 32)
			   {
					a=p[i++];
			   }
			   else//24位图就保存了RGB
			   {
					a=0;
			   }
		    color = (a<<24)|(r<<16)|(g<<8)|(b);
			Lcd_draw_point(width>0?x+x0:x0+abs(width)-1-x,high>0?high-1-y+y0:y+y0,color);
		}
	}
	//7.关闭图片 
	close(bmp_fd);
	
	//8.解映射 
	munmap(plcd,800*480*4);
	//9.关闭屏幕 
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




