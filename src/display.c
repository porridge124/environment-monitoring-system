#include "project.h"

// 全局变量
static int *lcd_ptr = NULL;
static int screen_width = 800;
static int screen_height = 480;

// 初始化LCD映射
int init_lcd_map()
{
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1) {
        perror("打开LCD设备失败");
        return -1;
    }

    // 内存映射
    lcd_ptr = (int *)mmap(NULL, screen_width * screen_height * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if (lcd_ptr == MAP_FAILED) {
        perror("内存映射失败");
        close(lcd_fd);
        return -1;
    }

    close(lcd_fd);
    return 0;
}

// 关闭LCD映射
void close_lcd_map()
{
    if (lcd_ptr != NULL) {
        munmap(lcd_ptr, screen_width * screen_height * 4);
        lcd_ptr = NULL;
    }
}

// 画点
void display_point(int x, int y, int color)
{
    if (lcd_ptr == NULL) {
        init_lcd_map();
    }
    
    if (x >= 0 && x < screen_width && y >= 0 && y < screen_height) {
        *(lcd_ptr + y * screen_width + x) = color;
    }
}

// LCD清屏
void lcd_clear(int color)
{
    int x, y;
    for (y = 0; y < screen_height; y++) {
        for (x = 0; x < screen_width; x++) {
            display_point(x, y, color);
        }
    }
}

// 绘制矩形
void draw_rectangle(int x, int y, int width, int height, int color)
{
    int i, j;
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            display_point(x + i, y + j, color);
        }
    }
}

// 显示字符
void show_word(int x0, int y0, int w, int h, unsigned char word[][w/8], int color)
{
    int i, j, k;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w/8; j++) {
            // 解析word[i][j]的8个bits位，为1就显示颜色，为0就不显示
            for (k = 7; k >= 0; k--) {
                if (word[i][j] & (1 << k)) {
                    // 画点
                    display_point(j*8 + (7-k) + x0, i + y0, color);
                }
            }
        }
    }
}

// 显示数字
void show_number(int x0, int y0, int num, int color)
{
    char num_str[16];
    int len, i;
    
    // 处理0的情况
    if (num == 0) {
        show_word(x0, y0, 16, 31, numbers[0], color);
        return;
    }
    
    // 转换为字符串
    sprintf(num_str, "%d", num);
    len = strlen(num_str);
    
    // 从右向左显示每一位数字
    for (i = 0; i < len; i++) {
        int digit = num_str[len - 1 - i] - '0';
        show_word(x0 - i * 20, y0, 16, 31, numbers[digit], color);
    }
}

// 显示浮点数
void show_float(int x0, int y0, float value, int precision, int color)
{
    char float_str[16];
    
    // 根据精度格式化浮点数
    switch (precision) {
        case 0:
            sprintf(float_str, "%.0f", value);
            break;
        case 1:
            sprintf(float_str, "%.1f", value);
            break;
        case 2:
            sprintf(float_str, "%.2f", value);
            break;
        default:
            sprintf(float_str, "%.1f", value);
    }
    
    // 显示字符串
    int len = strlen(float_str);
    int pos_x = x0;
    
    // 从右向左显示每一位字符
    for (int i = 0; i < len; i++) {
        char ch = float_str[len - 1 - i];
        if (ch == '.') {
            // 显示小数点
            draw_rectangle(pos_x - 5, y0 + 25, 5, 5, color);
            pos_x -= 10;
        } else {
            // 显示数字
            int digit = ch - '0';
            show_word(pos_x - 20, y0, 16, 31, numbers[digit], color);
            pos_x -= 20;
        }
    }
}