#!/usr/bin/env python3
"""
串口连接诊断工具
用于检测和解决MaixCam串口连接问题
"""

import os
import time
from maix import uart

def check_uart_devices():
    """检查可用的串口设备"""
    print("=== 串口设备检查 ===")
    
    # 常见的串口设备路径
    uart_paths = [
        "/dev/ttyS0",
        "/dev/ttyS1", 
        "/dev/ttyS2",
        "/dev/ttyUSB0",
        "/dev/ttyUSB1",
        "/dev/ttyAMA0",
        "/dev/ttyAMA1"
    ]
    
    available_ports = []
    
    for path in uart_paths:
        if os.path.exists(path):
            print(f"✅ 发现串口设备: {path}")
            available_ports.append(path)
        else:
            print(f"❌ 串口设备不存在: {path}")
    
    return available_ports

def check_uart_permissions(port):
    """检查串口权限"""
    print(f"\n=== 检查串口权限: {port} ===")
    
    try:
        # 检查文件权限
        stat_info = os.stat(port)
        print(f"文件权限: {oct(stat_info.st_mode)}")
        
        # 检查是否可读写
        if os.access(port, os.R_OK):
            print("✅ 串口可读")
        else:
            print("❌ 串口不可读")
            
        if os.access(port, os.W_OK):
            print("✅ 串口可写")
        else:
            print("❌ 串口不可写")
            
        return os.access(port, os.R_OK | os.W_OK)
        
    except Exception as e:
        print(f"❌ 权限检查失败: {e}")
        return False

def test_uart_connection(port, baudrate=115200):
    """测试串口连接"""
    print(f"\n=== 测试串口连接: {port}@{baudrate} ===")
    
    try:
        # 尝试打开串口
        uart_port = uart.UART(port, baudrate, 8, 0, 1, timeout=0.1)
        print("✅ 串口打开成功")
        
        # 测试发送数据
        test_data = b"TEST"
        uart_port.write(test_data)
        print(f"✅ 数据发送成功: {test_data}")
        
        # 尝试读取数据
        time.sleep(0.1)
        received = uart_port.read(10)
        if received:
            print(f"📥 接收到数据: {received}")
        else:
            print("📭 未接收到数据 (正常，如果STM32未连接)")
        
        uart_port.close()
        print("✅ 串口关闭成功")
        return True
        
    except Exception as e:
        print(f"❌ 串口连接失败: {e}")
        return False

def check_system_info():
    """检查系统信息"""
    print("\n=== 系统信息检查 ===")
    
    try:
        # 检查内核版本
        with open("/proc/version", "r") as f:
            kernel_version = f.read().strip()
            print(f"内核版本: {kernel_version}")
    except:
        print("❌ 无法读取内核版本")
    
    try:
        # 检查串口驱动
        os.system("lsmod | grep -i uart")
        os.system("lsmod | grep -i serial")
    except:
        print("❌ 无法检查串口驱动")

def check_uart_usage():
    """检查串口是否被其他进程占用"""
    print("\n=== 检查串口占用情况 ===")
    
    try:
        # 检查进程占用
        os.system("lsof | grep -i tty")
        os.system("ps aux | grep -i uart")
    except:
        print("❌ 无法检查进程占用")

def main():
    """主诊断流程"""
    print("🔍 MaixCam串口连接诊断工具")
    print("=" * 50)
    
    # 1. 检查可用串口设备
    available_ports = check_uart_devices()
    
    if not available_ports:
        print("\n❌ 未发现任何串口设备！")
        print("请检查:")
        print("1. 硬件连接是否正确")
        print("2. 设备驱动是否正常")
        return
    
    # 2. 检查系统信息
    check_system_info()
    
    # 3. 检查串口占用
    check_uart_usage()
    
    # 4. 测试每个可用串口
    working_ports = []
    for port in available_ports:
        if check_uart_permissions(port):
            if test_uart_connection(port):
                working_ports.append(port)
    
    # 5. 输出诊断结果
    print("\n" + "=" * 50)
    print("🎯 诊断结果总结")
    print("=" * 50)
    
    if working_ports:
        print("✅ 可用的串口设备:")
        for port in working_ports:
            print(f"   - {port}")
        print(f"\n💡 建议在config.py中设置: uart_port = \"{working_ports[0]}\"")
    else:
        print("❌ 没有可用的串口设备")
        print("\n🔧 故障排除建议:")
        print("1. 检查硬件连接:")
        print("   - MaixCam Pin8(TX) → STM32 PA10(RX)")
        print("   - MaixCam Pin10(RX) ← STM32 PA9(TX)")
        print("   - 确保GND连接")
        print("2. 检查STM32是否正常工作")
        print("3. 尝试重启MaixCam设备")
        print("4. 检查串口权限: sudo chmod 666 /dev/ttyS*")

if __name__ == "__main__":
    main()
