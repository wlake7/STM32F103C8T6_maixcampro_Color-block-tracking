"""
激光追踪模式数据包测试
验证激光追踪模式下的通信是否正确
"""

from config import Config
from communication import Communication
import time

def test_communication():
    """测试通信模块"""
    print("=" * 60)
    print("激光追踪模式通信测试")
    print("=" * 60)
    
    # 初始化配置和通信
    config = Config()
    config.debug_mode = True  # 启用调试模式
    
    comm = Communication(config)
    
    if not comm.is_connected:
        print("✗ 通信初始化失败")
        return False
    
    print("✓ 通信初始化成功")
    
    # 测试数据包发送
    print("\n测试数据包发送...")
    
    # 模拟检测到的位置数据
    target_positions = [
        (320, 240),  # 中心
        (300, 220),  # 左上
        (340, 260),  # 右下
        (280, 200),  # 左上角
        (360, 280)   # 右下角
    ]
    
    laser_positions = [
        (310, 230),  # 稍微偏移
        (290, 210),
        (330, 250),
        (270, 190),
        (350, 270)
    ]
    
    success_count = 0
    total_count = len(target_positions)
    
    for i, (target_pos, laser_pos) in enumerate(zip(target_positions, laser_positions)):
        print(f"\n第{i+1}组数据:")
        print(f"  目标位置: {target_pos}")
        print(f"  激光位置: {laser_pos}")
        
        # 发送位置数据
        success = comm.send_position_data(target_pos, laser_pos)
        
        if success:
            print("  ✓ 数据发送成功")
            success_count += 1
        else:
            print("  ✗ 数据发送失败")
        
        # 等待一段时间
        time.sleep(0.1)
    
    # 统计结果
    print(f"\n" + "=" * 60)
    print("测试结果统计:")
    print(f"成功发送: {success_count}/{total_count}")
    print(f"成功率: {success_count/total_count*100:.1f}%")
    
    # 获取通信统计
    stats = comm.get_communication_stats()
    print(f"发送数据包: {stats['sent_packets']}")
    print(f"失败数据包: {stats['failed_packets']}")
    print(f"通信成功率: {stats['success_rate']:.1f}%")
    
    # 关闭通信
    comm.close()
    
    return success_count == total_count

def test_packet_format():
    """测试数据包格式"""
    print("\n" + "=" * 60)
    print("数据包格式验证")
    print("=" * 60)
    
    config = Config()
    comm = Communication(config)
    
    # 测试目标位置数据包
    target_pos = (320, 240)
    target_x, target_y = int(target_pos[0]), int(target_pos[1])
    target_data = [
        target_x & 0xFF, (target_x >> 8) & 0xFF,
        target_y & 0xFF, (target_y >> 8) & 0xFF
    ]
    target_packet = comm.create_packet(comm.CMD_TARGET_POSITION, target_data)
    
    print("目标位置数据包:")
    print(f"  原始数据: {target_pos}")
    print(f"  数据包: {[hex(b) for b in target_packet]}")
    print(f"  长度: {len(target_packet)} 字节")
    
    # 验证数据包结构
    if len(target_packet) == 9:  # 2(帧头) + 1(长度) + 1(命令) + 4(数据) + 1(校验和)
        print("  ✓ 数据包长度正确")
    else:
        print(f"  ✗ 数据包长度错误: 期望9字节，实际{len(target_packet)}字节")
    
    if target_packet[0] == 0xAA and target_packet[1] == 0x55:
        print("  ✓ 帧头正确")
    else:
        print("  ✗ 帧头错误")
    
    if target_packet[2] == 4:  # 数据长度
        print("  ✓ 长度字段正确")
    else:
        print(f"  ✗ 长度字段错误: 期望4，实际{target_packet[2]}")
    
    if target_packet[3] == comm.CMD_TARGET_POSITION:
        print("  ✓ 命令字段正确")
    else:
        print(f"  ✗ 命令字段错误: 期望{comm.CMD_TARGET_POSITION}，实际{target_packet[3]}")
    
    # 验证校验和
    calculated_checksum = comm.calculate_checksum(target_packet[2:8])
    received_checksum = target_packet[8]
    if calculated_checksum == received_checksum:
        print(f"  ✓ 校验和正确: {hex(calculated_checksum)}")
    else:
        print(f"  ✗ 校验和错误: 期望{hex(calculated_checksum)}, 实际{hex(received_checksum)}")
    
    # 验证坐标解析
    parsed_x = target_packet[4] | (target_packet[5] << 8)
    parsed_y = target_packet[6] | (target_packet[7] << 8)
    if parsed_x == target_x and parsed_y == target_y:
        print(f"  ✓ 坐标解析正确: ({parsed_x}, {parsed_y})")
    else:
        print(f"  ✗ 坐标解析错误: 期望({target_x}, {target_y}), 解析({parsed_x}, {parsed_y})")

def main():
    """主测试函数"""
    print("激光追踪模式数据包测试")
    print("请确保STM32已连接并运行通信调试模式")
    
    # 测试数据包格式
    test_packet_format()
    
    # 测试通信
    success = test_communication()
    
    if success:
        print("\n🎉 所有测试通过！激光追踪模式通信正常")
    else:
        print("\n❌ 测试失败，请检查硬件连接和STM32程序")

if __name__ == "__main__":
    main()
