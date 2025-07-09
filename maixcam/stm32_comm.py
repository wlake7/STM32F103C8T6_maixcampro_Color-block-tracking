"""
STM32通信模块 v2.0
实现与STM32的串口通信协议，支持激光追踪数据传输
"""

import struct
import time
from maix import uart
from typing import Optional, Dict, Any, List

class STM32Communication:
    """STM32通信类"""
    
    def __init__(self, port: str = "/dev/ttyUSB0", baudrate: int = 115200):
        """
        初始化STM32通信
        
        Args:
            port: 串口设备路径
            baudrate: 波特率
        """
        self.port = port
        self.baudrate = baudrate
        self.uart_conn: Optional[uart.UART] = None
        self.is_connected = False
        
        # 协议常量
        self.HEADER1 = 0xAA
        self.HEADER2 = 0x55
        self.CMD_TARGET_POSITION = 0x01
        self.CMD_LASER_POSITION = 0x02
        self.CMD_PID_PARAMS = 0x03
        self.CMD_SYSTEM_STATUS = 0x04
        self.CMD_CALIBRATION = 0x05
        
        # 统计信息
        self.stats = {
            'packets_sent': 0,
            'packets_received': 0,
            'send_errors': 0,
            'receive_errors': 0,
            'connection_attempts': 0,
            'last_send_time': 0
        }
        
        # 自动重连配置
        self.auto_reconnect = True
        self.reconnect_interval = 5.0  # 秒
        self.last_reconnect_attempt = 0
        
        self._connect()
    
    def _connect(self) -> bool:
        """连接串口"""
        self.stats['connection_attempts'] += 1
        
        try:
            if self.uart_conn:
                self.uart_conn.close()
                
            self.uart_conn = uart.UART(
                self.port,
                self.baudrate,
                8, 0, 1,  # 8位数据位，无校验，1位停止位
                timeout=100  # 100ms超时
            )
            
            self.is_connected = True
            print(f"STM32通信连接成功: {self.port}@{self.baudrate}")
            return True
            
        except Exception as e:
            print(f"STM32通信连接失败: {e}")
            self.is_connected = False
            return False
    
    def _auto_reconnect(self) -> bool:
        """自动重连"""
        if not self.auto_reconnect:
            return False
            
        current_time = time.time()
        if (current_time - self.last_reconnect_attempt) < self.reconnect_interval:
            return False
            
        self.last_reconnect_attempt = current_time
        print("尝试自动重连STM32...")
        return self._connect()
    
    def _calculate_checksum(self, data: bytes) -> int:
        """计算校验和"""
        return sum(data) & 0xFF
    
    def _send_packet(self, command: int, data: bytes = b'') -> bool:
        """
        发送数据包
        
        Args:
            command: 命令字节
            data: 数据内容
            
        Returns:
            bool: 发送是否成功
        """
        if not self.is_connected or not self.uart_conn:
            if self.auto_reconnect:
                if not self._auto_reconnect():
                    return False
            else:
                return False
        
        try:
            # 构造数据包
            packet = bytearray()
            packet.append(self.HEADER1)        # 帧头1
            packet.append(self.HEADER2)        # 帧头2
            packet.append(len(data))           # 数据长度
            packet.append(command)             # 命令
            packet.extend(data)                # 数据
            
            # 计算校验和
            checksum = self._calculate_checksum(packet[2:])
            packet.append(checksum)
            
            # 发送数据包
            self.uart_conn.write(bytes(packet))
            
            self.stats['packets_sent'] += 1
            self.stats['last_send_time'] = time.time()
            return True
            
        except Exception as e:
            print(f"发送数据包失败: {e}")
            self.stats['send_errors'] += 1
            self.is_connected = False
            return False
    
    def send_position_data(self, target_x: int, target_y: int, 
                          laser_x: int, laser_y: int, 
                          confidence: int, timestamp: int = 0) -> bool:
        """
        发送位置数据
        
        Args:
            target_x: 目标X坐标
            target_y: 目标Y坐标
            laser_x: 激光X坐标
            laser_y: 激光Y坐标
            confidence: 置信度 (0-100)
            timestamp: 时间戳
            
        Returns:
            bool: 发送是否成功
        """
        try:
            # 限制坐标范围
            target_x = max(-32768, min(32767, target_x))
            target_y = max(-32768, min(32767, target_y))
            laser_x = max(-32768, min(32767, laser_x))
            laser_y = max(-32768, min(32767, laser_y))
            confidence = max(0, min(100, confidence))
            timestamp = timestamp & 0xFFFF
            
            # 打包数据 (小端序)
            data = struct.pack('<hhhhhh', 
                             target_x, target_y, 
                             laser_x, laser_y, 
                             confidence, timestamp)
            
            return self._send_packet(self.CMD_TARGET_POSITION, data)
            
        except Exception as e:
            print(f"发送位置数据失败: {e}")
            return False
    
    def send_pid_params(self, kp_h: float, ki_h: float, kd_h: float,
                       kp_v: float, ki_v: float, kd_v: float) -> bool:
        """
        发送PID参数
        
        Args:
            kp_h: 水平Kp
            ki_h: 水平Ki
            kd_h: 水平Kd
            kp_v: 垂直Kp
            ki_v: 垂直Ki
            kd_v: 垂直Kd
            
        Returns:
            bool: 发送是否成功
        """
        try:
            # 将浮点数转换为整数 (乘以100保留两位小数)
            data = struct.pack('<HHHHHH',
                             int(kp_h * 100), int(ki_h * 100), int(kd_h * 100),
                             int(kp_v * 100), int(ki_v * 100), int(kd_v * 100))
            
            return self._send_packet(self.CMD_PID_PARAMS, data)
            
        except Exception as e:
            print(f"发送PID参数失败: {e}")
            return False
    
    def send_calibration_data(self, calibration_points: List[Dict]) -> bool:
        """
        发送标定数据
        
        Args:
            calibration_points: 标定点列表
            
        Returns:
            bool: 发送是否成功
        """
        try:
            # 简化的标定数据格式
            data = bytearray()
            data.append(len(calibration_points))
            
            for point in calibration_points[:8]:  # 最多8个标定点
                x = max(-32768, min(32767, point.get('x', 0)))
                y = max(-32768, min(32767, point.get('y', 0)))
                data.extend(struct.pack('<hh', x, y))
            
            return self._send_packet(self.CMD_CALIBRATION, bytes(data))
            
        except Exception as e:
            print(f"发送标定数据失败: {e}")
            return False
    
    def request_system_status(self) -> bool:
        """请求系统状态"""
        return self._send_packet(self.CMD_SYSTEM_STATUS)
    
    def is_communication_healthy(self) -> bool:
        """检查通信是否健康"""
        if not self.is_connected:
            return False
            
        # 检查最近是否有成功发送
        current_time = time.time()
        if (current_time - self.stats['last_send_time']) > 10.0:  # 10秒内无发送
            return False
            
        # 检查错误率
        total_attempts = self.stats['packets_sent'] + self.stats['send_errors']
        if total_attempts > 100:
            error_rate = self.stats['send_errors'] / total_attempts
            if error_rate > 0.1:  # 错误率超过10%
                return False
                
        return True
    
    def get_stats(self) -> Dict[str, Any]:
        """获取统计信息"""
        stats = self.stats.copy()
        stats['is_connected'] = self.is_connected
        stats['is_healthy'] = self.is_communication_healthy()
        return stats
    
    def reset_stats(self):
        """重置统计信息"""
        self.stats = {
            'packets_sent': 0,
            'packets_received': 0,
            'send_errors': 0,
            'receive_errors': 0,
            'connection_attempts': self.stats['connection_attempts'],
            'last_send_time': self.stats['last_send_time']
        }
    
    def close(self):
        """关闭连接"""
        self.auto_reconnect = False
        if self.uart_conn:
            try:
                self.uart_conn.close()
            except:
                pass
            self.is_connected = False
            print("STM32通信连接已关闭")
