"""
激光追踪系统配置模块
包含所有系统参数的配置
"""

class Config:
    """系统配置类"""

    def __init__(self):
        """初始化配置参数"""

        # 摄像头配置
        self.camera_width = 640
        self.camera_height = 480
        self.camera_fps = 30

        # 显示配置
        self.display_width = 640
        self.display_height = 480

        # 红色目标检测参数 (LAB色彩空间)
        self.red_target_threshold = [
            [0, 60, 0, 127, -128, -35]  # 红色LAB阈值
        ]
        self.red_target_min_pixels = 100
        self.red_target_min_area = 200

        # 绿色激光检测参数 (LAB色彩空间)
        self.green_laser_threshold = [
            [0, 80, -120, -10, 0, 30]  # 绿色LAB阈值
        ]
        self.green_laser_min_pixels = 30
        self.green_laser_min_area = 60

        # 图像矫正参数
        self.correction_enabled = True
        self.corner_points = []  # 四个角点坐标，在标定时设置

        # 通信配置
        self.uart_port = "/dev/ttyS0"  # 默认串口
        self.uart_baudrate = 115200
        self.uart_timeout = 2000  # 毫秒，与官方例程保持一致

        # 协议配置
        self.protocol_header = [0xAA, 0x55]
        self.max_packet_size = 64

        # 追踪参数
        self.tracking_enabled = True
        self.max_tracking_distance = 100  # 最大追踪距离(像素)
        self.tracking_confidence_threshold = 0.7

        # 调试配置
        self.debug_mode = True
        self.show_detection_info = True
        self.save_debug_images = False

        # 性能配置
        self.max_fps = 30
        self.processing_timeout = 0.1  # 处理超时时间(秒)

        print("配置模块初始化完成")

    def update_red_target_threshold(self, threshold):
        """更新红色目标检测阈值"""
        self.red_target_threshold = threshold
        print(f"红色目标阈值已更新: {threshold}")

    def update_green_laser_threshold(self, threshold):
        """更新绿色激光检测阈值"""
        self.green_laser_threshold = threshold
        print(f"绿色激光阈值已更新: {threshold}")

    def set_corner_points(self, points):
        """设置矫正角点"""
        if len(points) == 4:
            self.corner_points = points
            print(f"矫正角点已设置: {points}")
            return True
        else:
            print("错误: 需要4个角点")
            return False

    def enable_correction(self, enabled=True):
        """启用/禁用图像矫正"""
        self.correction_enabled = enabled
        status = "启用" if enabled else "禁用"
        print(f"图像矫正已{status}")

    def set_debug_mode(self, enabled=True):
        """设置调试模式"""
        self.debug_mode = enabled
        status = "启用" if enabled else "禁用"
        print(f"调试模式已{status}")

    def get_detection_params(self):
        """获取检测参数字典"""
        return {
            'red_threshold': self.red_target_threshold,
            'red_min_pixels': self.red_target_min_pixels,
            'red_min_area': self.red_target_min_area,
            'green_threshold': self.green_laser_threshold,
            'green_min_pixels': self.green_laser_min_pixels,
            'green_min_area': self.green_laser_min_area
        }

    def get_communication_params(self):
        """获取通信参数字典"""
        return {
            'port': self.uart_port,
            'baudrate': self.uart_baudrate,
            'timeout': self.uart_timeout,
            'header': self.protocol_header,
            'max_packet_size': self.max_packet_size
        }

    def print_config(self):
        """打印当前配置"""
        print("\n" + "=" * 40)
        print("当前系统配置:")
        print("=" * 40)
        print(f"摄像头: {self.camera_width}x{self.camera_height}@{self.camera_fps}fps")
        print(f"显示器: {self.display_width}x{self.display_height}")
        print(f"串口: {self.uart_port}@{self.uart_baudrate}")
        print(f"图像矫正: {'启用' if self.correction_enabled else '禁用'}")
        print(f"调试模式: {'启用' if self.debug_mode else '禁用'}")
        print(f"追踪: {'启用' if self.tracking_enabled else '禁用'}")
        print("=" * 40)