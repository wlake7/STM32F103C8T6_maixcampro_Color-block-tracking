"""
通信诊断工具
专门用于诊断MaixCam与STM32之间的通信问题
"""

from maix import uart, time
import struct

def test_uart_basic():
    """基础UART连接测试"""
    print("=" * 60)
    print("1. 基础UART连接测试")
    print("=" * 60)
    
    try:
        # 使用默认串口0
        device = "/dev/ttyS0"
        serial = uart.UART(device, 115200)
        print(f"✓ UART初始化成功: {device}@115200")
        
        # 等待开机日志结束
        print("等待MaixCam开机日志结束...")
        time.sleep(2)
        
        # 清空接收缓冲区
        serial.read(timeout=100)
        print("✓ 清空接收缓冲区")
        
        return serial
        
    except Exception as e:
        print(f"✗ UART初始化失败: {e}")
        return None

def test_protocol_sending(serial):
    """测试协议数据包发送"""
    print("\n" + "=" * 60)
    print("2. 协议数据包发送测试")
    print("=" * 60)
    
    if not serial:
        print("✗ 串口未初始化，跳过测试")
        return False
    
    try:
        # 测试数据包1：目标位置
        target_x, target_y = 320, 240
        target_packet = bytes([
            0xAA, 0x55,                    # 帧头
            0x04,                          # 数据长度
            0x01,                          # 命令：目标位置
            target_x & 0xFF,               # X坐标低字节
            (target_x >> 8) & 0xFF,        # X坐标高字节
            target_y & 0xFF,               # Y坐标低字节
            (target_y >> 8) & 0xFF         # Y坐标高字节
        ])
        
        print(f"发送目标位置: ({target_x}, {target_y})")
        print(f"数据包: {[hex(b) for b in target_packet]}")
        serial.write(target_packet)
        print("✓ 目标位置数据包发送完成")
        
        time.sleep(0.1)
        
        # 测试数据包2：激光位置
        laser_x, laser_y = 300, 220
        laser_packet = bytes([
            0xAA, 0x55,                    # 帧头
            0x04,                          # 数据长度
            0x02,                          # 命令：激光位置
            laser_x & 0xFF,                # X坐标低字节
            (laser_x >> 8) & 0xFF,         # X坐标高字节
            laser_y & 0xFF,                # Y坐标低字节
            (laser_y >> 8) & 0xFF          # Y坐标高字节
        ])
        
        print(f"发送激光位置: ({laser_x}, {laser_y})")
        print(f"数据包: {[hex(b) for b in laser_packet]}")
        serial.write(laser_packet)
        print("✓ 激光位置数据包发送完成")
        
        return True
        
    except Exception as e:
        print(f"✗ 数据包发送失败: {e}")
        return False

def test_continuous_tracking(serial):
    """测试连续追踪数据发送"""
    print("\n" + "=" * 60)
    print("3. 连续追踪数据发送测试")
    print("=" * 60)
    
    if not serial:
        print("✗ 串口未初始化，跳过测试")
        return False
    
    try:
        print("开始发送连续追踪数据...")
        print("模拟场景：目标在移动，激光在追踪")
        
        for i in range(20):
            # 模拟移动的目标
            target_x = 320 + int(50 * (i % 10 - 5))  # 在中心附近摆动
            target_y = 240 + int(30 * (i % 8 - 4))
            
            # 模拟追踪的激光（有延迟和误差）
            laser_x = target_x - 20 + int(10 * (i % 3))
            laser_y = target_y - 15 + int(8 * (i % 4))
            
            # 发送目标位置
            target_packet = bytes([
                0xAA, 0x55, 0x04, 0x01,
                target_x & 0xFF, (target_x >> 8) & 0xFF,
                target_y & 0xFF, (target_y >> 8) & 0xFF
            ])
            serial.write(target_packet)
            
            time.sleep(0.02)  # 20ms间隔
            
            # 发送激光位置
            laser_packet = bytes([
                0xAA, 0x55, 0x04, 0x02,
                laser_x & 0xFF, (laser_x >> 8) & 0xFF,
                laser_y & 0xFF, (laser_y >> 8) & 0xFF
            ])
            serial.write(laser_packet)
            
            print(f"第{i+1:2d}组: 目标({target_x:3d},{target_y:3d}) 激光({laser_x:3d},{laser_y:3d}) 误差({target_x-laser_x:+3d},{target_y-laser_y:+3d})")
            
            time.sleep(0.08)  # 100ms总间隔，模拟10Hz
        
        print("✓ 连续追踪数据发送完成")
        return True
        
    except Exception as e:
        print(f"✗ 连续数据发送失败: {e}")
        return False

def test_response_monitoring(serial):
    """监控STM32响应"""
    print("\n" + "=" * 60)
    print("4. STM32响应监控测试")
    print("=" * 60)
    
    if not serial:
        print("✗ 串口未初始化，跳过测试")
        return False
    
    try:
        print("监控STM32响应数据...")
        print("如果STM32有调试输出，应该能看到数据")
        
        # 发送一个测试数据包
        test_packet = bytes([0xAA, 0x55, 0x04, 0x01, 0x40, 0x01, 0xF0, 0x00])
        serial.write(test_packet)
        print("已发送测试数据包，等待响应...")
        
        # 监控响应
        for i in range(10):
            response = serial.read(timeout=500)
            if response:
                print(f"收到响应: {response}")
                if isinstance(response, bytes):
                    print(f"字节格式: {[hex(b) for b in response]}")
                break
            else:
                print(f"等待响应... ({i+1}/10)")
        else:
            print("⚠ 未收到STM32响应")
            print("可能原因：")
            print("  1. STM32未运行或未连接")
            print("  2. 串口连接错误")
            print("  3. STM32端未配置调试输出")
        
        return True
        
    except Exception as e:
        print(f"✗ 响应监控失败: {e}")
        return False

def main():
    """主诊断函数"""
    print("MaixCam ↔ STM32 通信诊断工具")
    print("请确保：")
    print("1. STM32已连接并运行激光追踪程序")
    print("2. 串口连接正确：MaixCam A16(TX)→STM32 PA10(RX), MaixCam A17(RX)→STM32 PA9(TX)")
    print("3. 共地连接")
    
    input("\n按Enter键开始诊断...")
    
    # 执行诊断步骤
    serial = test_uart_basic()
    
    if serial:
        test_protocol_sending(serial)
        test_continuous_tracking(serial)
        test_response_monitoring(serial)
        
        print("\n" + "=" * 60)
        print("诊断完成")
        print("=" * 60)
        print("如果看到所有✓标记，说明MaixCam端通信正常")
        print("如果未收到STM32响应，请检查STM32端配置")
    else:
        print("\n✗ 基础UART连接失败，请检查硬件连接")

if __name__ == "__main__":
    main()
