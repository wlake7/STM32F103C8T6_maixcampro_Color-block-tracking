#!/usr/bin/env python3
"""
测试改进后的通信模块
基于comm_protocol_yolov5.py的方法
"""

import time
import sys

def test_comm_protocol_import():
    """测试CommProtocol导入"""
    print("=== 测试CommProtocol导入 ===")
    try:
        from maix import comm, protocol
        from maix.err import Err
        print("✅ CommProtocol模块导入成功")
        return True
    except Exception as e:
        print(f"❌ CommProtocol模块导入失败: {e}")
        return False

def test_comm_protocol_init():
    """测试CommProtocol初始化"""
    print("\n=== 测试CommProtocol初始化 ===")
    try:
        from maix import comm
        
        # 尝试初始化CommProtocol
        p = comm.CommProtocol(buff_size=1024)
        print("✅ CommProtocol初始化成功")
        return True, p
    except Exception as e:
        print(f"❌ CommProtocol初始化失败: {e}")
        return False, None

def test_communication_module():
    """测试改进后的通信模块"""
    print("\n=== 测试改进后的通信模块 ===")
    try:
        from config import Config
        from communication import Communication
        
        # 创建配置和通信对象
        config = Config()
        comm = Communication(config)
        
        if comm.is_connected:
            print("✅ 通信模块初始化成功")
            
            # 检查使用的通信方式
            if comm.comm_protocol:
                print("✅ 使用CommProtocol通信方式")
            elif hasattr(comm, 'uart_port') and comm.uart_port:
                print("✅ 使用UART回退通信方式")
            else:
                print("⚠️ 通信方式未知")
            
            return True, comm
        else:
            print("❌ 通信模块初始化失败")
            return False, None
            
    except Exception as e:
        print(f"❌ 通信模块测试异常: {e}")
        return False, None

def test_position_data_sending(comm):
    """测试位置数据发送"""
    print("\n=== 测试位置数据发送 ===")
    try:
        # 模拟位置数据
        target_pos = (320, 240)  # 目标位置
        laser_pos = (315, 245)   # 激光位置
        
        print(f"发送测试数据: 目标{target_pos}, 激光{laser_pos}")
        
        # 发送数据
        result = comm.send_position_data(target_pos, laser_pos)
        
        if result:
            print("✅ 位置数据发送成功")
        else:
            print("❌ 位置数据发送失败")
            
        return result
        
    except Exception as e:
        print(f"❌ 位置数据发送异常: {e}")
        return False

def test_communication_stats(comm):
    """测试通信统计"""
    print("\n=== 测试通信统计 ===")
    try:
        stats = comm.get_communication_stats()
        print(f"通信统计:")
        print(f"  连接状态: {stats['connected']}")
        print(f"  发送包数: {stats['sent_packets']}")
        print(f"  失败包数: {stats['failed_packets']}")
        print(f"  成功率: {stats['success_rate']:.1f}%")
        return True
    except Exception as e:
        print(f"❌ 通信统计异常: {e}")
        return False

def test_system_config():
    """测试系统配置"""
    print("\n=== 测试系统配置 ===")
    try:
        from maix import app
        
        # 检查通信方法配置
        comm_method = app.get_sys_config_kv("comm", "method")
        print(f"系统通信方法: {comm_method}")
        
        # 检查其他相关配置
        print("系统配置检查完成")
        return True
    except Exception as e:
        print(f"❌ 系统配置检查异常: {e}")
        return False

def main():
    """主测试流程"""
    print("🧪 改进后的通信模块测试")
    print("=" * 50)
    
    # 测试1: 模块导入
    if not test_comm_protocol_import():
        print("\n❌ 基础模块导入失败，无法继续测试")
        return
    
    # 测试2: CommProtocol初始化
    success, proto = test_comm_protocol_init()
    if success:
        print("✅ CommProtocol可用")
    else:
        print("⚠️ CommProtocol不可用，将使用UART回退")
    
    # 测试3: 系统配置
    test_system_config()
    
    # 测试4: 通信模块
    success, comm = test_communication_module()
    if not success:
        print("\n❌ 通信模块测试失败")
        return
    
    # 测试5: 位置数据发送
    for i in range(3):
        print(f"\n--- 第{i+1}次发送测试 ---")
        test_position_data_sending(comm)
        time.sleep(0.1)
    
    # 测试6: 通信统计
    test_communication_stats(comm)
    
    # 清理
    comm.close()
    
    print("\n" + "=" * 50)
    print("🎯 测试完成")
    print("=" * 50)
    
    print("\n💡 使用建议:")
    if comm.comm_protocol:
        print("✅ 推荐使用CommProtocol方式，更稳定可靠")
    else:
        print("⚠️ 当前使用UART回退方式")
        print("   建议检查系统配置或MaixPy版本")
    
    print("\n📝 下一步:")
    print("1. 确保STM32正常工作")
    print("2. 运行主程序: python main.py")
    print("3. 观察通信状态和数据传输")

if __name__ == "__main__":
    main()
