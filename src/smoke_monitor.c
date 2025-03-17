#include "project.h"

// 烟雾监测线程
void *mq2_thread(void *arg)
{
    printf("烟雾监测线程启动\n");
    int warning_state = 0;  // 警告显示状态，用于闪烁效果
    
    while (1) {
        // 获取烟雾浓度
        int new_value = get_smoke_value();
        
        if (new_value >= 0) {
            // 更新全局变量
            smoke_value = new_value;
            
            // 清除上一次的数据（使用与背景图片匹配的颜色）
            // 假设背景图片在数值显示区域是黑色的
            draw_rectangle(350, 200, 150, 50, 0x000000);
            
            // 显示数字
            if (smoke_value > SMOKE_THRESHOLD) {
                // 烟雾浓度过高，显示红色警告
                show_number(400, 200, smoke_value, 0xFF0000);  // 红色
                
                // 清除上一次的警告区域（使用与背景图片匹配的颜色）
                draw_rectangle(200, 300, 400, 50, 0x000000);
                
                // 警告闪烁效果
                if (warning_state) {
                    // 显示红色"警告"字样
                    show_word(350, 300, 24, 31, jing, 0xFF0000);  // 警
                    show_word(380, 300, 24, 31, gao, 0xFF0000);   // 告
                }
                warning_state = !warning_state;  // 切换状态
            } else {
                // 烟雾浓度正常，显示绿色
                show_number(400, 200, smoke_value, 0x00FF00);  // 绿色
                
                // 清除警告信息（使用与背景图片匹配的颜色）
                draw_rectangle(200, 300, 400, 50, 0x000000);
                warning_state = 0;  // 重置警告状态
            }
        } else {
            printf("获取烟雾浓度失败\n");
        }
        
        // 每秒更新一次
        sleep(1);
    }
    
    return NULL;
}

// 烟雾监测功能
int smoke_monitor()
{
    printf("进入烟雾浓度监测功能\n");
    
    // 使用黑色背景替代背景图片
    lcd_clear(0x000000);
    
    // 显示标题："烟雾浓度检测"
    show_word(300, 50, 24, 31, yan, 0xFFFFFF);  // 烟
    show_word(330, 50, 24, 31, wu, 0xFFFFFF);   // 雾
    show_word(360, 50, 24, 31, nong, 0xFFFFFF); // 浓
    show_word(390, 50, 24, 31, du, 0xFFFFFF);   // 度
    show_word(420, 50, 24, 31, jian, 0xFFFFFF); // 检
    show_word(450, 50, 24, 31, ce, 0xFFFFFF);   // 测
    
    // 显示说明："烟雾浓度"
    show_word(200, 200, 24, 31, yan, 0xFFFFFF);  // 烟
    show_word(230, 200, 24, 31, wu, 0xFFFFFF);   // 雾
    show_word(260, 200, 24, 31, nong, 0xFFFFFF); // 浓
    show_word(290, 200, 24, 31, du, 0xFFFFFF);   // 度
    
    // 绘制退出按钮
    draw_rectangle(20, 20, 100, 50, 0xFF0000);
    
    // 创建烟雾监测线程
    pthread_t mq2_tid;
    if (pthread_create(&mq2_tid, NULL, mq2_thread, NULL) != 0) {
        perror("创建烟雾监测线程失败");
        return -1;
    }
    
    // 主循环，处理触摸输入
    while (1) {
        // 获取触摸输入
        input();
        printf("触摸坐标：(%d, %d)\n", input_x, input_y);
        
        // 检查是否点击了退出按钮
        if (input_x > 20 && input_x < 120 && input_y > 20 && input_y < 70) {
            printf("退出烟雾监测\n");
            
            // 取消线程
            pthread_cancel(mq2_tid);
            
            // 返回主界面
            show_bmp("main.bmp", 0, 0);
            return 0;
        }
    }
    
    return 0;
}