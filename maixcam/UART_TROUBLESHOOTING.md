# MaixCam串口连接故障排除指南

## 🚨 问题现象
```
目标位置: (598, 455), 激光位置: (258, 406), 偏移: {...}
串口未连接，无法发送数据。
```

## 🔍 问题诊断

### 1. 快速诊断
```bash
# 在MaixCam上运行
cd /root/laser_tracker
python quick_fix.py
```

### 2. 详细诊断
```bash
# 在MaixCam上运行
python test_uart.py
```

## 🛠️ 解决方案

### 方案1: 检查硬件连接
```
MaixCam端:
- Pin8 (TX) → STM32 PA10 (RX)
- Pin10 (RX) ← STM32 PA9 (TX)  
- GND → GND

STM32端:
- 确保USART1正常初始化
- 波特率设置为115200
- 确保显示"CtrlBoard OK"
```

### 方案2: 检查串口设备
```bash
# 查看可用串口
ls -la /dev/tty*

# 常见设备:
# /dev/ttyS0  - 主串口
# /dev/ttyS1  - 辅助串口
# /dev/ttyUSB0 - USB转串口
```

### 方案3: 修复权限
```bash
# 修复串口权限
sudo chmod 666 /dev/ttyS0
sudo chmod 666 /dev/ttyS1

# 或者添加用户到dialout组
sudo usermod -a -G dialout $USER
```

### 方案4: 检查进程占用
```bash
# 查看串口占用
lsof | grep tty
ps aux | grep uart

# 如果有占用，杀死进程
sudo kill -9 <PID>
```

### 方案5: 手动测试串口
```python
# 在MaixCam Python终端中测试
from maix import uart
test_uart = uart.UART("/dev/ttyS0", 115200, 8, 0, 1, timeout=0.1)
test_uart.write(b"TEST")
test_uart.close()
```

## 🔧 配置调整

### 修改串口设备
编辑 `config.py`:
```python
# 尝试不同的串口设备
self.uart_port = "/dev/ttyS0"  # 主串口
# self.uart_port = "/dev/ttyS1"  # 备用串口
# self.uart_port = "/dev/ttyUSB0"  # USB串口
```

### 调整超时设置
```python
# 增加超时时间
self.uart_timeout = 0.5  # 从0.1增加到0.5秒
```

### 降低波特率测试
```python
# 临时降低波特率测试
self.uart_baudrate = 9600  # 从115200降低到9600
```

## 📋 检查清单

### 硬件检查
- [ ] MaixCam和STM32都已上电
- [ ] 串口线连接正确 (TX-RX交叉连接)
- [ ] GND线已连接
- [ ] STM32 OLED显示正常状态

### 软件检查  
- [ ] STM32固件已正确烧录
- [ ] STM32显示"CtrlBoard OK"
- [ ] MaixCam系统正常启动
- [ ] 串口设备存在且有权限

### 通信检查
- [ ] 串口设备路径正确
- [ ] 波特率设置匹配 (115200)
- [ ] 没有其他程序占用串口
- [ ] 串口权限正确 (666)

## 🚀 快速修复步骤

1. **运行快速修复**:
   ```bash
   python quick_fix.py
   ```

2. **检查STM32状态**:
   - 确认OLED显示"CtrlBoard OK"
   - 确认舵机已移动到中心位置

3. **重启程序**:
   ```bash
   python main.py
   ```

4. **如果仍有问题**:
   ```bash
   python test_uart.py
   ```

## 🔍 高级调试

### 使用逻辑分析仪
- 监控TX/RX线上的数据传输
- 验证波特率和数据格式
- 检查信号电平和时序

### 使用示波器
- 检查信号质量
- 验证电压电平 (3.3V)
- 检查信号完整性

### 串口监控
```bash
# 使用minicom监控 (如果可用)
minicom -D /dev/ttyS0 -b 115200

# 或使用cat命令
cat /dev/ttyS0
```

## 📞 获取帮助

如果以上方法都无法解决问题，请提供以下信息:

1. **硬件信息**:
   - MaixCam型号和固件版本
   - STM32型号和固件版本
   - 连接方式和线材规格

2. **软件信息**:
   - 运行 `python test_uart.py` 的完整输出
   - 运行 `ls -la /dev/tty*` 的输出
   - STM32 OLED显示的状态信息

3. **错误信息**:
   - 完整的错误日志
   - 问题出现的具体步骤
   - 之前是否正常工作过
