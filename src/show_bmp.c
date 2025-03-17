#include "project.h"

int show_bmp(char *picname, int b_x, int b_y)
{
    // 1. 打开文件（两个）
    // 对象：bmp图片和lcd设备文件
    int bmp_fd = open(picname, O_RDWR);
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (bmp_fd == -1)
    {
        printf("open bmp error\n");
        return -1;
    }
    if (lcd_fd == -1)
    {
        printf("open lcd error\n");
        return -1;
    }

    // 2. 读取图片的像素数据
    int bmp_w, bmp_h;
    
    lseek(bmp_fd, 18, SEEK_SET);
    read(bmp_fd, &bmp_w, 4);
    read(bmp_fd, &bmp_h, 4);
    printf("图片的宽：%d, 图片的高：%d\n", bmp_w, bmp_h);

    char buf[bmp_w * bmp_h * 3];
    bzero(buf, bmp_w * bmp_h * 3);  // 清空
    lseek(bmp_fd, 54, SEEK_SET);    // 从文件的起始位置开始向后偏移54字节
    read(bmp_fd, buf, bmp_w * bmp_h * 3);

    // 3. 直接处理得到的像素数据，写入到映射空间中    
    int *mmap_start = (int *)mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if (mmap_start == (int *)MAP_FAILED)
    {
        printf("mmap error\n");
        return -2;
    }

    int x, y, n;
    int *new_start = mmap_start + 800 * b_y + b_x;

    for(y = 0, n = 0; y < bmp_h; y++)
    {
        for(x = 0; x < bmp_w; x++, n += 3)
        {
            // 将BGR格式转换为RGB格式并存储
            // buf[n] 是B, buf[n+1] 是G, buf[n+2] 是R
            *(new_start + 800 * (bmp_h - 1 - y) + x) = buf[n] | (buf[n+1] << 8) | (buf[n+2] << 16);
        }
    }

    // 4. 注销映射空间
    munmap(mmap_start, 800*480*4);

    // 5. 关闭文件（两个）
    close(bmp_fd);
    close(lcd_fd);

    return 0;
}