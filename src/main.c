#include "project.h"

int main()
{
    // 显示主界面
    show_bmp("main.bmp", 0, 0);
    
    while(1)
    {
        // 获取触摸输入
        input();
        
        // 打印当前触摸坐标，帮助调试
        printf("当前触摸坐标：(%d, %d)\n", input_x, input_y);
        
        // 相册功能区域
        if (input_x > 95 && input_x < 195 && input_y > 30 && input_y < 170)
        {
            printf("进入相册功能\n");
            album();
        }
        
        // 环境监测功能区域
        if (input_x > 445 && input_x < 545 && input_y > 30 && input_y < 170)
        {
            printf("进入环境监测功能\n");
            env_monitor();
        }
        
        // 烟雾浓度功能区域
        if (input_x > 650 && input_x < 800 && input_y > 30 && input_y < 170)
        {
            printf("进入烟雾浓度监测功能\n");
            smoke_monitor();
        }
    }
    
    return 0;
}