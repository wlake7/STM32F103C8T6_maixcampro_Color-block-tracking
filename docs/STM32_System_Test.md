# STM32激光追踪系统测试文档

## 测试概述

本文档描述了STM32端激光追踪系统的测试方案，包括单元测试、集成测试和系统测试。

## 系统架构

```
MaixCam (Python)  <--UART--> STM32F103C8T6 <--UART--> 舵机系统
     |                           |
图像处理模块                   控制模块
- 目标检测                    - 通信协议
- 激光检测                    - PID控制
- 坐标计算                    - 舵机控制
- 数据传输                    - 状态管理
```

## 模块测试

### 1. 通信协议模块测试

#### 1.1 数据包格式验证
```c
// 测试数据包构建
CommPacket_t packet;
uint8_t test_data[] = {0x01, 0x02, 0x03, 0x04};
bool result = Communication_SendPacket(CMD_TARGET_POSITION, test_data, 4);

// 预期结果: 
// 帧头: 0xAA 0x55
// 长度: 0x04
// 命令: 0x01
// 数据: 0x01 0x02 0x03 0x04
// 校验: 计算值
```

#### 1.2 校验和验证
```c
uint8_t data[] = {0x04, 0x01, 0x01, 0x02, 0x03, 0x04};
uint8_t checksum = Communication_CalculateChecksum(data, 6);
// 预期: checksum = ~(0x04+0x01+0x01+0x02+0x03+0x04) = ~0x0F = 0xF0
```

#### 1.3 数据解析测试
```c
// 模拟接收完整数据包
uint8_t rx_data[] = {0xAA, 0x55, 0x04, 0x01, 0x01, 0x02, 0x03, 0x04, 0xF0};
Communication_ProcessReceiveData(rx_data, 9);
// 验证回调函数是否正确调用
```

### 2. 舵机控制模块测试

#### 2.1 舵机命令发送测试
```c
// 测试位置控制命令
bool result = Servo_MoveToPosition(SERVO_ID_HORIZONTAL, 500, 1000);
// 预期发送: 55 55 02 07 01 F4 01 E8 03 [checksum]

// 测试停止命令
result = Servo_StopMove(SERVO_ID_VERTICAL);
// 预期发送: 55 55 01 03 0C [checksum]
```

#### 2.2 角度转换测试
```c
// 测试角度转换
float angle_deg = Servo_ConvertAngleToFloat(500);  // 应该返回120.0度
uint16_t angle_raw = Servo_ConvertFloatToAngle(120.0f);  // 应该返回500
```

#### 2.3 舵机状态管理测试
```c
ServoStatus_t* status = Servo_GetStatus(SERVO_ID_HORIZONTAL);
// 验证状态结构正确初始化
assert(status->id == SERVO_ID_HORIZONTAL);
assert(status->current_angle == SERVO_ANGLE_CENTER);
```

### 3. PID控制器模块测试

#### 3.1 PID参数设置测试
```c
// 测试参数设置
bool result = PID_SetParams(PID_TYPE_HORIZONTAL, 2.0f, 0.1f, 0.5f);
PIDParams_t* params = PID_GetParams(PID_TYPE_HORIZONTAL);
assert(params->kp == 2.0f);
assert(params->ki == 0.1f);
assert(params->kd == 0.5f);
```

#### 3.2 PID计算测试
```c
// 测试PID计算
PID_SetSetpoint(PID_TYPE_HORIZONTAL, 100.0f);
PID_Enable(PID_TYPE_HORIZONTAL, true);

float output1 = PID_Compute(PID_TYPE_HORIZONTAL, 90.0f);  // 误差=10
float output2 = PID_Compute(PID_TYPE_HORIZONTAL, 95.0f);  // 误差=5
// 验证输出随误差减小而减小
```

#### 3.3 输出限制测试
```c
PID_SetOutputLimits(PID_TYPE_HORIZONTAL, -100.0f, 100.0f);
PID_SetSetpoint(PID_TYPE_HORIZONTAL, 1000.0f);  // 设置很大的设定值
float output = PID_Compute(PID_TYPE_HORIZONTAL, 0.0f);
assert(output <= 100.0f);  // 输出应该被限制
```

## 集成测试

### 1. 通信-控制集成测试

#### 测试场景: MaixCam发送目标位置数据
```c
// 模拟MaixCam发送的数据包
uint8_t position_data[] = {
    0xAA, 0x55,           // 帧头
    0x10,                 // 数据长度
    0x01,                 // 目标位置命令
    // 目标位置数据 (x=320, y=240, confidence=95, timestamp=1000)
    0x40, 0x01,           // x = 320
    0xF0, 0x00,           // y = 240  
    0x5F, 0x00,           // confidence = 95
    0xE8, 0x03,           // timestamp = 1000
    // 激光位置数据 (x=300, y=250, confidence=90, timestamp=1001)
    0x2C, 0x01,           // x = 300
    0xFA, 0x00,           // y = 250
    0x5A, 0x00,           // confidence = 90
    0xE9, 0x03,           // timestamp = 1001
    0x00                  // 校验和(需要计算)
};

// 处理数据并验证PID响应
Communication_ProcessReceiveData(position_data, sizeof(position_data));
// 验证目标位置和激光位置是否正确解析
// 验证PID控制器是否产生正确输出
```

### 2. PID-舵机集成测试

#### 测试场景: PID输出驱动舵机运动
```c
// 设置追踪模式
g_system_state = SYSTEM_STATE_TRACKING;
g_target_position.x = 320;
g_target_position.y = 240;
g_laser_position.x = 300;
g_laser_position.y = 250;

// 执行追踪更新
System_UpdateTracking();

// 验证舵机是否接收到正确的位置命令
ServoStatus_t* h_servo = Servo_GetStatus(SERVO_ID_HORIZONTAL);
ServoStatus_t* v_servo = Servo_GetStatus(SERVO_ID_VERTICAL);
// 验证舵机目标角度是否根据PID输出调整
```

## 系统测试

### 1. 完整追踪流程测试

#### 测试步骤:
1. 系统初始化
2. 进入标定模式
3. 接收MaixCam数据
4. 切换到追踪模式
5. 执行闭环控制
6. 验证追踪精度

#### 预期结果:
- 系统正常初始化，所有模块就绪
- 舵机移动到中心位置完成标定
- 正确解析MaixCam发送的位置数据
- PID控制器产生合理的输出
- 舵机响应PID输出进行位置调整
- 激光点逐渐接近目标位置

### 2. 错误处理测试

#### 测试场景:
- 通信超时
- 校验和错误
- 舵机响应超时
- PID输出饱和

#### 预期行为:
- 系统进入错误状态
- LED指示错误
- 舵机停止运动
- 发送错误状态给MaixCam

### 3. 性能测试

#### 测试指标:
- 通信延迟: < 10ms
- 控制周期: 50Hz (20ms)
- 追踪精度: ±2像素
- 响应时间: < 100ms

## 调试工具

### 1. OLED显示调试信息
```c
// 显示系统状态
OLED_ShowString(1, 1, "State: TRACK");
// 显示位置信息
sprintf(buffer, "T:%d,%d", target_x, target_y);
OLED_ShowString(2, 1, buffer);
// 显示PID输出
sprintf(buffer, "O:%.1f,%.1f", h_output, v_output);
OLED_ShowString(3, 1, buffer);
```

### 2. 串口调试输出
```c
// 通过USART1发送调试信息到PC
printf("PID H: Kp=%.2f, Ki=%.2f, Kd=%.2f, Out=%.2f\r\n", 
       params->kp, params->ki, params->kd, output);
```

### 3. LED状态指示
```c
// 正常运行: LED常亮
// 追踪模式: LED闪烁
// 错误状态: LED快速闪烁
```

## 测试检查清单

### 基础功能测试
- [ ] 系统正常启动和初始化
- [ ] OLED显示正常
- [ ] 按键响应正常
- [ ] LED指示正常

### 通信模块测试
- [ ] 串口初始化成功
- [ ] 数据包发送正常
- [ ] 数据包接收和解析正常
- [ ] 校验和计算正确
- [ ] 错误处理正常

### 舵机控制测试
- [ ] 舵机初始化成功
- [ ] 位置控制命令发送正常
- [ ] 舵机响应正常
- [ ] 角度转换正确
- [ ] 状态查询正常

### PID控制测试
- [ ] PID参数设置正常
- [ ] PID计算正确
- [ ] 输出限制有效
- [ ] 积分饱和保护正常
- [ ] 微分滤波有效

### 系统集成测试
- [ ] 模块间通信正常
- [ ] 数据流传递正确
- [ ] 控制逻辑正确
- [ ] 错误处理完善
- [ ] 性能指标达标

## 已知问题和改进建议

### 当前限制:
1. 系统时钟使用简单计数器，需要实现真实的时钟
2. 部分超时检查功能未完全实现
3. 调试输出功能需要完善

### 改进建议:
1. 添加系统时钟管理模块
2. 实现更完善的错误恢复机制
3. 添加参数持久化存储
4. 优化PID参数自适应调节
5. 添加更多的性能监控指标

## 测试结论

STM32端激光追踪系统已实现完整的模块化架构，包括通信协议、舵机控制、PID控制和系统管理等核心功能。系统设计合理，代码结构清晰，具备良好的可测试性和可维护性。

通过系统的单元测试、集成测试和系统测试，可以验证各模块功能的正确性和整体系统的性能表现。
