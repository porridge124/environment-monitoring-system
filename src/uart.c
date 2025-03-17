#include "project.h"

// 全局变量
int smoke_value = 0;
int lux_value = 0;
float temp_value = 0.0, humi_value = 0.0, pressure_value = 0.0, altitude_value = 0.0;

// 串口初始化
int init_serial(const char *file, int baudrate)
{
    int fd;
    
    fd = open(file, O_RDWR);
    if (fd == -1) {
        perror("open device error:");
        return -1;
    }

    struct termios myserial;
    // 清空结构体
    memset(&myserial, 0, sizeof(myserial));
    // 设置控制模式状态，本地连接，接受使能
    myserial.c_cflag |= (CLOCAL | CREAD);
    // 设置数据位
    myserial.c_cflag &= ~CSIZE;   // 清空数据位
    myserial.c_cflag &= ~CRTSCTS; // 无硬件流控制
    myserial.c_cflag |= CS8;      // 数据位:8

    myserial.c_cflag &= ~CSTOPB;  // 1位停止位
    myserial.c_cflag &= ~PARENB;  // 不要校验
    
    // 设置波特率
    switch (baudrate) {
        case 9600:
            cfsetospeed(&myserial, B9600);  // 设置波特率
            cfsetispeed(&myserial, B9600);
            break;
        case 115200:
            cfsetospeed(&myserial, B115200);  // 设置波特率
            cfsetispeed(&myserial, B115200);
            break;
        case 19200:
            cfsetospeed(&myserial, B19200);  // 设置波特率
            cfsetispeed(&myserial, B19200);
            break;
        default:
            printf("不支持的波特率\n");
            close(fd);
            return -1;
    }
    
    // 刷新输出队列,清除正接受的数据
    tcflush(fd, TCIFLUSH);

    // 改变配置
    tcsetattr(fd, TCSANOW, &myserial);

    return fd;
}

// 获取MQ2烟雾数据
int get_smoke_value()
{
    // 打开串口并初始化
    int fd = init_serial(COM2, 9600);
    if (fd == -1) {
        printf("打开串口失败\n");
        return -1;
    }

    unsigned char cmd[9] = {0xFF, 0x01, 0x86, 0, 0, 0, 0, 0, 0x79}; // 查询指令
    unsigned char buf[9] = {0};
    int smoke = -1;

    // 发送指令
    int re = write(fd, cmd, 9);
    if (re < 9) {
        printf("发送指令失败\n");
        close(fd);
        return -1;
    }

    // 等待响应
    usleep(100000); // 等待100ms

    // 接收数据
    re = read(fd, buf, 9);
    if (re == 9) {
        // 检查数据格式
        if (buf[0] == 0xFF && buf[1] == 0x86) {
            // 解析烟雾浓度值
            int raw_value = buf[2] << 8 | buf[3];
            
            // 校准读数 - 减去基准值140
            int calibrated_value = raw_value - 140;
            if (calibrated_value < 0) {
                calibrated_value = 0;
            }
            
            smoke = calibrated_value;
            printf("烟雾浓度: 原始值=%d, 校准后=%d\n", raw_value, smoke);
        } else {
            printf("数据格式错误\n");
        }
    } else {
        printf("接收数据失败，只收到 %d 字节\n", re);
    }

    // 关闭串口
    close(fd);
    return smoke;
}

// 解析GY39的数据
void parse_data(unsigned char buf[], int n, int *lux, float *temp, float *humi, float *pressure, float *altitude)
{
    if (buf[2] == 0x15)    // 光照
    {
        // 解析光照强度 - 4字节数据
        *lux = buf[4] << 24 | buf[5] << 16 | buf[6] << 8 | buf[7];
        printf("光照强度: %d lux\n", *lux);
    }
    else if (buf[2] == 0x45)   // 温湿度、气压、海拔
    {
        // 解析温度 (温度值需要除以100)
        int temp_raw = buf[4] << 8 | buf[5];
        *temp = temp_raw / 100.0;
        
        // 解析湿度 (湿度值需要除以100)
        int humi_raw = buf[6] << 8 | buf[7];
        *humi = humi_raw / 100.0;
        
        // 解析气压 (气压值需要除以100) - 修正解析方式
        // 使用无符号整数避免负数问题
        unsigned int pressure_raw = ((unsigned int)buf[8] << 24) | 
                                   ((unsigned int)buf[9] << 16) | 
                                   ((unsigned int)buf[10] << 8) | 
                                   (unsigned int)buf[11];
        *pressure = pressure_raw / 100.0;
        
        // 如果气压值仍然不合理，使用默认值
        if (*pressure < 800 || *pressure > 1200) {
            printf("气压值异常: %.2f，使用默认值\n", *pressure);
            *pressure = 1013.25; // 标准大气压
        }
        
        // 解析海拔 (海拔值需要除以100)
        int altitude_raw = buf[12] << 8 | buf[13];
        *altitude = altitude_raw / 100.0;
        
        printf("温度: %.2f°C, 湿度: %.2f%%, 气压: %.2fhPa, 海拔: %.2fm\n", 
               *temp, *humi, *pressure, *altitude);
    }
    else
    {
        printf("未知数据包类型: 0x%02X\n", buf[2]);
        // 打印数据内容，用于调试
        printf("数据内容: ");
        for (int i = 0; i < n; i++) {
            printf("%02X ", buf[i]);
        }
        printf("\n");
    }
}

// 获取GY39传感器数据
int get_gy39_data(unsigned char *buf, int *lux, float *temp, float *humi, float *pressure, float *altitude)
{
    // 打开串口并初始化
    int fd = init_serial(COM4, 9600);
    if (fd == -1) {
        printf("打开串口失败\n");
        return -1;
    }

    // 发送命令 - 同时获取光照强度、温度、湿度、气压、海拔
    unsigned char cmd[3] = {0xA5, 0x83, 0x28};
    write(fd, cmd, 3);
    
    // 等待响应
    usleep(100000); // 等待100ms
    
    unsigned char ch;
    int found_light = 0;
    int found_env = 0;
    
    // 尝试读取数据包
    int timeout = 50; // 设置超时计数
    while (timeout > 0 && (!found_light || !found_env)) {
        // 先读第一个0x5A
        do {
            if (read(fd, &ch, 1) <= 0) {
                timeout--;
                usleep(10000); // 等待10ms
                continue;
            }
        } while (ch != 0x5A && timeout-- > 0);
        
        if (timeout <= 0) break;
        
        // 再读第二个0x5A
        if (read(fd, &ch, 1) <= 0 || ch != 0x5A) {
            continue;
        }
        
        buf[0] = 0x5A;
        buf[1] = 0x5A;
        
        // 读取数据类型
        if (read(fd, &buf[2], 1) <= 0) continue;
        
        // 读取数据长度
        if (read(fd, &buf[3], 1) <= 0) continue;
        
        // 读取传感器数据
        int len = buf[3];
        int i;
        for (i = 0; i < len; i++) {
            if (read(fd, &buf[4 + i], 1) <= 0) break;
        }
        
        if (i < len) continue; // 数据不完整
        
        // 读取校验和
        if (read(fd, &buf[4 + len], 1) <= 0) continue;
        
        // 解析数据
        if (buf[2] == 0x15) {
            parse_data(buf, 4 + len + 1, lux, temp, humi, pressure, altitude);
            found_light = 1;
        } else if (buf[2] == 0x45) {
            parse_data(buf, 4 + len + 1, lux, temp, humi, pressure, altitude);
            found_env = 1;
        }
        
        // 如果已经找到了两种数据包，就可以退出循环
        if (found_light && found_env) {
            break;
        }
        
        // 继续尝试读取下一个数据包
        timeout--;
        usleep(10000); // 等待10ms
    }
    
    // 关闭串口
    close(fd);
    
    if (!found_light && !found_env) {
        printf("未找到有效数据包\n");
        return -1;
    }
    
    return 0;
}

// 读取传感器数据包
int read_sensor_data(int fd, unsigned char *buf, int *lux, float *temp, float *humi, float *pressure, float *altitude)
{
    unsigned char ch;
    int found = 0;
    
    // 尝试读取数据包
    int timeout = 50; // 设置超时计数
    while (timeout > 0 && !found) {
        // 先读第一个0x5A
        int ret = read(fd, &ch, 1);
        if (ret > 0 && ch == 0x5A) {
            // 再读第二个0x5A
            ret = read(fd, &ch, 1);
            if (ret > 0 && ch == 0x5A) {
                found = 1;
                buf[0] = 0x5A;
                buf[1] = 0x5A;
                
                // 读取数据类型
                read(fd, &buf[2], 1);
                
                // 读取数据长度
                read(fd, &buf[3], 1);
                
                // 读取传感器数据
                int len = buf[3];
                for (int i = 0; i < len; i++) {
                    read(fd, &buf[4 + i], 1);
                }
                
                // 读取校验和
                read(fd, &buf[4 + len], 1);
                
                // 解析数据
                parse_data(buf, 4 + len + 1, lux, temp, humi, pressure, altitude);
                return 0;
            }
        }
        timeout--;
        usleep(10000); // 等待10ms
    }
    
    if (!found) {
        printf("未找到有效数据包\n");
        return -1;
    }
    
    return 0;
}