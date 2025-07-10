"""
通信测试脚本
测试与STM32的串口通信功能
"""

from config import Config
from communication import Communication
import time

def test_uart_connection():
    """测试UART连接"""
    print("=" * 50)
    print("UART连接测试")
    print("=" * 50)
    
    # 加载配置
    config = Config()
    
    # 初始化通信模块
    comm = Communication(config)
    
    if not comm.is_connected:
        print("UART连接失败")
        return False
    
    print("UART连接成功")
    
    # 测试发送数据包
    print("\n测试发送数据包...")
    
    # 发送测试位置数据
    target_pos = (320, 240)  # 图像中心
    laser_pos = (300, 220)   # 稍微偏移的激光位置
    
    success = comm.send_position_data(target_pos, laser_pos)
    if success:
        print(f"位置数据发送成功: 目标{target_pos}, 激光{laser_pos}")
    else:
        print("位置数据发送失败")
    
    # 发送PID参数
    print("\n测试发送PID参数...")
    success = comm.send_pid_params(2.0, 0.1, 0.5, 2.0, 0.1, 0.5)
    if success:
        print("PID参数发送成功")
    else:
        print("PID参数发送失败")
    
    # 显示统计信息
    stats = comm.get_communication_stats()
    print(f"\n通信统计:")
    print(f"连接状态: {stats['connected']}")
    print(f"发送成功: {stats['sent_packets']}")
    print(f"发送失败: {stats['failed_packets']}")
    print(f"成功率: {stats['success_rate']:.1f}%")
    
    # 关闭连接
    comm.close()
    print("\n通信测试完成")
    return True

def test_available_ports():
    """测试可用端口检测"""
    print("=" * 50)
    print("可用端口检测")
    print("=" * 50)

    try:
        from maix import uart
        # 根据官方例程，可以尝试常见的串口设备
        common_ports = ["/dev/ttyS0", "/dev/ttyS1", "/dev/ttyS2", "/dev/ttyUSB0"]
        print(f"常见UART端口: {common_ports}")
        print("建议使用: /dev/ttyS2 (串口2)")

        # 可以尝试使用uart.list_devices()如果可用
        try:
            ports = uart.list_devices()
            print(f"系统检测到的端口: {ports}")
        except:
            print("uart.list_devices()不可用，使用默认端口")

    except Exception as e:
        print(f"端口检测失败: {e}")

def test_packet_format():
    """测试数据包格式"""
    print("=" * 50)
    print("数据包格式测试")
    print("=" * 50)
    
    config = Config()
    comm = Communication(config)
    
    # 测试创建数据包
    test_data = [0x01, 0x02, 0x03, 0x04]
    packet = comm.create_packet(0x01, test_data)
    
    print(f"测试数据: {[hex(b) for b in test_data]}")
    print(f"生成数据包: {[hex(b) for b in packet]}")
    
    # 验证数据包格式
    expected_format = [0xAA, 0x55, len(test_data), 0x01] + test_data
    checksum = comm.calculate_checksum(expected_format[2:])
    expected_format.append(checksum)
    
    print(f"期望格式: {[hex(b) for b in expected_format]}")
    
    if packet == bytes(expected_format):
        print("✓ 数据包格式正确")
    else:
        print("✗ 数据包格式错误")

def main():
    """主测试函数"""
    print("MaixCam通信模块测试")
    print("请确保STM32已连接并运行激光追踪程序")
    
    # 测试可用端口
    test_available_ports()
    
    print("\n" + "=" * 50)
    input("按Enter键继续UART连接测试...")
    
    # 测试数据包格式
    test_packet_format()
    
    print("\n" + "=" * 50)
    input("按Enter键继续UART通信测试...")
    
    # 测试UART连接
    test_uart_connection()

if __name__ == "__main__":
    main()
