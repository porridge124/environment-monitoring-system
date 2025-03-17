#include "project.h"

// 全局变量 - 移除重复定义，这些变量已在uart.c中定义
// 只需要声明为extern
extern int lux_value;
extern float temp_value, humi_value, pressure_value, altitude_value;

// 环境监测线程
void *env_thread(void *arg)
{
    printf("环境监测线程启动\n");
    
    // 缓冲区
    unsigned char buf[32] = {0};
    
    while (1) {
        // 获取传感器数据
        if (get_gy39_data(buf, &lux_value, &temp_value, &humi_value, &pressure_value, &altitude_value) == 0) {
            // 清除上一次的数据 - 使用更大的区域确保完全覆盖
            
            // 光照强度 - 增加宽度
            draw_rectangle(350, 100, 250, 50, 0x000000);
            show_number(500, 100, lux_value, 0xFFFFFF);
            
            // 温度 - 增加宽度
            draw_rectangle(350, 150, 250, 50, 0x000000);
            show_float(500, 150, temp_value, 1, 0xFFFFFF);
            
            // 湿度 - 增加宽度
            draw_rectangle(350, 200, 250, 50, 0x000000);
            show_float(500, 200, humi_value, 1, 0xFFFFFF);
            
            // 气压 - 增加宽度并向右移动，转换为kPa显示
            draw_rectangle(350, 250, 250, 50, 0x000000);
            // 将hPa转换为kPa (除以10)，并保留1位小数
            show_float(500, 250, pressure_value / 10.0, 1, 0xFFFFFF);
            
            // 海拔 - 增加宽度
            draw_rectangle(350, 300, 250, 50, 0x000000);
            show_float(500, 300, altitude_value, 1, 0xFFFFFF);
        } else {
            printf("获取传感器数据失败\n");
        }
        
        // 每秒更新一次
        sleep(1);
    }
    
    return NULL;
}

/// 环境监测功能
int env_monitor()
{
    printf("进入环境监测功能\n");
    
    // 清屏，设置黑色背景
    lcd_clear(0x000000);
    
    // 显示标题
    show_word(300, 30, 24, 31, wen, 0xFFFFFF);  // 温
    show_word(330, 30, 24, 31, shi, 0xFFFFFF);  // 湿
    show_word(360, 30, 24, 31, du, 0xFFFFFF);   // 度
    show_word(390, 30, 24, 31, qi, 0xFFFFFF);   // 气
    show_word(420, 30, 24, 31, ya, 0xFFFFFF);   // 压
    
    // 显示各项指标名称 - 调整位置，向左移动
    // 光照强度
    show_word(150, 100, 24, 31, guang, 0xFFFFFF); // 光
    show_word(180, 100, 24, 31, zhao, 0xFFFFFF);  // 照
    show_word(210, 100, 24, 31, qiang, 0xFFFFFF); // 强
    show_word(240, 100, 24, 31, du, 0xFFFFFF);    // 度
    
    // 温度
    show_word(150, 150, 24, 31, wen, 0xFFFFFF);  // 温
    show_word(180, 150, 24, 31, du, 0xFFFFFF);   // 度
    
    // 湿度
    show_word(150, 200, 24, 31, shi, 0xFFFFFF);  // 湿
    show_word(180, 200, 24, 31, du, 0xFFFFFF);   // 度
    
    // 气压 (显示单位为kPa)
    show_word(150, 250, 24, 31, qi, 0xFFFFFF);   // 气
    show_word(180, 250, 24, 31, ya, 0xFFFFFF);   // 压
    
    // 海拔
    show_word(150, 300, 24, 31, hai, 0xFFFFFF);  // 海
    show_word(180, 300, 24, 31, ba, 0xFFFFFF);   // 拔
    
    // 显示单位
    // 光照强度单位 lux - 调整字符间距，增加间隔
    show_word(600, 100, 8, 31, letter_l, 0xFFFFFF);  // l
    show_word(615, 100, 8, 31, letter_u, 0xFFFFFF);  // u
    show_word(630, 100, 8, 31, letter_x, 0xFFFFFF);  // x
    
    // 温度单位 ℃
    show_word(600, 150, 24, 31, celsius, 0xFFFFFF);  // ℃
    
    // 湿度单位 %
    show_word(600, 200, 24, 31, percent, 0xFFFFFF);  // %
    
    // 气压单位 kPa
    show_word(600, 250, 16, 31, letter_k, 0xFFFFFF);  // k
    show_word(620, 250, 16, 31, letter_P, 0xFFFFFF);  // P
    show_word(640, 250, 16, 31, letter_a, 0xFFFFFF);  // a
    
    // 海拔单位 m
    show_word(600, 300, 24, 31, letter_m, 0xFFFFFF);  // m
    
    // 绘制退出按钮
    draw_rectangle(20, 20, 100, 50, 0xFF0000);
    
    // 创建环境监测线程
    pthread_t env_tid;
    if (pthread_create(&env_tid, NULL, env_thread, NULL) != 0) {
        perror("创建环境监测线程失败");
        return -1;
    }
    
    // 主循环，处理触摸输入
    while (1) {
        // 获取触摸输入
        input();
        printf("触摸坐标：(%d, %d)\n", input_x, input_y);
        
        // 检查是否点击了退出按钮
        if (input_x > 20 && input_x < 120 && input_y > 20 && input_y < 70) {
            printf("退出环境监测\n");
            
            // 取消线程
            pthread_cancel(env_tid);
            
            // 退出环境监测，恢复主界面
            show_bmp("main.bmp", 0, 0);
            
            return 0;
        }
    }
    
    return 0;
}