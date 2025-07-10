"""
数据包格式测试脚本
验证MaixCam发送的数据包格式是否符合STM32期望
"""

def test_packet_format():
    """测试数据包格式"""
    
    # 模拟数据
    target_x, target_y = 320, 240
    laser_x, laser_y = 300, 220
    
    print("=" * 60)
    print("数据包格式测试")
    print("=" * 60)
    
    # 目标位置数据包
    print("1. 目标位置数据包:")
    target_payload = bytes([
        0x04,  # 数据长度（4字节坐标数据）
        0x01,  # 命令：目标位置
        target_x & 0xFF, (target_x >> 8) & 0xFF,  # X坐标（小端）
        target_y & 0xFF, (target_y >> 8) & 0xFF   # Y坐标（小端）
    ])
    checksum = sum(target_payload) & 0xFF
    target_packet = bytes([0xAA, 0x55]) + target_payload + bytes([checksum])
    
    print(f"  原始数据: target_x={target_x}, target_y={target_y}")
    print(f"  数据包: {[hex(b) for b in target_packet]}")
    print(f"  长度: {len(target_packet)} 字节")
    print(f"  校验和: {hex(checksum)}")
    
    # 验证数据包解析
    print("  解析验证:")
    if target_packet[0] == 0xAA and target_packet[1] == 0x55:
        print("    ✓ 帧头正确")
    else:
        print("    ✗ 帧头错误")
    
    length = target_packet[2]
    command = target_packet[3]
    data = target_packet[4:4+length]  # 数据部分（长度字段指定的纯数据）
    received_checksum = target_packet[4+length]

    print(f"    长度: {length}")
    print(f"    命令: {hex(command)}")
    print(f"    数据: {[hex(b) for b in data]}")
    print(f"    数据长度: {len(data)}")

    # 验证校验和（从长度字节到数据结束，包含命令字节）
    calculated_checksum = sum(target_packet[2:4+length]) & 0xFF
    if received_checksum == calculated_checksum:
        print(f"    ✓ 校验和正确: {hex(calculated_checksum)}")
    else:
        print(f"    ✗ 校验和错误: 期望{hex(calculated_checksum)}, 收到{hex(received_checksum)}")

    # 解析坐标
    if len(data) >= 4:
        parsed_x = data[0] | (data[1] << 8)
        parsed_y = data[2] | (data[3] << 8)
    else:
        print(f"    ✗ 数据长度不足: {len(data)} < 4")
        return
    print(f"    解析坐标: x={parsed_x}, y={parsed_y}")
    
    if parsed_x == target_x and parsed_y == target_y:
        print("    ✓ 坐标解析正确")
    else:
        print("    ✗ 坐标解析错误")
    
    print()
    
    # 激光位置数据包
    print("2. 激光位置数据包:")
    laser_data = bytes([
        0x04, 0x02,  # 长度和命令
        laser_x & 0xFF, (laser_x >> 8) & 0xFF,
        laser_y & 0xFF, (laser_y >> 8) & 0xFF
    ])
    checksum = sum(laser_data) & 0xFF
    laser_packet = bytes([0xAA, 0x55]) + laser_data + bytes([checksum])
    
    print(f"  原始数据: laser_x={laser_x}, laser_y={laser_y}")
    print(f"  数据包: {[hex(b) for b in laser_packet]}")
    print(f"  长度: {len(laser_packet)} 字节")
    print(f"  校验和: {hex(checksum)}")
    
    print()
    
    # STM32期望格式说明
    print("3. STM32期望的数据包格式:")
    print("  [0xAA, 0x55, Length, Command, Data..., Checksum]")
    print("  - 帧头: 0xAA 0x55")
    print("  - 长度: 数据字节数（包含命令字节）")
    print("  - 命令: 0x01=目标位置, 0x02=激光位置")
    print("  - 数据: 坐标数据（小端格式）")
    print("  - 校验和: 从长度字节开始的所有字节之和的低8位")
    
    print()
    print("=" * 60)
    print("测试完成")
    print("=" * 60)

if __name__ == "__main__":
    test_packet_format()
