"""
通信模块
实现与STM32的串口通信协议
"""

import struct
import time
from maix import uart

class Communication:
    """通信管理器"""

    # 命令定义
    CMD_TARGET_POSITION = 0x01
    CMD_LASER_POSITION = 0x02
    CMD_PID_PARAMS = 0x03
    CMD_SYSTEM_STATUS = 0x04
    CMD_CALIBRATION = 0x05

    def __init__(self, config):
        """初始化通信模块"""
        self.config = config
        self.uart_port = None
        self.is_connected = False

        # 协议参数
        self.header = config.protocol_header  # [0xAA, 0x55]
        self.max_packet_size = config.max_packet_size

        # 统计信息
        self.sent_packets = 0
        self.failed_packets = 0

        # 初始化串口
        self.init_uart()

    def init_uart(self):
        """初始化串口连接"""
        try:
            self.uart_port = uart.UART(
                self.config.uart_port,
                self.config.uart_baudrate,
                8, 0, 1,
                timeout=self.config.uart_timeout
            )
            self.is_connected = True
            print(f"串口连接成功: {self.config.uart_port}@{self.config.uart_baudrate}")
        except Exception as e:
            print(f"串口连接失败: {e}")
            self.is_connected = False

    def calculate_checksum(self, data):
        """计算校验和"""
        return sum(data) & 0xFF

    def create_packet(self, cmd, data=None):
        """创建数据包"""
        if data is None:
            data = []

        # 构建数据包
        packet = []
        packet.extend(self.header)  # 帧头 [0xAA, 0x55]
        packet.append(len(data))    # 数据长度
        packet.append(cmd)          # 命令
        packet.extend(data)         # 数据

        # 计算校验和
        checksum = self.calculate_checksum(packet[2:])  # 从长度字段开始计算
        packet.append(checksum)

        return bytes(packet)

    def send_packet(self, packet):
        """发送数据包"""
        if not self.is_connected or not self.uart_port:
            print("串口未连接，无法发送数据")
            self.failed_packets += 1
            return False

        try:
            self.uart_port.write(packet)
            self.sent_packets += 1
            return True
        except Exception as e:
            print(f"数据发送失败: {e}")
            self.failed_packets += 1
            return False

    def send_position_data(self, target_pos, laser_pos):
        """发送位置数据"""
        if not target_pos or not laser_pos:
            return False

        # 打包位置数据 (每个坐标2字节，置信度2字节，时间戳2字节)
        data = []

        # 目标位置数据 (8字节)
        data.extend(struct.pack('<H', int(target_pos[0])))  # X坐标
        data.extend(struct.pack('<H', int(target_pos[1])))  # Y坐标
        data.extend(struct.pack('<H', 100))                 # 置信度 (固定100)
        data.extend(struct.pack('<H', int(time.time() * 1000) & 0xFFFF))  # 时间戳

        # 激光位置数据 (8字节)
        data.extend(struct.pack('<H', int(laser_pos[0])))   # X坐标
        data.extend(struct.pack('<H', int(laser_pos[1])))   # Y坐标
        data.extend(struct.pack('<H', 100))                 # 置信度 (固定100)
        data.extend(struct.pack('<H', int(time.time() * 1000) & 0xFFFF))  # 时间戳

        # 创建并发送数据包
        packet = self.create_packet(self.CMD_TARGET_POSITION, data)
        return self.send_packet(packet)

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
            # 设置超时
            if timeout:
                original_timeout = self.uart_port.timeout
                self.uart_port.timeout = timeout

            # 读取数据
            data = self.uart_port.read()

            # 恢复原始超时设置
            if timeout:
                self.uart_port.timeout = original_timeout

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
            if self.uart_port:
                self.uart_port.close()
                self.uart_port = None
            self.is_connected = False
            print("串口连接已关闭")
        except Exception as e:
            print(f"关闭串口时发生错误: {e}")

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