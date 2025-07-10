# STM32 OLED调试指南 - 舵机不动问题诊断

## 🎯 调试目标
通过OLED实时显示系统状态，诊断舵机不动的具体原因

## 📺 OLED显示内容

### 系统启动显示
```
STM32 Laser Track
Init Complete
Mode: SERVO_DEBUG
```

## 🔧 调试模式说明

### MODE_SERVO_DEBUG (当前模式)
**专门用于诊断舵机不动问题**

#### 显示内容
```
行1: SERVO DEBUG MODE
行2: Test: CENTER/LEFT-UP/RIGHT-UP等
行3: Step: XX (当前测试步骤)
行4: Count: XXXX (循环计数)
```

#### 测试序列
1. **Step 0**: CENTER (500,500) - 测试中心位置
2. **Step 1**: LEFT-UP (200,200) - 测试左上角
3. **Step 2**: RIGHT-UP (800,200) - 测试右上角
4. **Step 3**: RIGHT-DN (800,800) - 测试右下角
5. **Step 4**: LEFT-DN (200,800) - 测试左下角
6. **Step 5**: H-SCAN - 水平扫描
7. **Step 6**: V-SCAN - 垂直扫描

#### 舵机命令发送显示
当发送舵机命令时，OLED会显示：
```
行1: SERVO CMD SENT
行2: H:XXXX V:XXXX
行3: Time:XXXX ms
行4: Count:XXXXX
```

### MODE_COMM_DEBUG
**用于测试MaixCam通信**

#### 显示内容
```
行1: COMM DEBUG READY
行2: Data received!/Waiting MaixCam
行3: RX:XXXX S:XXX,XXX
行4: T:XXX,XXX L:XXX,XXX
```

### MODE_LASER_TRACK
**完整激光追踪模式**

#### 初始化显示
```
行1: LASER TRACK MODE
行2: PID: Kp=8.0
行3: Ki=0.1 Kd=0.5
行4: Ready to track
```

#### 运行时显示
```
行1: LASER TRACK MODE
行2: T:XXX,XXX L:XXX,XXX
行3: PID:±XXX,±XXX
行4: Servo:XXX,XXX
```

## 🔍 诊断步骤

### 第一步：观察OLED启动信息
1. **检查项目**：OLED是否正常显示启动信息
2. **预期显示**：
   ```
   STM32 Laser Track
   Init Complete
   Mode: SERVO_DEBUG
   ```
3. **问题排查**：
   - 如果OLED无显示：检查OLED硬件连接
   - 如果显示异常：检查OLED初始化代码

### 第二步：观察舵机调试模式
1. **检查项目**：OLED是否显示测试步骤
2. **预期显示**：
   ```
   SERVO DEBUG MODE
   Test: CENTER
   Step: 0
   Count: 1
   ```
3. **观察要点**：
   - Count数字是否递增（确认程序运行）
   - Step是否按序列变化（确认测试流程）
   - Test描述是否对应当前测试

### 第三步：观察舵机命令发送
1. **检查项目**：是否显示舵机命令发送信息
2. **预期显示**：
   ```
   SERVO CMD SENT
   H:0500 V:0500
   Time:1000 ms
   Count:00001
   ```
3. **关键诊断点**：
   - **如果看到此显示**：说明STM32正在发送舵机命令
   - **如果看不到此显示**：说明舵机命令发送有问题

### 第四步：观察舵机物理响应
1. **检查项目**：舵机是否按OLED显示的命令移动
2. **对比分析**：
   - OLED显示发送了命令 + 舵机不动 = 舵机控制板或舵机硬件问题
   - OLED不显示命令发送 = STM32软件问题

## 🚨 问题诊断矩阵

| OLED启动显示 | 舵机命令显示 | 舵机物理响应 | 问题定位 |
|------------|------------|------------|---------|
| ✅ 正常 | ✅ 显示发送 | ❌ 不动 | 舵机控制板/舵机硬件问题 |
| ✅ 正常 | ❌ 不显示 | ❌ 不动 | STM32软件/ServoBoard模块问题 |
| ❌ 异常 | - | - | OLED硬件/STM32基础问题 |
| ✅ 正常 | ✅ 显示发送 | ✅ 正常动 | 系统正常，问题在其他模式 |

## 🔧 进一步诊断

### 如果舵机命令正常发送但舵机不动
1. **检查舵机控制板连接**：
   - STM32 PA2(TX) → 舵机控制板RX
   - STM32 PA3(RX) → 舵机控制板TX
   - 波特率：9600bps

2. **检查舵机控制板电源**：
   - 舵机控制板是否上电
   - 电源电压是否符合要求(6-8.4V)

3. **检查舵机连接**：
   - 舵机是否正确连接到控制板
   - 舵机ID设置是否正确(水平:2, 垂直:1)

### 如果舵机命令不发送
1. **检查ServoBoard模块**：
   - USART2初始化是否正确
   - 数据包构造是否正确

2. **检查调用链**：
   - ServoDebug_Process → ServoBoard_MoveHV → ServoBoard_SendPacket

## 📊 预期结果

### 正常情况下的OLED显示序列
```
启动: STM32 Laser Track → Init Complete → Mode: SERVO_DEBUG
运行: SERVO DEBUG MODE → Test: CENTER → SERVO CMD SENT → H:0500 V:0500
循环: Step递增 → Count递增 → 不同测试位置 → 舵机响应移动
```

### 异常情况的诊断
- **只有启动显示，无测试显示**：主循环问题
- **有测试显示，无命令发送显示**：ServoBoard模块问题
- **有命令发送显示，舵机不动**：硬件连接问题

## 🎯 下一步行动

根据OLED显示的诊断结果：
1. **确认问题定位**：软件问题 vs 硬件问题
2. **针对性解决**：修复代码 vs 检查硬件连接
3. **验证修复效果**：重新测试并观察OLED显示
