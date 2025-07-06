"""
激光追踪系统主模块
基于现有的图像处理功能实现红色色块和绿色激光的追踪
"""

from maix import camera, display, image, app, time
from image_processor import ImageProcessor
from communication import Communication
import math

class LaserTracker:
    """激光追踪主控制器"""

    def __init__(self, config):
        """初始化激光追踪器"""
        self.config = config

        # 初始化图像处理器
        self.image_processor = ImageProcessor(config)
        print("图像处理器初始化完成")

        # 初始化通信模块
        self.communication = Communication(config)
        print("通信模块初始化完成")

        # 追踪状态
        self.tracking_active = False
        self.last_target_pos = None
        self.last_laser_pos = None
        self.tracking_start_time = None

        # 性能统计
        self.frame_count = 0
        self.fps_start_time = time.time()
        self.current_fps = 0

        print("激光追踪器初始化完成")

    def calibrate_system(self):
        """系统标定"""
        print("开始系统标定...")

        # 四角标定
        if not self.image_processor.calibrate_corners():
            print("四角标定失败")
            return False

        print("系统标定完成")
        return True

    def start_tracking(self):
        """开始激光追踪"""
        print("开始激光追踪...")
        self.tracking_active = True
        self.tracking_start_time = time.time()

        try:
            while not app.need_exit() and self.tracking_active:
                # 处理一帧
                self.process_frame()

                # 更新FPS统计
                self.update_fps_stats()

        except KeyboardInterrupt:
            print("用户中断追踪")
        except Exception as e:
            print(f"追踪过程中发生错误: {e}")
            import traceback
            traceback.print_exc()
        finally:
            self.stop_tracking()

    def process_frame(self):
        """处理单帧图像"""
        # 获取图像
        img = self.image_processor.capture_image()
        if img is None:
            return

        # 应用图像矫正
        corrected_img = self.image_processor.apply_correction(img)

        # 检测红色目标
        red_target = self.image_processor.detect_red_target(corrected_img)

        # 检测绿色激光
        green_laser = self.image_processor.detect_green_laser(corrected_img)

        # 计算偏移并发送控制命令
        if red_target and green_laser:
            self.process_tracking_data(red_target, green_laser)

        # 显示结果
        self.display_tracking_result(corrected_img, red_target, green_laser)

        # 更新历史位置
        self.last_target_pos = red_target
        self.last_laser_pos = green_laser

    def process_tracking_data(self, target_pos, laser_pos):
        """处理追踪数据并发送控制命令"""
        # 计算偏移
        offset = self.image_processor.calculate_offset(target_pos, laser_pos)

        # 发送位置数据到STM32
        self.communication.send_position_data(target_pos, laser_pos)

        if self.config.debug_mode:
            print(f"目标位置: {target_pos}, 激光位置: {laser_pos}, 偏移: {offset}")

    def display_tracking_result(self, img, red_target, green_laser):
        """显示追踪结果"""
        # 绘制红色目标
        if red_target:
            img.draw_circle(red_target[0], red_target[1], 10, image.COLOR_RED, 3)
            img.draw_string(red_target[0] + 15, red_target[1] - 10,
                          "Target", image.COLOR_RED, 1.5)

        # 绘制绿色激光
        if green_laser:
            img.draw_circle(green_laser[0], green_laser[1], 8, image.COLOR_GREEN, 3)
            img.draw_string(green_laser[0] + 15, green_laser[1] - 10,
                          "Laser", image.COLOR_GREEN, 1.5)

        # 绘制连接线
        if red_target and green_laser:
            img.draw_line(red_target[0], red_target[1],
                         green_laser[0], green_laser[1],
                         image.COLOR_YELLOW, 2)

        # 显示状态信息
        self.draw_status_info(img)

        # 显示图像
        self.image_processor.display_image(img)

    def draw_status_info(self, img):
        """绘制状态信息"""
        y_offset = 10
        line_height = 25

        # 追踪状态
        status = "追踪中" if self.tracking_active else "已停止"
        img.draw_string(10, y_offset, f"状态: {status}", image.COLOR_WHITE, 1.5)
        y_offset += line_height

        # FPS信息
        img.draw_string(10, y_offset, f"FPS: {self.current_fps:.1f}", image.COLOR_WHITE, 1.5)
        y_offset += line_height

        # 运行时间
        if self.tracking_start_time:
            runtime = time.time() - self.tracking_start_time
            img.draw_string(10, y_offset, f"运行时间: {runtime:.1f}s", image.COLOR_WHITE, 1.5)
            y_offset += line_height

        # 检测状态
        target_status = "✓" if self.last_target_pos else "✗"
        laser_status = "✓" if self.last_laser_pos else "✗"
        img.draw_string(10, y_offset, f"目标: {target_status} 激光: {laser_status}",
                       image.COLOR_WHITE, 1.5)

    def update_fps_stats(self):
        """更新FPS统计"""
        self.frame_count += 1
        current_time = time.time()

        if current_time - self.fps_start_time >= 1.0:  # 每秒更新一次
            self.current_fps = self.frame_count / (current_time - self.fps_start_time)
            self.frame_count = 0
            self.fps_start_time = current_time

    def stop_tracking(self):
        """停止追踪"""
        print("停止激光追踪...")
        self.tracking_active = False

        # 关闭通信
        self.communication.close()

        # 关闭图像处理器
        self.image_processor.close()

        print("激光追踪已停止")

    def set_tracking_parameters(self, red_threshold=None, green_threshold=None):
        """设置追踪参数"""
        if red_threshold:
            self.config.update_red_target_threshold(red_threshold)
            self.image_processor.update_red_threshold(red_threshold)

        if green_threshold:
            self.config.update_green_laser_threshold(green_threshold)
            self.image_processor.update_green_threshold(green_threshold)

    def get_tracking_status(self):
        """获取追踪状态"""
        return {
            'active': self.tracking_active,
            'fps': self.current_fps,
            'target_detected': self.last_target_pos is not None,
            'laser_detected': self.last_laser_pos is not None,
            'runtime': time.time() - self.tracking_start_time if self.tracking_start_time else 0
        }