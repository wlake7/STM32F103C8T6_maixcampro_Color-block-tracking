#!/usr/bin/env python3
"""
快速修复串口连接问题
"""

import os
import sys

def main():
    print("🔧 快速修复MaixCam串口连接问题")
    print("=" * 40)
    
    # 1. 检查常见串口设备
    uart_devices = ["/dev/ttyS0", "/dev/ttyS1", "/dev/ttyS2", "/dev/ttyUSB0"]
    available = []
    
    for device in uart_devices:
        if os.path.exists(device):
            available.append(device)
            print(f"✅ 发现设备: {device}")
        else:
            print(f"❌ 设备不存在: {device}")
    
    if not available:
        print("\n❌ 未发现任何串口设备！")
        print("请检查硬件连接和驱动")
        return
    
    # 2. 修复权限
    print(f"\n🔧 修复串口权限...")
    for device in available:
        os.system(f"chmod 666 {device} 2>/dev/null")
        print(f"✅ 权限已修复: {device}")
    
    # 3. 测试串口
    print(f"\n🧪 测试串口连接...")
    working_port = None
    
    for device in available:
        try:
            from maix import uart
            test_uart = uart.UART(device, 115200, 8, 0, 1, timeout=0.1)
            test_uart.close()
            working_port = device
            print(f"✅ 串口测试成功: {device}")
            break
        except Exception as e:
            print(f"❌ 串口测试失败: {device} - {str(e)[:50]}")
    
    if not working_port:
        print("\n❌ 所有串口测试都失败了")
        print("可能的原因:")
        print("1. STM32未连接或未上电")
        print("2. 硬件连接错误")
        print("3. 串口驱动问题")
        return
    
    # 4. 更新配置文件
    print(f"\n📝 更新配置文件...")
    try:
        # 读取当前配置
        with open("config.py", "r") as f:
            content = f.read()
        
        # 查找并替换串口配置
        import re
        old_pattern = r'self\.uart_port\s*=\s*"[^"]*"'
        new_setting = f'self.uart_port = "{working_port}"'
        
        if re.search(old_pattern, content):
            new_content = re.sub(old_pattern, new_setting, content)
            
            # 写回文件
            with open("config.py", "w") as f:
                f.write(new_content)
            
            print(f"✅ 配置已更新: uart_port = {working_port}")
        else:
            print("⚠️ 未找到uart_port配置项")
            
    except Exception as e:
        print(f"❌ 配置更新失败: {e}")
    
    # 5. 给出使用建议
    print(f"\n🎯 修复完成！")
    print("=" * 40)
    print(f"推荐串口: {working_port}")
    print("下一步:")
    print("1. 确保STM32正常工作并显示'CtrlBoard OK'")
    print("2. 重新运行主程序: python main.py")
    print("3. 如果仍有问题，运行: python test_uart.py")

if __name__ == "__main__":
    main()
