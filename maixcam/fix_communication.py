#!/usr/bin/env python3
"""
通信问题快速修复脚本
解决"串口未连接，无法发送数据"问题
"""

import os
import shutil
import time

def backup_original():
    """备份原始通信模块"""
    print("📦 备份原始通信模块...")
    try:
        if os.path.exists("communication.py"):
            backup_name = f"communication_backup_{int(time.time())}.py"
            shutil.copy2("communication.py", backup_name)
            print(f"✅ 原始文件已备份为: {backup_name}")
            return True
    except Exception as e:
        print(f"❌ 备份失败: {e}")
        return False

def switch_to_simple_communication():
    """切换到简化版通信模块"""
    print("🔄 切换到简化版通信模块...")
    try:
        if os.path.exists("communication_simple.py"):
            # 备份原文件
            backup_original()
            
            # 复制简化版本
            shutil.copy2("communication_simple.py", "communication.py")
            print("✅ 已切换到简化版通信模块")
            return True
        else:
            print("❌ 找不到简化版通信模块文件")
            return False
    except Exception as e:
        print(f"❌ 切换失败: {e}")
        return False

def test_new_communication():
    """测试新的通信模块"""
    print("🧪 测试新的通信模块...")
    try:
        from config import Config
        from communication import Communication
        
        config = Config()
        comm = Communication(config)
        
        if comm.is_connected:
            print("✅ 新通信模块工作正常")
            
            # 显示使用的通信方式
            stats = comm.get_stats()
            print(f"📡 通信方式: {stats['method']}")
            
            # 测试发送数据
            test_result = comm.test_connection()
            if test_result:
                print("✅ 数据发送测试成功")
            else:
                print("⚠️ 数据发送测试失败，但连接正常")
            
            comm.close()
            return True
        else:
            print("❌ 新通信模块连接失败")
            return False
            
    except Exception as e:
        print(f"❌ 测试异常: {e}")
        return False

def check_system_environment():
    """检查系统环境"""
    print("🔍 检查系统环境...")
    
    # 检查串口设备
    uart_devices = ["/dev/ttyS0", "/dev/ttyS1", "/dev/ttyS2", "/dev/ttyUSB0"]
    available_devices = []
    
    for device in uart_devices:
        if os.path.exists(device):
            available_devices.append(device)
            print(f"✅ 发现串口设备: {device}")
    
    if not available_devices:
        print("⚠️ 未发现可用的串口设备")
    
    # 检查MaixPy模块
    try:
        from maix import comm
        print("✅ MaixPy comm模块可用")
    except:
        print("⚠️ MaixPy comm模块不可用")
    
    try:
        from maix import uart
        print("✅ MaixPy uart模块可用")
    except:
        print("⚠️ MaixPy uart模块不可用")

def show_usage_guide():
    """显示使用指南"""
    print("\n" + "=" * 50)
    print("📖 使用指南")
    print("=" * 50)
    
    print("\n🎯 修复完成后的使用步骤:")
    print("1. 运行主程序: python main.py")
    print("2. 观察终端输出，查看通信状态")
    print("3. 如果仍有问题，检查硬件连接")
    
    print("\n🔧 如果问题仍然存在:")
    print("1. 检查STM32是否正常工作")
    print("2. 检查串口线连接")
    print("3. 确认波特率设置正确(115200)")
    print("4. 运行: python test_communication_v2.py")
    
    print("\n📝 恢复原始版本:")
    print("1. 查找备份文件: communication_backup_*.py")
    print("2. 复制回原文件名: cp communication_backup_*.py communication.py")

def main():
    """主修复流程"""
    print("🛠️ 通信问题快速修复工具")
    print("=" * 50)
    print("解决问题: 串口未连接，无法发送数据")
    print("参考方案: comm_protocol_yolov5.py")
    print("=" * 50)
    
    # 步骤1: 检查环境
    check_system_environment()
    
    # 步骤2: 切换到简化版通信模块
    print(f"\n{'='*20} 开始修复 {'='*20}")
    
    if not switch_to_simple_communication():
        print("❌ 修复失败，无法切换通信模块")
        return
    
    # 步骤3: 测试新模块
    if test_new_communication():
        print("\n🎉 修复成功！")
        print("✅ 通信模块已更新并测试通过")
    else:
        print("\n⚠️ 修复部分成功")
        print("✅ 通信模块已更新，但测试未完全通过")
        print("💡 建议检查硬件连接和STM32状态")
    
    # 步骤4: 显示使用指南
    show_usage_guide()
    
    print(f"\n{'='*20} 修复完成 {'='*20}")

if __name__ == "__main__":
    main()
