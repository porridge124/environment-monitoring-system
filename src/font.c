#include "project.h"

// 烟雾浓度相关汉字字模数据
unsigned char yan[31][24/8] = {
    // 烟
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x1C,0x00,0x00},{0x1C,0xFF,0xFE},{0x1C,0xFF,0xFE},
    {0x1C,0xE3,0x0E},{0x1C,0xE3,0x8E},{0xFF,0xE3,0x8E},{0xFF,0xE3,0x8E},
    {0xFF,0xFF,0xFE},{0xFF,0xFF,0xFE},{0x7F,0xFF,0xFE},{0x7E,0xE7,0x8E},
    {0x1C,0xE7,0xCE},{0x1C,0xE7,0xCE},{0x1C,0xE7,0xEE},{0x3C,0xEF,0xEE},
    {0x3E,0xEE,0xFE},{0x3F,0xFE,0x7E},{0x3F,0xFC,0x7E},{0x7B,0xF8,0x0E},
    {0x73,0xE0,0x0E},{0xF0,0xFF,0xFE},{0xE0,0xFF,0xFE},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char wu[31][24/8] = {
    // 雾
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x3F,0xFF,0xFC},{0x3F,0xFF,0xF8},
    {0x7F,0xFF,0xFE},{0x7F,0xFF,0xFE},{0x70,0x3C,0x0E},{0x7F,0xFF,0xFE},
    {0x7F,0xFF,0xFE},{0x7F,0xFF,0xFE},{0x0F,0xFF,0xF0},{0x07,0xFF,0xF8},
    {0x1F,0xFF,0xF8},{0x7F,0x81,0xF8},{0x7B,0xFF,0xC0},{0x23,0xFF,0xF0},
    {0xFF,0xFF,0xFF},{0xFE,0x70,0x3F},{0x1F,0xFF,0xF8},{0x1F,0xFF,0xF8},
    {0x01,0xE0,0x38},{0x07,0xC0,0x78},{0x7F,0x9F,0xF0},{0x7E,0x1F,0xE0},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char nong[31][24/8] = {
    // 浓
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x20,0x03,0x80},{0x78,0x07,0x80},{0x7C,0x07,0x00},
    {0x3F,0xFF,0xFE},{0x1D,0xFF,0xFE},{0x01,0xFF,0xFE},{0x61,0xCF,0x0E},
    {0xF1,0xDF,0x0E},{0xF8,0x1F,0x00},{0x3C,0x3F,0x8E},{0x18,0x3B,0x9E},
    {0x00,0x7B,0xBC},{0x00,0xF9,0xF8},{0x19,0xF9,0xF0},{0x3D,0xF9,0xE0},
    {0x3F,0xF8,0xF0},{0x3F,0xF8,0x70},{0x3F,0x78,0x7C},{0x78,0x7B,0xBE},
    {0x78,0x7F,0x9F},{0x70,0x7F,0x0F},{0x70,0x7C,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char du[31][24/8] = {
    // 度
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x1C,0x00},{0x00,0x1E,0x00},{0x3F,0xFF,0xFF},
    {0x3F,0xFF,0xFF},{0x3F,0xFF,0xFE},{0x38,0xE0,0xF0},{0x3F,0xFF,0xFE},
    {0x3F,0xFF,0xFF},{0x3F,0xFF,0xFE},{0x38,0xE0,0xF0},{0x38,0xFF,0xF0},
    {0x38,0xFF,0xF0},{0x38,0xE0,0xF0},{0x3B,0xFF,0xF8},{0x3F,0xFF,0xF8},
    {0x3F,0xFF,0xF8},{0x38,0xF0,0xF0},{0x78,0x7B,0xE0},{0x78,0x3F,0xC0},
    {0x70,0x3F,0x80},{0xF1,0xFF,0xF8},{0xFF,0xF1,0xF8},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char jian[31][24/8] = {
    // 检
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x1C,0x03,0xC0},{0x1C,0x07,0xC0},{0x1C,0x07,0xC0},
    {0x1C,0x0F,0xE0},{0x1C,0x1E,0xF0},{0xFF,0xBC,0x78},{0xFF,0xFC,0x3C},
    {0x1C,0xF8,0x1F},{0x3D,0xFF,0xFF},{0x3F,0xFF,0xFE},{0x3F,0x3F,0xF8},
    {0x7F,0x87,0x00},{0x7F,0xF7,0x1C},{0xFC,0x77,0xBC},{0xFC,0x73,0xBC},
    {0xFC,0x7B,0xB8},{0xDC,0x3B,0xB8},{0x1C,0x3B,0xF8},{0x1C,0x38,0x70},
    {0x1C,0x00,0x70},{0x1D,0xFF,0xFF},{0x1D,0xFF,0xFF},{0x1C,0xFF,0xFE},
    {0x0C,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char ce[31][24/8] = {
    // 测
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x20,0x00,0x0E},{0x73,0xFF,0x0E},{0x7B,0xFF,0xFE},
    {0x3F,0xFF,0xFE},{0x1F,0x87,0xFE},{0x03,0xFF,0xFE},{0x03,0xFF,0xFE},
    {0xE3,0xFF,0xFE},{0xF3,0xFF,0xFE},{0x7F,0xFF,0xFE},{0x3B,0xFF,0xFE},
    {0x03,0xFF,0xFE},{0x03,0xF7,0xFE},{0x1B,0xF7,0xFE},{0x3F,0xF7,0xFE},
    {0x3F,0xF7,0xFE},{0x3B,0x76,0xFE},{0x38,0xF8,0xFE},{0x79,0xFC,0x0E},
    {0x7B,0xDF,0x0E},{0x77,0xCF,0x8E},{0xFF,0x87,0xFE},{0x7F,0x00,0x7C},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char jing[31][24/8] = {
    // 警
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x0E,0xE1,0xC0},{0xFF,0xFF,0xC0},{0xFF,0xFF,0xFF},
    {0x3C,0xE7,0xFF},{0x3F,0xFF,0x9C},{0x7F,0xFF,0xDC},{0xFF,0xBF,0xF8},
    {0xFF,0xB8,0xF8},{0x3F,0xB0,0xF8},{0x3F,0xF7,0xFF},{0x39,0xFF,0x8F},
    {0x7F,0xFF,0xFF},{0xFF,0xFF,0xFF},{0x00,0x00,0x00},{0x1F,0xFF,0xF0},
    {0x0F,0xFF,0xF0},{0x1F,0xFF,0xF8},{0x0F,0xFF,0xF0},{0x1F,0xFF,0xF0},
    {0x1F,0xFF,0xF8},{0x1C,0x00,0x38},{0x1F,0xFF,0xF8},{0x1F,0xFF,0xF8},
    {0x0C,0x00,0x30},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char gao[31][24/8] = {
    // 告
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x06,0x1C,0x00},{0x0F,0x1C,0x00},{0x0F,0x1C,0x00},
    {0x1F,0xFF,0xFC},{0x1F,0xFF,0xFE},{0x3F,0xFF,0xFC},{0x3C,0x1C,0x00},
    {0x78,0x1C,0x00},{0x30,0x1C,0x00},{0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x1F,0xFF,0xF8},{0x1F,0xFF,0xF8},
    {0x1F,0xFF,0xF8},{0x1C,0x00,0x38},{0x1C,0x00,0x38},{0x1C,0x00,0x38},
    {0x1C,0x00,0x38},{0x1F,0xFF,0xF8},{0x1F,0xFF,0xF8},{0x1C,0x00,0x38},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

// 数字字模数据
unsigned char numbers[10][31][16/8] = {
    // 0-9的字模数据，与之前相同
    // 0
    {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x07,0x80},
    {0x1F,0xE0},{0x3F,0xF0},{0x3C,0x78},{0x78,0x78},{0x78,0x78},{0x70,0x3C},{0xF0,0x3C},
    {0xF0,0x3C},{0xF0,0x3C},{0xF0,0x3C},{0xF0,0x3C},{0xF0,0x3C},{0x70,0x38},{0x78,0x78},
    {0x78,0x78},{0x3C,0xF0},{0x3F,0xF0},{0x1F,0xE0},{0x07,0x80},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00}},
    // 1
    {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x01,0xC0},
    {0x03,0xC0},{0x0F,0xC0},{0x3F,0xC0},{0x3F,0xC0},{0x33,0xC0},{0x03,0xC0},{0x03,0xC0},
    {0x03,0xC0},{0x03,0xC0},{0x03,0xC0},{0x03,0xC0},{0x03,0xC0},{0x03,0xC0},{0x03,0xC0},
    {0x03,0xC0},{0x03,0xC0},{0x03,0xC0},{0x03,0xC0},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00}},
    
    // 2
    {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x0F,0x80},
    {0x3F,0xE0},{0x7F,0xF0},{0x78,0xF8},{0x60,0x78},{0x00,0x78},{0x00,0x78},{0x00,0x78},
    {0x00,0xF0},{0x01,0xF0},{0x03,0xE0},{0x0F,0xC0},{0x1F,0x00},{0x3E,0x00},{0x3C,0x00},
    {0x78,0x00},{0x78,0x00},{0x7F,0xFC},{0x7F,0xFC},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00}},
    
    // 3
    {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x0F,0x80},
    {0x3F,0xE0},{0x3F,0xF0},{0x30,0xF0},{0x00,0xF0},{0x00,0x70},{0x00,0xF0},{0x00,0xF0},
    {0x1F,0xE0},{0x1F,0xC0},{0x1F,0xF0},{0x00,0xF0},{0x00,0x78},{0x00,0x78},{0x00,0x78},
    {0x00,0x78},{0x70,0xF0},{0x7F,0xF0},{0x7F,0xE0},{0x0F,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00}},
    
    // 4
    {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0xE0},
    {0x01,0xF0},{0x01,0xF0},{0x03,0xF0},{0x03,0xF0},{0x07,0xF0},{0x0F,0xF0},{0x0E,0xF0},
    {0x1E,0xF0},{0x3C,0xF0},{0x78,0xF0},{0x78,0xF0},{0xFF,0xFC},{0xFF,0xFC},{0xFF,0xFC},
    {0x00,0xF0},{0x00,0xF0},{0x00,0xF0},{0x00,0xF0},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00}},
    
    // 5
    {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x1F,0xF0},
    {0x3F,0xF0},{0x3F,0xF0},{0x3C,0x00},{0x3C,0x00},{0x38,0x00},{0x38,0x00},{0x38,0x00},
    {0x3F,0xC0},{0x3F,0xF0},{0x01,0xF0},{0x00,0x78},{0x00,0x78},{0x00,0x78},{0x00,0x78},
    {0x00,0x78},{0x70,0xF0},{0x7F,0xF0},{0x7F,0xE0},{0x1F,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00}},
    
    // 6
    {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x01,0xF0},
    {0x0F,0xF8},{0x1F,0xF8},{0x1E,0x00},{0x3C,0x00},{0x38,0x00},{0x78,0x00},{0x7B,0xC0},
    {0x7F,0xF0},{0x7F,0xF8},{0x7C,0x78},{0x78,0x3C},{0x78,0x3C},{0x78,0x3C},{0x78,0x3C},
    {0x78,0x38},{0x3C,0x78},{0x3F,0xF0},{0x1F,0xE0},{0x03,0x80},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00}},
    
    // 7
    {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x7F,0xF8},
    {0x7F,0xFC},{0x7F,0xF8},{0x00,0x78},{0x00,0x70},{0x00,0xF0},{0x00,0xE0},{0x01,0xE0},
    {0x01,0xC0},{0x03,0xC0},{0x03,0x80},{0x07,0x80},{0x07,0x80},{0x07,0x00},{0x0F,0x00},
    {0x0F,0x00},{0x0F,0x00},{0x1E,0x00},{0x1E,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00}},
    
    // 8
    {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x07,0x80},
    {0x1F,0xE0},{0x3F,0xF0},{0x3C,0x78},{0x78,0x78},{0x78,0x78},{0x78,0x78},{0x3C,0xF0},
    {0x1F,0xE0},{0x1F,0xE0},{0x3F,0xF0},{0x78,0x78},{0x70,0x38},{0xF0,0x3C},{0xF0,0x3C},
    {0x70,0x38},{0x78,0x78},{0x3F,0xF0},{0x1F,0xE0},{0x07,0x80},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00}},
    
    // 9
    {{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x07,0x80},
    {0x1F,0xE0},{0x3F,0xF0},{0x78,0xF8},{0x78,0x78},{0x70,0x78},{0xF0,0x38},{0xF0,0x3C},
    {0x78,0x7C},{0x7C,0xFC},{0x3F,0xFC},{0x1F,0xF8},{0x07,0x38},{0x00,0x78},{0x00,0x78},
    {0x00,0xF0},{0x21,0xF0},{0x7F,0xE0},{0x7F,0xC0},{0x1E,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00}}
};

// 环境监测相关汉字字模数据
unsigned char guang[31][24/8] = {
    // 光
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x3C,0x00},{0x00,0x3C,0x00},{0x38,0x3C,0x1C},
    {0x3C,0x3C,0x3C},{0x1E,0x3C,0x78},{0x0F,0x3C,0xF8},{0x0F,0xBD,0xF0},
    {0x07,0xBD,0xE0},{0x02,0x3C,0xC0},{0x00,0x3C,0x00},{0xFF,0xFF,0xFF},
    {0xFF,0xFF,0xFF},{0x01,0xC7,0x80},{0x01,0xC7,0x80},{0x03,0xC7,0x80},
    {0x03,0xC7,0x80},{0x03,0x87,0x87},{0x07,0x87,0x87},{0x0F,0x87,0x87},
    {0x1F,0x07,0x87},{0x7E,0x07,0x8F},{0xFC,0x03,0xFF},{0xF0,0x01,0xFE},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char zhao[31][24/8] = {
    // 照
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x7F,0xFF,0xFE},{0x7F,0xFF,0xFE},
    {0x71,0xC7,0x0E},{0x71,0xC7,0x0E},{0x71,0xCF,0x0E},{0x71,0xCF,0xFE},
    {0x7F,0xDF,0xFC},{0x7F,0xFC,0xF8},{0x7F,0xFF,0xFE},{0x71,0xDF,0xFE},
    {0x71,0xDC,0x0E},{0x71,0xDC,0x0E},{0x71,0xDC,0x0E},{0x7F,0xDF,0xFE},
    {0x7F,0xDF,0xFE},{0x71,0xDC,0x0E},{0x38,0x86,0x18},{0x39,0xC7,0x3C},
    {0x79,0xC7,0x9E},{0x71,0xE3,0x8E},{0xF0,0xE3,0xCF},{0xE0,0xE1,0x06},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char qiang[31][24/8] = {
    // 强
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0xFF,0xFF,0xFC},{0xFF,0xFF,0xFC},
    {0x07,0xF8,0x1C},{0x07,0xF8,0x1C},{0x07,0xF8,0x1C},{0x07,0xFF,0xFC},
    {0x7F,0xFF,0xFC},{0x7F,0xFB,0x9C},{0x77,0x83,0x80},{0xF0,0xFF,0xFE},
    {0xF0,0xFF,0xFE},{0xFF,0xF3,0x8E},{0xFF,0xF3,0x8E},{0x07,0xF3,0x8E},
    {0x07,0xFF,0xFE},{0x07,0xFF,0xFE},{0x07,0xF3,0x8C},{0x07,0x03,0x9E},
    {0x07,0x03,0x8E},{0x6F,0xFF,0xFF},{0x7F,0xFF,0xFF},{0x7E,0xF8,0x07},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char wen[31][24/8] = {
    // 温
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x70,0x00,0x00},{0x79,0xFF,0xFC},{0x7D,0xFF,0xFC},
    {0x3F,0xE0,0x1C},{0x1F,0xE0,0x1C},{0x01,0xFF,0xFC},{0x61,0xFF,0xFC},
    {0xF1,0xE0,0x1C},{0xF9,0xFF,0xFC},{0x3D,0xFF,0xFC},{0x1D,0xFF,0xFC},
    {0x00,0xE0,0x1C},{0x01,0xFF,0xFC},{0x39,0xFF,0xFE},{0x3D,0xFF,0xFE},
    {0x3D,0xDD,0xDE},{0x39,0xDD,0xDE},{0x39,0xDD,0xDE},{0x79,0xDD,0xDE},
    {0x79,0xDD,0xDE},{0x7F,0xFF,0xFF},{0xFF,0xFF,0xFF},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char shi[31][24/8] = {
    // 湿
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x20,0x00,0x00},{0x79,0xFF,0xFC},{0x7D,0xFF,0xFC},
    {0x3F,0xE0,0x1C},{0x1F,0xE0,0x1C},{0x01,0xFF,0xFC},{0x61,0xFF,0xFC},
    {0xF1,0xE0,0x1C},{0xF9,0xE0,0x1C},{0x3D,0xFF,0xFC},{0x1D,0xFF,0xFC},
    {0x01,0xFC,0xFC},{0x01,0x9C,0xE6},{0x3B,0x9C,0xE7},{0x3F,0xDC,0xEF},
    {0x39,0xDC,0xFE},{0x39,0xFC,0xFC},{0x78,0xFC,0xFC},{0x78,0xDC,0xF8},
    {0x78,0x1C,0xE0},{0x77,0xFF,0xFF},{0xF7,0xFF,0xFF},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char qi[31][24/8] = {
    // 气
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x0F,0x00,0x00},{0x0F,0x00,0x00},{0x0F,0xFF,0xFE},
    {0x1F,0xFF,0xFE},{0x1F,0xFF,0xFE},{0x3C,0x00,0x00},{0x3F,0xFF,0xF8},
    {0x7F,0xFF,0xF8},{0xF0,0x00,0x00},{0xE0,0x00,0x00},{0xFF,0xFF,0xF0},
    {0xFF,0xFF,0xF0},{0x00,0x00,0x70},{0x00,0x00,0x70},{0x00,0x00,0x70},
    {0x00,0x00,0x70},{0x00,0x00,0x77},{0x00,0x00,0x77},{0x00,0x00,0x7F},
    {0x00,0x00,0x7F},{0x00,0x00,0x3F},{0x00,0x00,0x3F},{0x00,0x00,0x1E},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char ya[31][24/8] = {
    // 压
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x1F,0xFF,0xFE},{0x3F,0xFF,0xFF},
    {0x3F,0xFF,0xFF},{0x3C,0x06,0x00},{0x3C,0x07,0x00},{0x3C,0x07,0x00},
    {0x3C,0x07,0x00},{0x3C,0x07,0x00},{0x3C,0x07,0x00},{0x3F,0xFF,0xFE},
    {0x3F,0xFF,0xFE},{0x3C,0x07,0x00},{0x3C,0x07,0x70},{0x3C,0x07,0x78},
    {0x3C,0x07,0x78},{0x38,0x07,0x3C},{0x38,0x07,0x1C},{0x78,0x07,0x00},
    {0x78,0x07,0x00},{0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF},{0x60,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char hai[31][24/8] = {
    // 海
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x70,0x78,0x00},{0x78,0x70,0x00},{0x7C,0xFF,0xFF},
    {0x1F,0xFF,0xFF},{0x0D,0xC0,0x00},{0x03,0xC0,0x00},{0x67,0xFF,0xFC},
    {0xF7,0xFF,0xFC},{0xF8,0xEF,0x1C},{0x3C,0xE7,0x9C},{0x19,0xE3,0x9C},
    {0x07,0xFF,0xFF},{0x07,0xFF,0xFF},{0x1F,0xFF,0xFF},{0x3D,0xCE,0x1C},
    {0x3D,0xCF,0x1C},{0x39,0xC7,0x9C},{0x3B,0xFF,0xFE},{0x7B,0xFF,0xFF},
    {0x79,0xFF,0xFF},{0x70,0x00,0x38},{0x70,0x07,0xF8},{0xF0,0x07,0xF0},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

unsigned char ba[31][24/8] = {
    // 拔
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x1C,0x1C,0xE0},{0x1C,0x1C,0xF0},{0x1C,0x1C,0x7C},
    {0x1C,0x1C,0x38},{0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF},{0x1C,0x3C,0x00},
    {0x1C,0x3C,0x00},{0x1C,0x38,0x00},{0x1C,0x3F,0xFC},{0x1F,0xFF,0xFC},
    {0x3F,0xFC,0x3C},{0xFE,0x7C,0x38},{0xFC,0xFC,0x38},{0x9C,0xEE,0x70},
    {0x1D,0xEF,0xF0},{0x1D,0xC7,0xE0},{0x1F,0xC7,0xC0},{0x1F,0x87,0xE0},
    {0x1F,0x9F,0xF8},{0xFF,0x7E,0xFE},{0xFD,0xFC,0x3F},{0xF9,0xF0,0x0E},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};
// 添加到font.c文件末尾

// 单位字模数据
// 英文字母 l
unsigned char letter_l[31][8/8] = {
    {0x00},{0x00},{0x00},{0x00},{0x00},{0x1E},{0x3C},{0x3C},
    {0x3C},{0x3C},{0x3C},{0x3C},{0x3C},{0x3C},{0x3C},{0x3C},
    {0x3C},{0x3C},{0x3C},{0x3C},{0x3C},{0x3C},{0x3C},{0x3C},
    {0x3C},{0x00},{0x00},{0x00},{0x00},{0x00},{0x00}
};

// 英文字母 u
unsigned char letter_u[31][8/8] = {
    {0x00},{0x00},{0x00},{0x00},{0x00},{0x00},{0x00},{0x00},
    {0x00},{0x00},{0x00},{0x00},{0x3C},{0x3C},{0x3C},{0x3C},
    {0x3C},{0x3C},{0x3C},{0x3C},{0x3C},{0x3C},{0x3E},{0x1E},
    {0x0E},{0x02},{0x00},{0x00},{0x00},{0x00},{0x00}
};

// 英文字母 x
unsigned char letter_x[31][8/8] = {
    {0x00},{0x00},{0x00},{0x00},{0x00},{0x00},{0x00},{0x00},
    {0x00},{0x00},{0x00},{0x00},{0x78},{0x3C},{0x3C},{0x1E},
    {0x0E},{0x0E},{0x06},{0x0E},{0x0E},{0x1E},{0x3C},{0x3C},
    {0x78},{0x00},{0x00},{0x00},{0x00},{0x00},{0x00}
};

// 摄氏度符号 ℃
unsigned char celsius[31][24/8] = {
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x3C,0x01,0xF8},{0x7E,0x0F,0xFE},
    {0xF7,0x1F,0xFE},{0xE7,0x3F,0x06},{0xE7,0x7C,0x00},{0xFF,0x78,0x00},
    {0x7E,0xF0,0x00},{0x18,0xF0,0x00},{0x00,0xF0,0x00},{0x00,0xF0,0x00},
    {0x00,0xF0,0x00},{0x00,0xF0,0x00},{0x00,0xF0,0x00},{0x00,0xF0,0x00},
    {0x00,0x78,0x00},{0x00,0x7C,0x00},{0x00,0x3F,0x0E},{0x00,0x1F,0xFE},
    {0x00,0x0F,0xFE},{0x00,0x01,0xF0},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

// 百分比符号 %
unsigned char percent[31][24/8] = {
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x0E,0x01,0x80},{0x3F,0x83,0xC0},
    {0x7B,0xC3,0x80},{0x71,0xC7,0x00},{0xF1,0xCF,0x00},{0xF1,0xCE,0x00},
    {0xF1,0xDE,0x00},{0x73,0xFC,0x00},{0x7F,0xB8,0x00},{0x3F,0x79,0x80},
    {0x00,0x77,0xF0},{0x00,0xEF,0xF0},{0x01,0xEE,0x78},{0x01,0xDE,0x38},
    {0x03,0x9C,0x38},{0x07,0x9E,0x38},{0x07,0x1E,0x78},{0x0F,0x0F,0xF0},
    {0x1E,0x07,0xE0},{0x0C,0x01,0x80},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};

// 英文字母 k
unsigned char letter_k[31][16/8] = {
    {0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x30,0x00},{0x78,0x00},{0x78,0x00},{0x78,0x00},{0x78,0x00},
    {0x78,0x00},{0x78,0x00},{0x78,0xF8},{0x78,0xF0},{0x79,0xE0},
    {0x7B,0xC0},{0x7F,0x80},{0x7F,0x00},{0x7F,0x00},{0x7F,0x80},
    {0x7F,0xC0},{0x7B,0xE0},{0x79,0xF0},{0x78,0xF0},{0x78,0x78},
    {0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00}
};

// 英文字母 P
unsigned char letter_P[31][16/8] = {
    {0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x3F,0x80},{0x3F,0xF0},{0x3F,0xF8},{0x38,0x78},
    {0x38,0x38},{0x38,0x38},{0x38,0x38},{0x38,0x38},{0x38,0x38},
    {0x38,0x78},{0x3F,0xF8},{0x3F,0xF0},{0x3F,0x80},{0x38,0x00},
    {0x38,0x00},{0x38,0x00},{0x38,0x00},{0x38,0x00},{0x38,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00}
};

// 英文字母 a
unsigned char letter_a[31][16/8] = {
    {0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00},{0x07,0x00},{0x3F,0xE0},{0x3F,0xF0},{0x30,0xF0},
    {0x00,0xF0},{0x00,0xF0},{0x1F,0xF0},{0x3F,0xF0},{0x78,0xF0},
    {0xF0,0xF0},{0xF0,0xF0},{0xF9,0xF0},{0x7F,0xF0},{0x3F,0xF0},
    {0x0E,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},{0x00,0x00},
    {0x00,0x00}
};

// 英文字母 m
unsigned char letter_m[31][24/8] = {
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x01,0xC1,0xC0},{0x7F,0xF7,0xF0},{0x7F,0xFF,0xF8},{0x7C,0x7E,0x78},
    {0x7C,0x7C,0x78},{0x78,0x78,0x38},{0x78,0x78,0x38},{0x78,0x78,0x38},
    {0x78,0x78,0x38},{0x78,0x78,0x38},{0x78,0x78,0x38},{0x78,0x78,0x38},
    {0x78,0x78,0x38},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},
    {0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}
};