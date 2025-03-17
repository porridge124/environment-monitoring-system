#ifndef _PROJECT_H_
#define _PROJECT_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <linux/input.h>
#include <pthread.h>
#include <termios.h>

// 定义串口设备
#define COM2 "/dev/ttySAC1"  // MQ2烟雾传感器
#define COM4 "/dev/ttySAC3"  // GY39环境传感器

// 定义烟雾浓度阈值
#define SMOKE_THRESHOLD 50

// 全局变量
extern int input_x, input_y;
extern int smoke_value;
extern int lux_value;
extern float temp_value, humi_value, pressure_value, altitude_value;

// 烟雾相关汉字字模数据
extern unsigned char yan[31][24/8];   // 烟
extern unsigned char wu[31][24/8];    // 雾
extern unsigned char nong[31][24/8];  // 浓
extern unsigned char du[31][24/8];    // 度
extern unsigned char jian[31][24/8];  // 检
extern unsigned char ce[31][24/8];    // 测
extern unsigned char jing[31][24/8];  // 警
extern unsigned char gao[31][24/8];   // 告

// 环境监测相关汉字字模数据
extern unsigned char guang[31][24/8];  // 光
extern unsigned char zhao[31][24/8];   // 照
extern unsigned char qiang[31][24/8];  // 强
extern unsigned char wen[31][24/8];    // 温
extern unsigned char shi[31][24/8];    // 湿
extern unsigned char qi[31][24/8];     // 气
extern unsigned char ya[31][24/8];     // 压
extern unsigned char hai[31][24/8];    // 海
extern unsigned char ba[31][24/8];     // 拔

// 单位字模数据
extern unsigned char letter_l[31][8/8];   // l
extern unsigned char letter_u[31][8/8];   // u
extern unsigned char letter_x[31][8/8];   // x
extern unsigned char celsius[31][24/8];   // ℃
extern unsigned char percent[31][24/8];   // %
extern unsigned char letter_k[31][16/8];  // k
extern unsigned char letter_P[31][16/8];  // P
extern unsigned char letter_a[31][16/8];  // a
extern unsigned char letter_m[31][24/8];  // m

// 数字字模数据
extern unsigned char numbers[10][31][16/8];

// 显示函数
int show_bmp(char *picname, int b_x, int b_y);
void display_point(int x, int y, int color);
void lcd_clear(int color);
void draw_rectangle(int x, int y, int width, int height, int color);
void show_word(int x0, int y0, int w, int h, unsigned char word[][w/8], int color);
void show_number(int x0, int y0, int num, int color);
void show_float(int x0, int y0, float value, int precision, int color);

// 输入函数
int input();

// 串口函数
int init_serial(const char *file, int baudrate);
int get_smoke_value();
int get_gy39_data(unsigned char *buf, int *lux, float *temp, float *humi, float *pressure, float *altitude);

// 功能函数
int album();
int smoke_monitor();
int env_monitor();
int main();

#endif