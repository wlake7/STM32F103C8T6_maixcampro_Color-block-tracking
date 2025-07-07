# 激光追踪系统集成指南

## 系统概述

本激光追踪系统采用三层架构：MaixCam图像处理端、STM32主控制端、控制板舵机控制端，通过串口通信实现协同工作。

### 系统架构图
```
┌─────────────┐    图像处理    ┌─────────────┐    主控制    ┌─────────────┐    舵机控制    ┌─────────────┐
│  MaixCam    │ ──────────→   │   STM32     │ ──────────→ │   控制板     │ ──────────→   │  串联舵机    │
│  Pro        │ ←────────────  │  F103C8T6   │ ←────────── │             │ ←────────────  │             │
└─────────────┘    位置数据    └─────────────┘    状态反馈  └─────────────┘    位置反馈    └─────────────┘
```

## 硬件连接

### 1. MaixCam与STM32连接
```
MaixCam UART  <-->  STM32 USART1
Pin 8 (TX)    <-->  PA10 (RX)    [115200 baud]
Pin 10 (RX)   <-->  PA9 (TX)     [115200 baud]
GND           <-->  GND
```

### 2. STM32与控制板连接
```
STM32 USART2  <-->  控制板串口
PA2 (TX)      <-->  控制板 RX     [9600 baud]
PA3 (RX)      <-->  控制板 TX     [9600 baud]
GND           <-->  控制板 GND
```

### 3. 控制板与舵机连接
```
控制板舵机总线  <-->  串联舵机
舵机总线       <-->  舵机1 → 舵机2 (串联)
电源 (6-12V)   <-->  舵机供电
```

### 4. 舵机ID配置
- 垂直舵机: ID = 1
- 水平舵机: ID = 2

## 软件配置

### 1. MaixCam端配置

#### 启动主程序
```bash
cd /path/to/project
python main.py
```

#### 配置参数 (config.py)
```python
# 相机参数
CAMERA_WIDTH = 640
CAMERA_HEIGHT = 480
CAMERA_FPS = 30

# 检测参数
RED_TARGET_THRESHOLD = (30, 100, 15, 127, 15, 127)  # LAB颜色空间
GREEN_LASER_THRESHOLD = (30, 100, -64, -8, -32, 32)
MIN_BLOB_AREA = 50

# 通信参数
UART_PORT = "/dev/ttyS0"
UART_BAUDRATE = 115200

# PID参数
PID_KP_H = 2.0
PID_KI_H = 0.1
PID_KD_H = 0.5
PID_KP_V = 2.5
PID_KI_V = 0.15
PID_KD_V = 0.6
```

### 2. STM32端配置

#### 编译和下载
```bash
# 使用Keil MDK编译项目
# 或使用命令行工具
arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2 -g -Wall -ffunction-sections -fdata-sections -I. -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c main.c
```

#### 系统参数
```c
// 通信参数
#define SYSTEM_BAUDRATE             115200      // MaixCam通信波特率
#define CONTROL_BOARD_BAUDRATE      9600        // 控制板通信波特率
#define SYSTEM_LOOP_FREQUENCY       50          // 50Hz控制频率
#define HEARTBEAT_INTERVAL          1000        // 1秒心跳间隔

// PID默认参数
#define DEFAULT_KP_HORIZONTAL       2.0f
#define DEFAULT_KI_HORIZONTAL       0.1f
#define DEFAULT_KD_HORIZONTAL       0.5f
#define DEFAULT_KP_VERTICAL         2.5f
#define DEFAULT_KI_VERTICAL         0.15f
#define DEFAULT_KD_VERTICAL         0.6f
```

## 系统启动流程

### 1. 硬件检查
- [ ] 确认所有硬件连接正确
- [ ] 检查电源供应(控制板6-12V电源)
- [ ] 验证串口连接(MaixCam-STM32, STM32-控制板)
- [ ] 确认舵机串联连接正确

### 2. STM32端启动
1. 上电后系统自动初始化
2. OLED显示"Laser Tracker Initializing..."
3. 初始化通信、控制板、PID模块
4. 控制板通信建立后显示"CtrlBoard OK"
5. 舵机移动到中心位置(标定状态)
6. OLED显示"State: CALIB"

### 3. MaixCam端启动
1. 运行主程序 `python main.py`
2. 初始化相机和图像处理模块
3. 建立与STM32的串口连接
4. 开始发送心跳包

### 4. 系统标定
1. 按下STM32的按键切换到追踪模式
2. MaixCam检测绿色激光点位置
3. 进行四角标定(可选)
4. 系统进入正常追踪状态

## 操作指南

### 1. 正常追踪操作

#### 步骤:
1. 确保红色目标物在相机视野内
2. 系统自动检测目标位置
3. PID控制器计算舵机调整量
4. 舵机驱动激光指向目标
5. 实时显示追踪状态

#### 状态指示:
- OLED显示: "State: TRACK"
- 目标位置: "T:320,240"
- 激光位置: "L:315,245"
- PID输出: "O:2.5,-1.2"

### 2. 手动控制模式

#### 进入方式:
- 在追踪模式下按下按键
- 系统切换到"State: MANUAL"

#### 功能:
- 禁用自动追踪
- 可通过MaixCam发送手动控制命令
- 用于调试和测试

### 3. 参数调节

#### PID参数在线调节:
```python
# MaixCam端发送PID参数
pid_params = PIDParams_t()
pid_params.kp_h = int(2.5 * 100)  # 乘以100发送
pid_params.ki_h = int(0.2 * 100)
pid_params.kd_h = int(0.8 * 100)
# ... 设置垂直参数
communication.send_pid_params(pid_params)
```

#### 检测阈值调节:
```python
# 在config.py中调整颜色阈值
config.RED_TARGET_THRESHOLD = (25, 100, 10, 127, 10, 127)
config.update_detection_params()
```

## 故障排除

### 1. 通信问题

#### 症状: 无法建立通信连接
**检查项目:**
- [ ] 串口线连接是否正确
- [ ] 波特率设置是否一致(115200)
- [ ] 串口设备路径是否正确
- [ ] 是否有其他程序占用串口

#### 解决方案:
```bash
# 检查串口设备
ls /dev/ttyS* /dev/ttyUSB*

# 测试串口通信
echo "test" > /dev/ttyS1
```

### 2. 舵机控制问题

#### 症状: 舵机不响应或运动异常
**检查项目:**
- [ ] 舵机电源是否正常(5V)
- [ ] 舵机ID设置是否正确
- [ ] 舵机总线连接是否正确
- [ ] 舵机是否损坏

#### 解决方案:
```c
// 测试舵机基本功能
Servo_MoveToPosition(SERVO_ID_HORIZONTAL, SERVO_ANGLE_CENTER, 1000);
Servo_ReadPosition(SERVO_ID_HORIZONTAL);
```

### 3. 图像检测问题

#### 症状: 无法检测到目标或激光
**检查项目:**
- [ ] 光照条件是否合适
- [ ] 目标颜色是否符合阈值
- [ ] 相机焦距是否调整好
- [ ] 检测参数是否合理

#### 解决方案:
```python
# 调试检测参数
image_processor.debug_mode = True
image_processor.show_detection_result = True
```

### 4. PID控制问题

#### 症状: 追踪不稳定或振荡
**检查项目:**
- [ ] PID参数是否合理
- [ ] 控制频率是否足够
- [ ] 机械系统是否有间隙
- [ ] 负载是否过重

#### 解决方案:
```c
// 调整PID参数
PID_SetParams(PID_TYPE_HORIZONTAL, 1.5f, 0.05f, 0.3f);  // 降低增益
PID_SetDeadband(PID_TYPE_HORIZONTAL, 5.0f);             // 增加死区
```

## 性能优化

### 1. 追踪精度优化
- 调整相机分辨率和帧率
- 优化图像处理算法
- 精确标定相机参数
- 调节PID控制参数

### 2. 响应速度优化
- 提高控制循环频率
- 减少通信延迟
- 优化舵机响应时间
- 使用预测控制算法

### 3. 稳定性优化
- 添加滤波算法
- 实现自适应控制
- 增强错误处理机制
- 优化机械结构

## 维护建议

### 1. 定期检查
- 检查硬件连接
- 清洁相机镜头
- 检查舵机磨损
- 更新软件版本

### 2. 参数备份
- 保存调试好的参数
- 记录系统配置
- 备份标定数据
- 建立参数版本管理

### 3. 性能监控
- 记录追踪精度数据
- 监控系统响应时间
- 分析错误日志
- 评估系统稳定性

## 扩展功能

### 1. 多目标追踪
- 实现目标识别和分类
- 支持多个激光器控制
- 添加目标优先级管理

### 2. 智能预测
- 实现目标运动预测
- 添加卡尔曼滤波
- 优化追踪算法

### 3. 远程监控
- 添加网络通信功能
- 实现远程参数调节
- 支持数据记录和分析

## 技术支持

如遇到技术问题，请提供以下信息:
1. 硬件配置和连接方式
2. 软件版本和配置参数
3. 错误现象和日志信息
4. 测试环境和条件

联系方式: [技术支持邮箱或论坛]
