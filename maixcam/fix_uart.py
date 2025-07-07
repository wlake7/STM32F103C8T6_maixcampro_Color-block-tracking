#!/usr/bin/env python3
"""
串口连接修复工具
快速诊断和修复MaixCam串口连接问题
"""

import os
import time
from maix import uart

def fix_uart_permissions():
    """修复串口权限"""
    print("🔧 修复串口权限...")
    
    uart_devices = ["/dev/ttyS0", "/dev/ttyS1", "/dev/ttyS2"]
    
    for device in uart_devices:
        if os.path.exists(device):
            try:
                os.system(f"chmod 666 {device}")
                print(f"✅ 已修复权限: {device}")
            except:
                print(f"❌ 权限修复失败: {device}")

def detect_working_uart():
    """检测可用的串口"""
    print("🔍 检测可用串口...")
    
    uart_candidates = [
        "/dev/ttyS0",
        "/dev/ttyS1", 
        "/dev/ttyS2",
        "/dev/ttyUSB0",
        "/dev/ttyAMA0"
    ]
    
    for port in uart_candidates:
        if os.path.exists(port):
            try:
                # 尝试打开串口
                test_uart = uart.UART(port, 115200, 8, 0, 1, timeout=0.1)
                test_uart.close()
                print(f"✅ 串口可用: {port}")
                return port
            except Exception as e:
                print(f"❌ 串口不可用: {port} - {e}")
    
    return None

def update_config_file(uart_port):
    """更新配置文件中的串口设置"""
    print(f"📝 更新配置文件: {uart_port}")
    
    config_file = "config.py"
    
    try:
        # 读取配置文件
        with open(config_file, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # 替换串口配置
        import re
        pattern = r'self\.uart_port\s*=\s*"[^"]*"'
        replacement = f'self.uart_port = "{uart_port}"'
        
        new_content = re.sub(pattern, replacement, content)
        
        # 写回文件
        with open(config_file, 'w', encoding='utf-8') as f:
            f.write(new_content)
        
        print(f"✅ 配置文件已更新: uart_port = {uart_port}")
        
    except Exception as e:
        print(f"❌ 配置文件更新失败: {e}")

def test_communication():
    """测试通信功能"""
    print("🧪 测试通信功能...")
    
    try:
        from config import Config
        from communication import Communication
        
        # 创建配置和通信对象
        config = Config()
        comm = Communication(config)
        
        if comm.is_connected:
            print("✅ 通信模块初始化成功")
            
            # 测试发送数据
            test_result = comm.test_connection()
            if test_result:
                print("✅ 通信测试成功")
            else:
                print("⚠️ 通信测试失败，但连接正常")
        else:
            print("❌ 通信模块初始化失败")
            
    except Exception as e:
        print(f"❌ 通信测试异常: {e}")

def main():
    """主修复流程"""
    print("🚀 MaixCam串口连接修复工具")
    print("=" * 40)
    
    # 步骤1: 修复权限
    fix_uart_permissions()
    
    # 步骤2: 检测可用串口
    working_port = detect_working_uart()
    
    if not working_port:
        print("\n❌ 未找到可用的串口设备")
        print("请检查:")
        print("1. 硬件连接是否正确")
        print("2. STM32是否正常工作")
        print("3. 串口驱动是否正常")
        return
    
    # 步骤3: 更新配置
    update_config_file(working_port)
    
    # 步骤4: 测试通信
    test_communication()
    
    print("\n" + "=" * 40)
    print("🎯 修复完成")
    print("=" * 40)
    print(f"✅ 推荐串口: {working_port}")
    print("✅ 配置已更新")
    print("💡 请重新运行主程序测试")

if __name__ == "__main__":
    main()
