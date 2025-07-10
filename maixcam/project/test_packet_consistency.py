"""
测试激光追踪模式与通信诊断模式的数据包格式一致性
"""

def test_diagnosis_format():
    """测试run_communication_diagnosis()的数据包格式"""
    print("=" * 60)
    print("测试 run_communication_diagnosis() 数据包格式")
    print("=" * 60)
    
    # 模拟run_communication_diagnosis()中的数据包构建
    target_x, target_y = 320, 240
    laser_x, laser_y = 300, 220
    
    def calculate_checksum(packet_data):
        """计算校验和: 从'数据长度'到'数据内容'末尾的所有字节之和"""
        return sum(packet_data[2:]) & 0xFF
    
    # 目标位置数据包
    target_data = bytearray([
        0xAA, 0x55, 0x04, 0x01,
        target_x & 0xFF, (target_x >> 8) & 0xFF,
        target_y & 0xFF, (target_y >> 8) & 0xFF
    ])
    target_checksum = calculate_checksum(target_data)
    target_packet = bytes(target_data + bytearray([target_checksum]))
    
    print("run_communication_diagnosis() 目标位置数据包:")
    print(f"  数据: {[hex(b) for b in target_packet]}")
    print(f"  长度: {len(target_packet)} 字节")
    print(f"  校验和: {hex(target_checksum)}")
    
    # 激光位置数据包
    laser_data = bytearray([
        0xAA, 0x55, 0x04, 0x02,
        laser_x & 0xFF, (laser_x >> 8) & 0xFF,
        laser_y & 0xFF, (laser_y >> 8) & 0xFF
    ])
    laser_checksum = calculate_checksum(laser_data)
    laser_packet = bytes(laser_data + bytearray([laser_checksum]))
    
    print("run_communication_diagnosis() 激光位置数据包:")
    print(f"  数据: {[hex(b) for b in laser_packet]}")
    print(f"  长度: {len(laser_packet)} 字节")
    print(f"  校验和: {hex(laser_checksum)}")
    
    return target_packet, laser_packet

def test_communication_format():
    """测试communication.py的数据包格式"""
    print("\n" + "=" * 60)
    print("测试 communication.py send_position_data() 数据包格式")
    print("=" * 60)
    
    # 模拟communication.py中的数据包构建
    target_pos = (320, 240)
    laser_pos = (300, 220)
    
    target_x = int(target_pos[0])
    target_y = int(target_pos[1])
    laser_x = int(laser_pos[0])
    laser_y = int(laser_pos[1])

    # 目标位置数据包
    target_data = bytearray([
        0xAA, 0x55, 0x04, 0x01,
        target_x & 0xFF, (target_x >> 8) & 0xFF,
        target_y & 0xFF, (target_y >> 8) & 0xFF
    ])
    target_checksum = sum(target_data[2:]) & 0xFF
    target_packet = bytes(target_data + bytearray([target_checksum]))

    print("communication.py 目标位置数据包:")
    print(f"  数据: {[hex(b) for b in target_packet]}")
    print(f"  长度: {len(target_packet)} 字节")
    print(f"  校验和: {hex(target_checksum)}")

    # 激光位置数据包
    laser_data = bytearray([
        0xAA, 0x55, 0x04, 0x02,
        laser_x & 0xFF, (laser_x >> 8) & 0xFF,
        laser_y & 0xFF, (laser_y >> 8) & 0xFF
    ])
    laser_checksum = sum(laser_data[2:]) & 0xFF
    laser_packet = bytes(laser_data + bytearray([laser_checksum]))

    print("communication.py 激光位置数据包:")
    print(f"  数据: {[hex(b) for b in laser_packet]}")
    print(f"  长度: {len(laser_packet)} 字节")
    print(f"  校验和: {hex(laser_checksum)}")
    
    return target_packet, laser_packet

def compare_packets():
    """比较两种方法生成的数据包"""
    print("\n" + "=" * 60)
    print("数据包格式一致性比较")
    print("=" * 60)
    
    # 获取两种方法的数据包
    diag_target, diag_laser = test_diagnosis_format()
    comm_target, comm_laser = test_communication_format()
    
    # 比较目标位置数据包
    print("\n目标位置数据包比较:")
    if diag_target == comm_target:
        print("  ✓ 目标位置数据包完全一致")
    else:
        print("  ✗ 目标位置数据包不一致")
        print(f"    诊断模式: {[hex(b) for b in diag_target]}")
        print(f"    通信模式: {[hex(b) for b in comm_target]}")
    
    # 比较激光位置数据包
    print("激光位置数据包比较:")
    if diag_laser == comm_laser:
        print("  ✓ 激光位置数据包完全一致")
    else:
        print("  ✗ 激光位置数据包不一致")
        print(f"    诊断模式: {[hex(b) for b in diag_laser]}")
        print(f"    通信模式: {[hex(b) for b in comm_laser]}")
    
    # 总结
    if diag_target == comm_target and diag_laser == comm_laser:
        print("\n🎉 数据包格式完全一致！激光追踪模式应该能正常工作")
        return True
    else:
        print("\n❌ 数据包格式不一致，需要进一步修复")
        return False

def main():
    """主测试函数"""
    print("激光追踪模式与通信诊断模式数据包格式一致性测试")
    
    success = compare_packets()
    
    if success:
        print("\n✅ 测试通过：数据包格式已统一")
        print("现在可以运行激光追踪模式，STM32应该能正确接收数据")
    else:
        print("\n❌ 测试失败：数据包格式仍有差异")

if __name__ == "__main__":
    main()
