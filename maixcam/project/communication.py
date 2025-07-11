"""
通信模块
实现与STM32的串口通信协议
参考comm_protocol_yolov5.py的实现方法
"""

import struct
import time

class Communication:
    """通信管理器 - 基于MaixPy CommProtocol实现"""

    # 命令定义
    CMD_TARGET_POSITION = 0x01
    CMD_LASER_POSITION = 0x02
    CMD_PID_PARAMS = 0x03
    CMD_SYSTEM_STATUS = 0x04
    CMD_CALIBRATION = 0x05

    def __init__(self, config):
        """初始化通信模块"""
        self.config = config
        self.comm_protocol = None
        self.uart_port = None
        self.is_connected = False

        # 协议头部
        self.header = config.protocol_header  # [0xAA, 0x55]

        # 统计信息
        self.sent_packets = 0
        self.failed_packets = 0

        # 初始化通信协议
        self.init_comm_protocol()

    def init_comm_protocol(self):
        """初始化通信协议"""
        # 使用官方UART API格式
        try:
            from maix import uart

            # 从配置中获取串口设备
            device = self.config.uart_port

            # 使用官方API格式初始化UART
            self.uart_port = uart.UART(device, self.config.uart_baudrate)
            self.is_connected = True
            print(f"UART初始化成功: {device}@{self.config.uart_baudrate}")

        except Exception as e:
            print(f"UART初始化失败: {e}")
            self.is_connected = False



    def calculate_checksum(self, data):
        """计算校验和"""
        return sum(data) & 0xFF

    def create_packet(self, cmd, data=None):
        """创建数据包"""
        if data is None:
            data = []

        # 1. 构建数据包的核心部分（长度、命令、数据）
        payload = bytearray()
        payload.append(len(data))
        payload.append(cmd)
        payload.extend(data)

        # 2. 计算校验和
        checksum = self.calculate_checksum(payload)

        # 3. 构建完整的数据包
        packet = bytearray(self.header) # 从帧头开始
        packet.extend(payload)
        packet.append(checksum) # 在末尾追加校验和

        return bytes(packet)

    def send_packet(self, packet):
        """发送数据包"""
        if not self.is_connected or not self.uart_port:
            print("UART未连接，无法发送数据")
            self.failed_packets += 1
            return False

        try:
            # 使用官方API发送字节数据
            self.uart_port.write(packet)
            self.sent_packets += 1

            if self.config.debug_mode:
                print(f"发送数据包: {[hex(b) for b in packet]}")

            return True
        except Exception as e:
            print(f"数据发送失败: {e}")
            self.failed_packets += 1
            return False



    def encode_position_data(self, target_pos, laser_pos):
        """编码位置数据为字节流"""
        # 参考comm_protocol_yolov5.py的encode_objs方法
        # 格式: target_x(2B) + target_y(2B) + laser_x(2B) + laser_y(2B) + confidence(2B) + timestamp(2B)
        data = struct.pack("<hhhhHH",
                          int(target_pos[0]), int(target_pos[1]),  # 目标位置
                          int(laser_pos[0]), int(laser_pos[1]),    # 激光位置
                          100,  # 置信度 (固定100)
                          int(time.time() * 1000) & 0xFFFF)       # 时间戳 (低16位)
        return data

    def send_position_data(self, target_pos, laser_pos):
        """发送位置数据 - 使用与run_communication_diagnosis()相同的格式"""
        if not target_pos or not laser_pos:
            return False
        try:
            # 使用与run_communication_diagnosis()完全相同的数据包格式
            target_x = int(target_pos[0])
            target_y = int(target_pos[1])
            laser_x = int(laser_pos[0])
            laser_y = int(laser_pos[1])

            # 1. 发送目标位置 - 与run_communication_diagnosis()格式完全一致
            target_data = bytearray([
                0xAA, 0x55, 0x04, 0x01,  # 帧头 + 长度 + 命令
                target_x & 0xFF, (target_x >> 8) & 0xFF,  # X坐标（小端）
                target_y & 0xFF, (target_y >> 8) & 0xFF   # Y坐标（小端）
            ])
            # 校验和计算：从索引2（长度字段）开始到数据末尾
            target_checksum = sum(target_data[2:]) & 0xFF
            target_packet = bytes(target_data + bytearray([target_checksum]))

            # 2. 发送激光位置 - 与run_communication_diagnosis()格式完全一致
            laser_data = bytearray([
                0xAA, 0x55, 0x04, 0x02,  # 帧头 + 长度 + 命令
                laser_x & 0xFF, (laser_x >> 8) & 0xFF,    # X坐标（小端）
                laser_y & 0xFF, (laser_y >> 8) & 0xFF     # Y坐标（小端）
            ])
            # 校验和计算：从索引2（长度字段）开始到数据末尾
            laser_checksum = sum(laser_data[2:]) & 0xFF
            laser_packet = bytes(laser_data + bytearray([laser_checksum]))

            # 发送两个数据包
            success1 = self.send_packet(target_packet)
            success2 = self.send_packet(laser_packet)

            if self.config.debug_mode and (success1 or success2):
                print(f"发送位置数据 - 目标: {target_pos}, 激光: {laser_pos}")
                print(f"校验和 - 目标: {target_checksum}, 激光: {laser_checksum}")

            return success1 and success2

        except Exception as e:
            print(f"发送位置数据异常: {e}")
            return False

    def send_pid_params(self, kp_h, ki_h, kd_h, kp_v, ki_v, kd_v):
        """发送PID参数"""
        # 将浮点数转换为整数 (乘以100保留两位小数)
        data = []
        data.extend(struct.pack('<H', int(kp_h * 100)))
        data.extend(struct.pack('<H', int(ki_h * 100)))
        data.extend(struct.pack('<H', int(kd_h * 100)))
        data.extend(struct.pack('<H', int(kp_v * 100)))
        data.extend(struct.pack('<H', int(ki_v * 100)))
        data.extend(struct.pack('<H', int(kd_v * 100)))

        packet = self.create_packet(self.CMD_PID_PARAMS, data)
        return self.send_packet(packet)

    def send_calibration_data(self, corner_points):
        """发送标定数据"""
        if len(corner_points) != 4:
            print("标定数据错误：需要4个角点")
            return False

        data = []
        for point in corner_points:
            data.extend(struct.pack('<H', int(point[0])))  # X坐标
            data.extend(struct.pack('<H', int(point[1])))  # Y坐标

        packet = self.create_packet(self.CMD_CALIBRATION, data)
        return self.send_packet(packet)

    def request_system_status(self):
        """请求系统状态"""
        packet = self.create_packet(self.CMD_SYSTEM_STATUS)
        return self.send_packet(packet)

    def receive_data(self, timeout=None):
        """接收数据"""
        if not self.is_connected or not self.uart_port:
            return None

        try:
            # 使用官方API读取数据，timeout单位为毫秒
            if timeout is None:
                timeout = self.config.uart_timeout

            data = self.uart_port.read(timeout=timeout)
            return data
        except Exception as e:
            print(f"数据接收失败: {e}")
            return None

    def parse_received_packet(self, data):
        """解析接收到的数据包"""
        if not data or len(data) < 5:  # 最小包长度
            return None

        # 检查帧头
        if data[0] != self.header[0] or data[1] != self.header[1]:
            print("数据包帧头错误")
            return None

        # 解析包结构
        length = data[2]
        cmd = data[3]
        payload = data[4:4+length]

        if len(data) < 4 + length + 1:  # 检查包长度
            print("数据包长度不足")
            return None

        checksum = data[4+length]

        # 验证校验和
        calculated_checksum = self.calculate_checksum(data[2:4+length])
        if checksum != calculated_checksum:
            print(f"校验和错误: 期望{calculated_checksum}, 收到{checksum}")
            return None

        return {
            'cmd': cmd,
            'data': payload,
            'length': length
        }

    def close(self):
        """关闭通信连接"""
        try:
            if hasattr(self, 'uart_port') and self.uart_port:
                # 官方API会自动处理资源释放
                del self.uart_port
                self.uart_port = None
            self.is_connected = False
            print("通信连接已关闭")
        except Exception as e:
            print(f"关闭通信时发生错误: {e}")

    def get_communication_stats(self):
        """获取通信统计信息"""
        return {
            'connected': self.is_connected,
            'sent_packets': self.sent_packets,
            'failed_packets': self.failed_packets,
            'success_rate': (self.sent_packets / (self.sent_packets + self.failed_packets) * 100)
                           if (self.sent_packets + self.failed_packets) > 0 else 0
        }

    def test_connection(self):
        """测试连接"""
        if not self.is_connected:
            print("串口未连接")
            return False

        # 发送测试数据包
        test_packet = self.create_packet(self.CMD_SYSTEM_STATUS)
        success = self.send_packet(test_packet)

        if success:
            print("连接测试成功")
        else:
            print("连接测试失败")

        return success