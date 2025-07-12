# 激光追踪系统 (Laser Tracking System)

## 项目概述
本项目是一个基于 MaixCam 视觉处理和 STM32F103C8T6标准库开发的运动控制的激光追踪系统。它能够实时识别视野中的色块，并控制舵机云台上的激光笔精确地指向该色块的中心。如果觉得好用不忘给个stars

## 核心功能
*   **双核异构架构**: 使用 MaixCam (K210) 进行复杂的图像处理，STM32F103C8T6 负责精确的实时运动控制，各司其职。
*   **颜色检测**: 基于 LAB 色彩空间进行颜色识别，相比 RGB 色彩空间，能更有效地减少光照变化带来的影响。
*   **PID控制**: 采用精确的增量式PID闭环控制算法，确保舵机云台能够快速、平稳、准确地追踪目标。
*   **模块化代码**: Python (MaixCam) 和 C (STM32) 代码均采用模块化设计，结构清晰，易于维护和扩展。
*   **实时调试**: 通过 OLED 显示屏实时输出目标坐标、PID参数等关键调试信息。

## 硬件组成
*   主控芯片: MaixCam Pro 
*   运动控制芯片: STM32F103C8T6
*   执行机构: 双轴舵机云台
*   指示器: 绿色激光笔
*   显示模块: 0.96寸 OLED 显示屏

## 软件架构
系统软件分为 `maixcam` 和 `stm32` 两部分。

### MaixCam端 (Python)
*   [`main.py`](maixcam/project/main.py): 主程序入口，负责初始化、任务调度和主循环。
*   [`image_processor.py`](maixcam/project/image_processor.py): 核心图像处理模块，负责颜色识别、目标查找和坐标计算。
*   [`communication.py`](maixcam/project/communication.py): 与STM32进行串口通信的模块。
*   [`config.py`](maixcam/project/config.py): 存放图像处理阈值、串口配置等参数。

### STM32端 (C)
*   [`main.c`](stm32/User/main.c): 主程序入口，负责硬件初始化和主循环。
*   [`LaserTracker.c`](stm32/Hardware/LaserTracker.c): 激光追踪核心逻辑，包含PID算法实现。
*   [`CameraComm.c`](stm32/Hardware/CameraComm.c): 负责接收和解析来自MaixCam的串口数据。
*   [`ServoControl.c`](stm32/Hardware/ServoControl.c): 舵机控制底层驱动。
*   [`OLED.c`](stm32/Hardware/OLED.c): OLED显示驱动及UI界面。

## 如何开始
1.  根据硬件连接图正确连接所有硬件模块。
2.  使用 Keil 5 打开 [`stm32/Project.uvprojx`](stm32/Project.uvprojx) 工程，编译并烧录固件到 STM32 开发板。
3.  将 `maixcam/project` 文件夹下的所有文件拷贝到 MaixCam 的存储卡中，并运行 [`maixcam/project/main.py`](maixcam/project/main.py)。

## 通信协议
MaixCam 通过串口向 STM32 发送目标坐标信息。协议格式为帧头+数据+帧尾的简单定长格式，例如：`0xA5 [X_High] [X_Low] [Y_High] [Y_Low] 0x5A`。

## 配置说明
*   MaixCam 的颜色阈值、ROI等参数可在 [`maixcam/project/config.py`](maixcam/project/config.py) 中修改。
*   STM32 的 PID 参数 (Kp, Ki, Kd) 等可在 [`stm32/Hardware/LaserTracker.h`](stm32/Hardware/LaserTracker.h) 中进行调整。
