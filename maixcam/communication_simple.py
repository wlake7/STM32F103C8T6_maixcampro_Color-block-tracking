"""
简化版通信模块
专门解决串口连接问题，参考comm_protocol_yolov5.py
"""

import struct
import time
import os

class SimpleCommunication:
    """简化版通信管理器"""

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
        self.use_comm_protocol = True

        # 统计信息
        self.sent_packets = 0
        self.failed_packets = 0

        # 初始化通信
        self.init_communication()

    def init_communication(self):
        """初始化通信 - 优先使用CommProtocol"""
        print("🔧 初始化通信模块...")
        
        # 方法1: 尝试使用CommProtocol
        if self._try_comm_protocol():
            return
        
        # 方法2: 尝试使用UART
        if self._try_uart():
            return
        
        # 方法3: 都失败了
        print("❌ 所有通信方式都失败了")
        self.is_connected = False

    def _try_comm_protocol(self):
        """尝试使用CommProtocol"""
        try:
            from maix import comm
            print("📡 尝试使用CommProtocol...")
            
            self.comm_protocol = comm.CommProtocol(buff_size=1024)
            self.is_connected = True
            self.use_comm_protocol = True
            print("✅ CommProtocol初始化成功")
            return True
            
        except Exception as e:
            print(f"⚠️ CommProtocol初始化失败: {e}")
            return False

    def _try_uart(self):
        """尝试使用UART"""
        try:
            from maix import uart
            print("📡 尝试使用UART...")
            
            # 自动检测可用串口
            uart_devices = ["/dev/ttyS0", "/dev/ttyS1", "/dev/ttyS2", "/dev/ttyUSB0"]
            
            for device in uart_devices:
                if os.path.exists(device):
                    try:
                        print(f"🔍 测试串口: {device}")
                        self.uart_port = uart.UART(
                            device,
                            self.config.uart_baudrate,
                            8, 0, 1,
                            timeout=self.config.uart_timeout
                        )
                        self.is_connected = True
                        self.use_comm_protocol = False
                        print(f"✅ UART初始化成功: {device}@{self.config.uart_baudrate}")
                        
                        # 更新配置文件中的串口设置
                        self._update_uart_config(device)
                        return True
                        
                    except Exception as e:
                        print(f"❌ {device} 失败: {e}")
                        continue
            
            print("❌ 所有UART设备都不可用")
            return False
            
        except Exception as e:
            print(f"❌ UART模块导入失败: {e}")
            return False

    def _update_uart_config(self, device):
        """更新配置文件中的串口设置"""
        try:
            # 更新内存中的配置
            self.config.uart_port = device
            print(f"📝 已更新串口配置: {device}")
        except Exception as e:
            print(f"⚠️ 配置更新失败: {e}")

    def send_position_data(self, target_pos, laser_pos):
        """发送位置数据"""
        if not self.is_connected:
            print("❌ 通信未连接，无法发送数据")
            self.failed_packets += 1
            return False

        if not target_pos or not laser_pos:
            return False

        try:
            if self.use_comm_protocol and self.comm_protocol:
                return self._send_via_comm_protocol(target_pos, laser_pos)
            elif self.uart_port:
                return self._send_via_uart(target_pos, laser_pos)
            else:
                print("❌ 没有可用的通信方式")
                return False
                
        except Exception as e:
            print(f"❌ 发送位置数据异常: {e}")
            self.failed_packets += 1
            return False

    def _send_via_comm_protocol(self, target_pos, laser_pos):
        """通过CommProtocol发送数据"""
        try:
            from maix.err import Err
            
            # 编码位置数据
            data = self._encode_position_data(target_pos, laser_pos)
            
            # 发送数据
            result = self.comm_protocol.report(self.CMD_TARGET_POSITION, data)
            
            if result == Err.ERR_NONE:
                self.sent_packets += 1
                return True
            else:
                print(f"❌ CommProtocol发送失败: {result}")
                self.failed_packets += 1
                return False
                
        except Exception as e:
            print(f"❌ CommProtocol发送异常: {e}")
            self.failed_packets += 1
            return False

    def _send_via_uart(self, target_pos, laser_pos):
        """通过UART发送数据"""
        try:
            # 创建数据包
            packet = self._create_uart_packet(target_pos, laser_pos)
            
            # 发送数据
            self.uart_port.write(packet)
            self.sent_packets += 1
            return True
            
        except Exception as e:
            print(f"❌ UART发送异常: {e}")
            self.failed_packets += 1
            return False

    def _encode_position_data(self, target_pos, laser_pos):
        """编码位置数据为字节流"""
        # 格式: target_x(2B) + target_y(2B) + laser_x(2B) + laser_y(2B) + confidence(2B) + timestamp(2B)
        data = struct.pack("<hhhhHH", 
                          int(target_pos[0]), int(target_pos[1]),  # 目标位置
                          int(laser_pos[0]), int(laser_pos[1]),    # 激光位置
                          100,  # 置信度
                          int(time.time() * 1000) & 0xFFFF)       # 时间戳
        return data

    def _create_uart_packet(self, target_pos, laser_pos):
        """创建UART数据包"""
        # 编码数据
        data = self._encode_position_data(target_pos, laser_pos)
        
        # 构建数据包: [0xAA, 0x55, length, cmd, data..., checksum]
        packet = bytearray()
        packet.extend([0xAA, 0x55])  # 帧头
        packet.append(len(data))     # 数据长度
        packet.append(self.CMD_TARGET_POSITION)  # 命令
        packet.extend(data)          # 数据
        
        # 计算校验和
        checksum = sum(packet[2:]) & 0xFF
        packet.append(checksum)
        
        return bytes(packet)

    def test_connection(self):
        """测试连接"""
        if not self.is_connected:
            print("❌ 通信未连接")
            return False

        try:
            # 发送测试数据
            test_pos = (320, 240)
            result = self.send_position_data(test_pos, test_pos)
            
            if result:
                print("✅ 连接测试成功")
            else:
                print("❌ 连接测试失败")
                
            return result
            
        except Exception as e:
            print(f"❌ 连接测试异常: {e}")
            return False

    def get_stats(self):
        """获取统计信息"""
        return {
            'connected': self.is_connected,
            'method': 'CommProtocol' if self.use_comm_protocol else 'UART',
            'sent_packets': self.sent_packets,
            'failed_packets': self.failed_packets,
            'success_rate': (self.sent_packets / (self.sent_packets + self.failed_packets) * 100)
                           if (self.sent_packets + self.failed_packets) > 0 else 0
        }

    def close(self):
        """关闭通信连接"""
        try:
            if self.comm_protocol:
                self.comm_protocol = None
            if self.uart_port:
                self.uart_port.close()
                self.uart_port = None
            self.is_connected = False
            print("✅ 通信连接已关闭")
        except Exception as e:
            print(f"⚠️ 关闭通信时发生错误: {e}")

# 兼容性别名
Communication = SimpleCommunication
