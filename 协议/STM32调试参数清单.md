# STM32端调试参数清单

## 🎯 快速调试指南

### 🔥 最关键的调试参数 (优先监控)

#### 1. 系统状态核心参数
- **System_GetTick()**: 系统时间计数 (验证Timer1工作)
- **g_system_initialized**: 系统初始化标志 (0/1)
- **communication_ok**: 通信状态 (true/false)

#### 2. 舵机控制核心参数
- **servo_h_pos**: 水平舵机位置 (0-1000)
- **servo_v_pos**: 垂直舵机位置 (0-1000)
- **servo_command_count**: 舵机命令发送计数

#### 3. 图像数据核心参数
- **target.x, target.y**: 红色目标位置 (像素坐标)
- **target.valid**: 目标数据有效性 (0/1)
- **laser.x, laser.y**: 绿色激光位置 (像素坐标)
- **laser.valid**: 激光数据有效性 (0/1)

#### 4. PID控制核心参数
- **error_x, error_y**: 位置误差 (像素)
- **pid_output_h, pid_output_v**: PID输出值
- **h_increment, v_increment**: 舵机位置增量

#### 5. 通信统计核心参数
- **packets_received**: 接收包计数
- **packets_error**: 错误包计数
- **last_receive_time**: 最后接收时间

#### 6. 控制周期核心参数
- **dt (时间差)**: 验证控制周期的稳定性

## 🎛️ 详细参数配置

### ⏰ 时钟与定时器
```c
// 系统时钟配置
SystemCoreClock = 72000000;  // 72MHz

// Timer1配置 (Timer.c)
TIM_Period = 1000 - 1;       // 1ms中断周期
TIM_Prescaler = 72 - 1;      // 预分频器
NVIC_IRQChannelPreemptionPriority = 1;  // 中断优先级

// SysTick配置 (main.c)
SysTick_Config(SystemCoreClock / 1000);  // 1ms中断
```

### 🎯 PID控制参数 (已改为宏定义便于调试)

#### PID参数宏定义
```c
// LaserTracker.h 第58-65行 - 便于调试
#define PID_KP_H            2.0f        // 水平轴比例增益
#define PID_KI_H            0.01f       // 水平轴积分增益
#define PID_KD_H            0.1f        // 水平轴微分增益
#define PID_KP_V            2.0f        // 垂直轴比例增益
#define PID_KI_V            0.01f       // 垂直轴积分增益
#define PID_KD_V            0.1f        // 垂直轴微分增益
#define PID_MAX_OUTPUT      50.0f       // PID输出限幅
#define PID_MAX_INTEGRAL    25.0f       // PID积分限幅
```

#### 控制算法参数宏定义
```c
// LaserTracker.h 第67-69行 - 便于调试
#define DEADZONE_PIXELS     3.0f        // 死区像素数，避免小误差抖动
#define MAX_SERVO_INCREMENT 20.0f       // 舵机最大单次位置增量
#define SERVO_MOVE_TIME     50          // 舵机移动时间(ms)
```

#### 调试开关宏定义
```c
// LaserTracker.h 第84-86行 - 便于调试
#define ENABLE_PID_DEBUG    1           // 启用PID调试输出
#define ENABLE_OLED_DEBUG   1           // 启用OLED调试显示
#define ENABLE_SAFETY_CHECK 1           // 启用安全检查
```

#### PID控制逻辑 (修正后)
- **目标位置**: 摄像头识别的红色色块坐标 (target.x, target.y)
- **当前位置**: 摄像头识别的绿色激光坐标 (laser.x, laser.y)
- **PID计算**: `PID_Calculate(目标位置, 激光位置, dt)`，计算中已包含时间差 `dt`，使积分和微分项更精确。
- **控制输出**: PID输出 → 舵机角度增量

### 🎮 舵机参数
```c
// 舵机ID (ServoBoard.h)
SERVO_ID_VERTICAL = 1;     // 垂直舵机
SERVO_ID_HORIZONTAL = 2;   // 水平舵机

// 舵机位置范围 (ServoBoard.h)
SERVO_POSITION_MIN = 0;    // 最小位置
SERVO_POSITION_MAX = 1000; // 最大位置
SERVO_POSITION_CENTER = 500; // 中心位置

// 舵机运动时间
激光追踪模式: 50ms    // 快速响应
测试模式: 200ms       // 平滑运动
回中心: 1000ms        // 缓慢稳定
```

### 📡 通信参数
```c
// 摄像头通信 USART1 (CameraComm.h)
CAMERA_UART_BAUDRATE = 115200;
CAMERA_UART_TX_PIN = GPIO_Pin_9;   // PA9
CAMERA_UART_RX_PIN = GPIO_Pin_10;  // PA10
CAMERA_COMM_TIMEOUT_MS = 10000;    // 10秒超时

// 舵机通信 USART2 (ServoBoard.h)
SERVO_UART_BAUDRATE = 9600;
SERVO_UART_TX_PIN = GPIO_Pin_2;    // PA2
SERVO_UART_RX_PIN = GPIO_Pin_3;    // PA3
SERVO_COMM_TIMEOUT_MS = 1000;      // 1秒超时

// 协议帧头
摄像头协议: [0xAA, 0x55]
舵机协议: [0x55, 0x55]
```

### 🖥️ OLED显示参数
```c
// OLED I2C配置
OLED_ADDRESS = 0x78;  // I2C从机地址
显示分辨率: 128x64
字体: 8x16点阵
显示行数: 4行
每行字符数: 16个字符

// 显示更新频率
激光追踪模式: 每3次控制循环更新一次
通信调试模式: 每200ms更新一次
舵机调试模式: 实时更新
```

### 🔧 图像处理参数
```c
// 图像坐标系 (LaserTracker.h)
IMAGE_WIDTH = 640;
IMAGE_HEIGHT = 480;
IMAGE_CENTER_X = 320;
IMAGE_CENTER_Y = 240;

// 坐标转换公式
舵机位置 = (像素坐标 * 1000) / 图像尺寸
PID输出偏移 = PID输出 * 0.5f
```

## 🎚️ 调试模式切换

### 宏开关配置 (main.c)
```c
#define MODE_SERVO_TEST     1   // 舵机测试模式
#define MODE_LASER_TRACK    2   // 激光追踪模式
#define MODE_COMM_DEBUG     3   // 通信调试模式
#define MODE_SERVO_DEBUG    4   // 舵机专项调试模式
#define MODE_CONTROL_TEST   5   // 控制方向测试模式

// 当前运行模式
#define CURRENT_MODE       MODE_LASER_TRACK
```

### 各模式主循环频率
- **MODE_LASER_TRACK**: 50Hz (20ms周期)
- **MODE_COMM_DEBUG**: 10Hz (100ms周期)
- **MODE_SERVO_TEST**: 0.5Hz (2000ms周期)
- **MODE_SERVO_DEBUG**: 1Hz (1000ms周期)
- **MODE_CONTROL_TEST**: 0.5Hz (2000ms周期)

## 📊 OLED显示内容对照表

### 激光追踪模式显示
```
行1: SYS:123456      // 系统时间(ms)
行2: T:320,240 L:315,235  // 目标和激光位置
行3: E:+05,-05 I:+2,-1    // 误差和增量
行4: Servo:502,498        // 舵机位置
```

### 通信调试模式显示
```
行1: COMM: OK / TIMEOUT   // 通信状态
行2: RX:0123 ERR:005      // 接收包数和错误包数
行3: T:320,240 S:500      // 目标位置和舵机H位置
行4: L:315,235 S:498      // 激光位置和舵机V位置
```

### 舵机调试模式显示
```
行1: H:500 V:500          // 舵机位置
行2: Step:0 Cnt:0         // 测试步骤和计数
行3: Pos:CENTER           // 位置描述
行4: Time:123456          // 系统时间
```

## ⚡ 性能监控指标

### 关键性能参数
- **控制频率**: 50Hz (激光追踪模式)
- **通信延迟**: <20ms (目标值)
- **响应时间**: <100ms (从接收到动作)
- **追踪精度**: ±5像素 (目标值)

### 统计计数器
- **g_system_tick_ms**: 系统运行时间
- **servo_command_count**: 舵机命令总数
- **packets_sent**: 发送包总数
- **packets_received**: 接收包总数
- **packets_error**: 错误包总数
- **timeouts**: 超时次数

## 🔍 故障诊断检查点

### 1. 系统时间检查
- **System_GetTick()** 是否正常递增
- **Timer1中断** 是否正常工作

### 2. 通信状态检查
- **communication_ok** 是否为true
- **packets_received** 是否递增
- **packets_error** 比例是否过高

### 3. 数据有效性检查
- **target.valid** 和 **laser.valid** 是否为1
- **坐标值** 是否在合理范围内 (0-640, 0-480)

### 4. 控制响应检查
- **PID输出** 是否合理 (不超过限幅值)
- **舵机位置** 是否在0-1000范围内
- **位置增量** 是否不超过MAX_INCREMENT
- **`dt`值** 是否合理（不应为零或过大），验证控制周期稳定性

### 5. 硬件连接检查
- **LED心跳** 是否正常闪烁
- **OLED显示** 是否正常更新
- **舵机响应** 是否与命令一致
