# 激光追踪系统 (Laser Tracking System)

基于STM32F103C8T6和MaixCamPro的智能激光追踪系统，能够自动检测红色目标并控制绿色激光指向目标位置。

## 系统概述

本系统采用双端协同架构：
- **MaixCam端**: 负责图像处理、目标检测、激光检测和坐标计算
- **STM32端**: 负责舵机控制、PID调节和系统状态管理

## 主要特性

### 🎯 核心功能
- **实时目标检测**: 基于LAB颜色空间的红色目标检测
- **激光位置检测**: 绿色激光点精确定位
- **自动追踪控制**: PID闭环控制实现精确追踪
- **图像矫正**: 支持透视变换和四角标定
- **双轴控制**: 独立的水平和垂直舵机控制

### 🔧 技术特点
- **模块化设计**: 清晰的模块划分，便于维护和扩展
- **实时通信**: 115200波特率串口通信，低延迟数据传输
- **精确控制**: 可调PID参数，支持积分饱和保护和微分滤波
- **状态管理**: 完整的系统状态机和错误处理机制
- **可视化调试**: OLED实时显示系统状态和调试信息

## 硬件配置

### 主控制器
- **STM32F103C8T6**: 主控制器，负责舵机控制和系统管理
- **MaixCamPro**: 图像处理单元，负责目标检测和坐标计算

### 执行机构
- **Huaner LX-224舵机 x2**: 
  - 水平舵机 (ID=2): 控制激光水平方向
  - 垂直舵机 (ID=1): 控制激光垂直方向
- **绿色激光器**: 安装在舵机云台上

### 显示和交互
- **OLED显示屏**: 显示系统状态和调试信息
- **按键**: 系统模式切换
- **LED指示灯**: 状态指示和错误报警

## 软件架构

### MaixCam端模块
```
main.py              # 主程序入口
├── config.py        # 配置管理模块
├── laser_tracker.py # 激光追踪控制器
├── image_processor.py # 图像处理模块
└── communication.py # 通信协议模块
```

### STM32端模块
```
main.c               # 主控制逻辑
├── Communication.c/h # 串口通信协议
├── Servo.c/h        # 舵机控制模块
├── PID.c/h          # PID控制器模块
└── Hardware/        # 硬件驱动模块
    ├── OLED.c/h     # OLED显示驱动
    ├── LED.c/h      # LED控制驱动
    └── Key.c/h      # 按键检测驱动
```

## 通信协议

### 数据包格式
```
| 帧头 | 长度 | 命令 | 数据 | 校验和 |
|------|------|------|------|--------|
| 0xAA 0x55 | Length | Cmd | Data | Checksum |
```

### 主要命令
- `CMD_TARGET_POSITION (0x01)`: 目标位置数据
- `CMD_LASER_POSITION (0x02)`: 激光位置数据  
- `CMD_PID_PARAMS (0x03)`: PID参数配置
- `CMD_SYSTEM_STATUS (0x04)`: 系统状态信息
- `CMD_CALIBRATION (0x05)`: 标定数据
- `CMD_HEARTBEAT (0x06)`: 心跳包

## 快速开始

### 1. 硬件连接
```
MaixCam UART  <-->  STM32 USART1
Pin 8 (TX)    <-->  PA10 (RX)
Pin 10 (RX)   <-->  PA9 (TX)
GND           <-->  GND

STM32 USART2  <-->  舵机总线
PA2 (TX)      <-->  舵机信号线
PA3 (RX)      <-->  舵机信号线
```

### 2. 软件部署

#### MaixCam端
```bash
# 上传代码到MaixCam
scp -r maixcam/* root@192.168.x.x:/root/laser_tracker/

# 运行程序
python main.py
```

#### STM32端
```bash
# 使用Keil MDK编译并下载
# 或使用命令行工具
make all
make flash
```

### 3. 系统启动
1. 上电后STM32自动初始化，OLED显示系统状态
2. 启动MaixCam程序，建立通信连接
3. 按下按键切换到追踪模式
4. 放置红色目标物，系统开始自动追踪

## 配置参数

### 图像检测参数
```python
# 颜色阈值 (LAB色彩空间)
RED_TARGET_THRESHOLD = (30, 100, 15, 127, 15, 127)
GREEN_LASER_THRESHOLD = (30, 100, -64, -8, -32, 32)

# 检测参数
MIN_BLOB_AREA = 50
MAX_BLOB_COUNT = 10
```

### PID控制参数
```c
// 水平轴PID参数
#define DEFAULT_KP_HORIZONTAL  2.0f
#define DEFAULT_KI_HORIZONTAL  0.1f  
#define DEFAULT_KD_HORIZONTAL  0.5f

// 垂直轴PID参数
#define DEFAULT_KP_VERTICAL    2.5f
#define DEFAULT_KI_VERTICAL    0.15f
#define DEFAULT_KD_VERTICAL    0.6f
```

## 性能指标

- **追踪精度**: ±2像素
- **响应时间**: <100ms
- **控制频率**: 50Hz
- **通信延迟**: <10ms
- **角度分辨率**: 0.24度 (1000步对应240度)

## 系统状态

### 运行模式
- **INIT**: 系统初始化
- **CALIB**: 标定模式，舵机移动到中心位置
- **TRACK**: 追踪模式，自动追踪目标
- **MANUAL**: 手动控制模式
- **ERROR**: 错误状态

### 状态指示
- **OLED显示**: 实时显示系统状态、位置信息和PID输出
- **LED指示**: 正常运行(常亮)、追踪模式(闪烁)、错误状态(快闪)

## 故障排除

### 常见问题
1. **通信连接失败**: 检查串口连接和波特率设置
2. **舵机不响应**: 检查电源供应和ID配置
3. **检测不到目标**: 调整光照条件和颜色阈值
4. **追踪不稳定**: 优化PID参数和机械结构

详细的故障排除指南请参考 [System_Integration_Guide.md](docs/System_Integration_Guide.md)

## 📚 文档

### 📖 用户文档
- [📋 快速开始指南](docs/Quick_Start_Guide.md) - 5分钟快速上手指南
- [📘 用户使用手册](docs/User_Manual.md) - 完整的使用说明和操作指南
- [❓ 常见问题解答](docs/FAQ.md) - FAQ和故障排除指南

### 🔧 技术文档
- [🧪 STM32系统测试文档](docs/STM32_System_Test.md) - 详细的测试方案和检查清单
- [🔗 系统集成指南](docs/System_Integration_Guide.md) - 硬件连接和软件配置指南
- [📡 舵机通信协议](舵机通信协议/通信协议.md) - Huaner LX-224舵机协议详解

## 项目结构

```
激光追踪/
├── maixcam/                 # MaixCam端代码
│   ├── main.py             # 主程序
│   ├── config.py           # 配置模块
│   ├── laser_tracker.py    # 追踪控制器
│   ├── image_processor.py  # 图像处理
│   └── communication.py    # 通信模块
├── stm32/                  # STM32端代码
│   ├── User/main.c         # 主控制逻辑
│   └── Hardware/           # 硬件模块
│       ├── Communication.c/h
│       ├── Servo.c/h
│       └── PID.c/h
├── docs/                   # 文档目录
└── 舵机通信协议/           # 舵机协议文档
```

## 版本历史

### v1.0.0 (当前版本)
- ✅ 完整的双端系统架构
- ✅ 实时图像处理和目标检测
- ✅ 精确的舵机控制和PID调节
- ✅ 稳定的串口通信协议
- ✅ 完善的状态管理和错误处理
- ✅ 详细的测试和集成文档

## 未来规划

### 功能扩展
- [ ] 多目标追踪支持
- [ ] 运动预测算法
- [ ] 网络远程控制
- [ ] 参数自适应调节
- [ ] 数据记录和分析

### 性能优化
- [ ] 更高的追踪精度
- [ ] 更快的响应速度
- [ ] 更强的抗干扰能力
- [ ] 更好的用户界面

## 贡献指南

欢迎提交Issue和Pull Request来改进项目。请确保：
1. 代码符合项目的编码规范
2. 添加必要的测试用例
3. 更新相关文档

## 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件

## 联系方式

如有技术问题或建议，请通过以下方式联系：
- 提交 GitHub Issue
- 发送邮件至项目维护者

---

**注意**: 本项目仅供学习和研究使用，请遵守当地法律法规，注意激光安全。
