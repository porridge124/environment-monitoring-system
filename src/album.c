#include "project.h"

int album()
{
    // 显示相册界面
    show_bmp("album.bmp", 0, 0);
    
    while(1)
    {
        // 获取触摸输入
        input();
        
        // 打印当前触摸坐标，帮助调试
        printf("当前触摸坐标：(%d, %d)\n", input_x, input_y);

        // 退出区域 (左上角粉色框)
        // 调整为更精确的范围
        if(input_x > 20 && input_x < 120 && input_y > 20 && input_y < 70)
        {
            printf("退出相册功能\n");
            show_bmp("main.bmp", 0, 0);
            return 0;
        }

        // 自动切换区域 (左侧粉色框)
        // 调整为更精确的范围
        if(input_x > 90 && input_x < 270 && input_y > 170 && input_y < 240)
        {
            printf("自动切换\n");
            
            // 自动播放图片
            int i;
            for(i = 0; i < 3; i++)  // 循环播放3次
            {
                show_bmp("1.bmp", 0, 0);
                sleep(1);            // 程序休眠1秒
                show_bmp("2.bmp", 0, 0);
                sleep(1);            // 程序休眠1秒
                show_bmp("3.bmp", 0, 0);
                sleep(1);            // 程序休眠1秒
            }
            
            // 回到相册功能选择界面
            show_bmp("album.bmp", 0, 0);
        }

        // 手动切换区域 (右侧粉色框)
        // 调整为更精确的范围
        if(input_x > 530 && input_x < 710 && input_y > 170 && input_y < 240)
        {
            printf("手动切换\n");
            
            // 显示第一张图片
            int j = 1;
            show_bmp("1.bmp", 0, 0);
            
            // 手动浏览循环
            while(1)
            {
                input();
                printf("手动浏览模式坐标：(%d, %d)\n", input_x, input_y);
                
                // 退出手动浏览 - 使用与主界面相同的退出区域
                if(input_x > 20 && input_x < 120 && input_y > 20 && input_y < 70)
                {
                    printf("返回相册界面\n");
                    show_bmp("album.bmp", 0, 0);
                    break;
                }
                
                // 左侧区域 - 上一张
                if(input_x < 266)  // 屏幕左三分之一
                {
                    j--;
                    if(j == 0)
                    {
                        j = 3;
                    }
                    
                    // 显示当前图片
                    switch(j)
                    {
                        case 1: show_bmp("1.bmp", 0, 0); break;
                        case 2: show_bmp("2.bmp", 0, 0); break;
                        case 3: show_bmp("3.bmp", 0, 0); break;
                    }
                }
                
                // 右侧区域 - 下一张
                if(input_x > 533)  // 屏幕右三分之一
                {
                    j++;
                    if(j == 4)
                    {
                        j = 1;
                    }
                    
                    // 显示当前图片
                    switch(j)
                    {
                        case 1: show_bmp("1.bmp", 0, 0); break;
                        case 2: show_bmp("2.bmp", 0, 0); break;
                        case 3: show_bmp("3.bmp", 0, 0); break;
                    }
                }
            }
        }
    }
    
    return 0;
}
