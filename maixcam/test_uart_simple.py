"""
简单UART测试脚本
基于官方例程格式测试串口通信
"""

from maix import uart
import time

def test_uart_basic():
    """基础UART测试"""
    print("=" * 50)
    print("基础UART测试 (基于官方例程)")
    print("=" * 50)
    
    # 使用串口2
    device = "/dev/ttyS2"  # 串口2
    baudrate = 115200
    
    try:
        # 初始化串口 (官方格式)
        serial = uart.UART(device, baudrate)
        print(f"UART初始化成功: {device}@{baudrate}")
        
        # 测试发送字符串
        test_message = "hello from maixcam"
        print(f"发送消息: {test_message}")
        serial.write_str(test_message)
        
        # 测试发送字节数据
        test_bytes = bytes([0xAA, 0x55, 0x04, 0x01, 0x40, 0x01, 0xF0, 0x00, 0x3B])
        print(f"发送字节数据: {[hex(b) for b in test_bytes]}")
        serial.write(test_bytes)
        
        # 尝试接收数据
        print("等待接收数据...")
        received = serial.read(timeout=2000)  # 2秒超时
        if received:
            print(f"接收到数据: {received}")
            if isinstance(received, bytes):
                print(f"字节格式: {[hex(b) for b in received]}")
        else:
            print("未接收到数据")
        
        print("UART测试完成")
        return True
        
    except Exception as e:
        print(f"UART测试失败: {e}")
        return False

def test_laser_tracking_protocol():
    """测试激光追踪协议数据包"""
    print("=" * 50)
    print("激光追踪协议测试")
    print("=" * 50)
    
    device = "/dev/ttyS2"
    baudrate = 115200
    
    try:
        serial = uart.UART(device, baudrate)
        print(f"UART初始化成功: {device}@{baudrate}")
        
        # 模拟发送目标位置数据
        # 协议格式: [0xAA, 0x55, Length, Cmd, Data...]
        
        # 目标位置: (320, 240)
        target_x = 320
        target_y = 240
        target_packet = bytes([
            0xAA, 0x55,                    # 帧头
            0x04,                          # 数据长度
            0x01,                          # 命令: 目标位置
            target_x & 0xFF,               # X坐标低字节
            (target_x >> 8) & 0xFF,        # X坐标高字节
            target_y & 0xFF,               # Y坐标低字节
            (target_y >> 8) & 0xFF         # Y坐标高字节
        ])
        
        print(f"发送目标位置数据: ({target_x}, {target_y})")
        print(f"数据包: {[hex(b) for b in target_packet]}")
        serial.write(target_packet)
        
        time.sleep(0.1)  # 短暂延时
        
        # 激光位置: (300, 220)
        laser_x = 300
        laser_y = 220
        laser_packet = bytes([
            0xAA, 0x55,                    # 帧头
            0x04,                          # 数据长度
            0x02,                          # 命令: 激光位置
            laser_x & 0xFF,                # X坐标低字节
            (laser_x >> 8) & 0xFF,         # X坐标高字节
            laser_y & 0xFF,                # Y坐标低字节
            (laser_y >> 8) & 0xFF          # Y坐标高字节
        ])
        
        print(f"发送激光位置数据: ({laser_x}, {laser_y})")
        print(f"数据包: {[hex(b) for b in laser_packet]}")
        serial.write(laser_packet)
        
        # 尝试接收响应
        print("等待STM32响应...")
        response = serial.read(timeout=1000)
        if response:
            print(f"收到响应: {response}")
        else:
            print("未收到响应")
        
        print("协议测试完成")
        return True
        
    except Exception as e:
        print(f"协议测试失败: {e}")
        return False

def test_continuous_sending():
    """连续发送测试"""
    print("=" * 50)
    print("连续发送测试")
    print("=" * 50)
    
    device = "/dev/ttyS2"
    baudrate = 115200
    
    try:
        serial = uart.UART(device, baudrate)
        print(f"UART初始化成功: {device}@{baudrate}")
        
        print("开始连续发送位置数据...")
        
        for i in range(10):
            # 模拟移动的目标和激光位置
            target_x = 320 + i * 5
            target_y = 240 + i * 3
            laser_x = 300 + i * 4
            laser_y = 220 + i * 2
            
            # 发送目标位置
            target_packet = bytes([
                0xAA, 0x55, 0x04, 0x01,
                target_x & 0xFF, (target_x >> 8) & 0xFF,
                target_y & 0xFF, (target_y >> 8) & 0xFF
            ])
            serial.write(target_packet)
            
            time.sleep(0.05)  # 50ms间隔
            
            # 发送激光位置
            laser_packet = bytes([
                0xAA, 0x55, 0x04, 0x02,
                laser_x & 0xFF, (laser_x >> 8) & 0xFF,
                laser_y & 0xFF, (laser_y >> 8) & 0xFF
            ])
            serial.write(laser_packet)
            
            print(f"发送第{i+1}组数据: 目标({target_x},{target_y}) 激光({laser_x},{laser_y})")
            time.sleep(0.1)  # 100ms间隔
        
        print("连续发送测试完成")
        return True
        
    except Exception as e:
        print(f"连续发送测试失败: {e}")
        return False

def main():
    """主测试函数"""
    print("MaixCam UART通信测试 (官方API格式)")
    print("请确保STM32已连接到串口2并运行激光追踪程序")
    
    print("\n选择测试项目:")
    print("1. 基础UART测试")
    print("2. 激光追踪协议测试")
    print("3. 连续发送测试")
    print("4. 全部测试")
    
    choice = input("请输入选择 (1-4): ").strip()
    
    if choice == "1":
        test_uart_basic()
    elif choice == "2":
        test_laser_tracking_protocol()
    elif choice == "3":
        test_continuous_sending()
    elif choice == "4":
        print("开始全部测试...")
        test_uart_basic()
        print("\n" + "="*30)
        test_laser_tracking_protocol()
        print("\n" + "="*30)
        test_continuous_sending()
    else:
        print("无效选择")

if __name__ == "__main__":
    main()
