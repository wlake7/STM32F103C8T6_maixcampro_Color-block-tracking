# 激光追踪系统

基于STM32F103C8T6和MaixCamPro的激光追踪系统，采用三层控制架构实现高精度激光目标追踪。

## 系统架构

```
MaixCamPro (图像处理) ↔ STM32F103C8T6 (主控制器) ↔ 控制板 (舵机驱动) ↔ 舵机
```

## 快速开始

### 1. 硬件连接
```
MaixCam UART → STM32 UART1 (PA9/PA10)
STM32 UART2 (PA2/PA3) → 控制板
控制板 → 舵机 (串行连接)
```

### 2. 软件配置

#### STM32端
```bash
cd stm32
# 使用Keil MDK编译烧录
```

#### MaixCam端
```bash
cd maixcam
python main.py
```

### 3. 系统操作
- **按键1**: 切换系统状态 (标定→追踪→手动)
- **按键2**: 舵机测试功能 (手动模式下)

## 配置参数

### 舵机配置
```c
// 舵机ID
#define SERVO_ID_HORIZONTAL  2  // 水平舵机
#define SERVO_ID_VERTICAL    1  // 垂直舵机

// 位置范围
#define SERVO_POS_MIN        0
#define SERVO_POS_MAX        1000
#define SERVO_POS_CENTER     500
```

### 通信配置
```python
# MaixCam配置
UART_BAUDRATE = 115200
UART_DEVICE = "/dev/ttyS1"

# 协议头
HEADER_BYTE1 = 0xAA
HEADER_BYTE2 = 0x55
```

### PID参数
```c
// 水平PID
#define PID_H_KP  1.0f
#define PID_H_KI  0.1f
#define PID_H_KD  0.05f

// 垂直PID
#define PID_V_KP  1.0f
#define PID_V_KI  0.1f
#define PID_V_KD  0.05f
```

## 故障排除

### 通信问题
1. 检查串口连接和波特率
2. 确认协议头配置正确
3. 检查设备权限

### 舵机问题
1. 检查控制板电源
2. 确认舵机ID配置
3. 测试舵机连接

### 图像处理问题
1. 检查摄像头连接
2. 调整激光功率
3. 优化环境光照


---

**版本**: v2.1 | **开发环境**: Keil MDK + MaixPy | **更新**: 2025-07-07
