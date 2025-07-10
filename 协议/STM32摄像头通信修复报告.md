# STM32与摄像头通信修复报告

## 🔍 **问题诊断结果**

### 发现的主要问题

#### 1. **串口配置不匹配** ⚠️
- **STM32端**: 使用USART1 (PA9-TX, PA10-RX)
- **MaixCam端**: 之前使用串口2 (/dev/ttyS2, A28-TX, A29-RX)
- **问题**: 两端串口不对应，无法通信

#### 2. **协议格式不匹配** ⚠️
- **STM32端期望**: CMD_TARGET_POSITION包含12字节数据
- **MaixCam端发送**: 分别发送CMD_TARGET_POSITION(4字节)和CMD_LASER_POSITION(4字节)
- **问题**: STM32端只处理CMD_TARGET_POSITION，忽略CMD_LASER_POSITION

#### 3. **数据处理逻辑缺陷** ⚠️
- **问题**: STM32端没有正确处理分离的目标和激光位置数据
- **影响**: 即使接收到数据也无法正确解析

## 🔧 **修复方案**

### 1. **统一串口配置**
#### MaixCam端修改
```python
# config.py
self.uart_port = "/dev/ttyS1"  # 改为串口1

# main.py
pinmap.set_pin_function("A18", "UART1_RX")  # 串口1引脚映射
pinmap.set_pin_function("A19", "UART1_TX")
```

#### 硬件连接
```
MaixCam A19(TX) → STM32 PA10(RX)
MaixCam A18(RX) → STM32 PA9(TX)
共地连接
```

### 2. **修复协议解析**
#### STM32端CameraComm.c修改
```c
// 新增CMD_LASER_POSITION处理
case CMD_LASER_POSITION:
    if (data_len >= 4) {
        // 解析激光位置数据
        g_camera_comm_system.latest_data.laser.x = (int16_t)(data[0] | (data[1] << 8));
        g_camera_comm_system.latest_data.laser.y = (int16_t)(data[2] | (data[3] << 8));
        // ...
    }
    break;

// 修改CMD_TARGET_POSITION处理
case CMD_TARGET_POSITION:
    if (data_len >= 4) {  // 改为4字节
        // 只处理目标位置数据
        // ...
    }
    break;
```

### 3. **增强通信调试**
#### STM32端OLED实时显示
```
行1: COMM: OK/TIMEOUT
行2: RX:XXXX ERR:XXX
行3: T:XXX,XXX S:XXX
行4: L:XXX,XXX S:XXX
```

## 📊 **修复后的通信流程**

### 数据流向
```
MaixCam → 串口1(/dev/ttyS1) → STM32 USART1 → CameraComm_IRQHandler → 
CameraComm_ParsePacket → LaserTracker_UpdatePosition → 舵机控制
```

### 协议格式
```
目标位置: [0xAA, 0x55, 0x04, 0x01, target_x_low, target_x_high, target_y_low, target_y_high]
激光位置: [0xAA, 0x55, 0x04, 0x02, laser_x_low, laser_x_high, laser_y_low, laser_y_high]
```

### 数据处理逻辑
1. **接收目标位置** → 更新target数据 → 调用LaserTracker_UpdateTargetPosition
2. **接收激光位置** → 更新laser数据 → 调用LaserTracker_UpdateLaserPosition
3. **两者都有效** → 设置both_detected=true → 触发PID控制

## 🧪 **测试验证**

### 第一步：MaixCam端测试
```bash
cd maixcam
# 确认run_config.py中 RUN_MODE = 2
python main.py
```

**预期输出**:
```
MaixCam激光追踪系统
当前运行模式: 2 - 通信诊断模式
启动通信诊断模式...
✓ UART初始化成功: /dev/ttyS1@115200
开始发送测试数据...
第1组: 目标(270,210) 激光(250,195)
```

### 第二步：STM32端验证
**编译设置**: `#define CURRENT_MODE MODE_COMM_DEBUG`

**OLED预期显示**:
```
COMM: OK
RX:0008 ERR:000
T:270,210 S:421
L:250,195 S:390
```

### 第三步：硬件响应验证
- **舵机应该移动**：根据目标位置计算的舵机位置
- **LED闪烁**：每次接收到有效数据时闪烁
- **OLED更新**：实时显示接收到的位置数据

## 🔍 **故障排除**

### 如果OLED显示"COMM: TIMEOUT"
1. **检查硬件连接**：
   - MaixCam A19 → STM32 PA10
   - MaixCam A18 → STM32 PA9
   - 共地连接

2. **检查波特率**：双方都是115200bps

3. **检查引脚映射**：MaixCam端A18/A19是否正确映射到UART1

### 如果OLED显示"RX:0000"
1. **检查MaixCam程序**：是否正常发送数据
2. **检查STM32中断**：USART1中断是否正常工作
3. **检查数据包格式**：帧头0xAA 0x55是否正确

### 如果接收数据但ERR计数增加
1. **检查数据包完整性**：长度、校验和
2. **检查协议格式**：命令字节是否正确
3. **检查数据解析**：字节序是否正确

## 📈 **预期改善效果**

### 通信质量
- **数据包接收率**: 应达到95%以上
- **解析错误率**: 应低于1%
- **通信延迟**: 应低于50ms

### 系统响应
- **舵机响应**: 应能跟随目标位置变化
- **PID控制**: 应能正常计算误差和输出
- **追踪精度**: 应有明显改善

## 🎯 **下一步计划**

1. **验证通信修复**: 确认数据正常收发
2. **PID参数调优**: 根据实际响应调整参数
3. **性能优化**: 提高通信频率和稳定性
4. **完整系统测试**: 激光追踪模式端到端测试

---

**修复状态**: ✅ 已完成，等待测试验证
**关键改进**: 串口配置统一、协议解析修复、调试功能增强
