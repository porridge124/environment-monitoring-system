#include "project.h"

int input_x, input_y;

int input()
{
    // 1. 打开设备文件
    int fd = open("/dev/input/event0", O_RDWR);
    if (fd == -1)
    {
        printf("open input error\n");
        return -1;
    }

    // 2. 读取数据 --> 压力事件 --> 坐标事件
    struct input_event buf;
    
    while(1)
    {
        read(fd, &buf, sizeof(buf));  // read函数具有阻塞的属性
        if (buf.type == EV_ABS && buf.code == ABS_X)
        {
            input_x = buf.value;
        }
        if (buf.type == EV_ABS && buf.code == ABS_Y)
        {
            input_y = buf.value;
        }
        if (buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 0)
        {
            printf("坐标：(%d, %d)\n", input_x, input_y);  // 当你抬手，打印最后一次的坐标
            break;  // 每次调用input函数，就可以拿到一次坐标
        }
    }

    // 3. 关闭文件
    close(fd);
    return 0;
}