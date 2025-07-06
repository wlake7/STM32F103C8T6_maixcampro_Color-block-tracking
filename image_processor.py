"""
图像处理模块
基于现有的digit_circle_mapping.py功能，适配激光追踪需求
"""

from maix import camera, display, image, touchscreen, app, time
import math

class ImageProcessor:
    """图像处理器 - 基于现有功能适配激光追踪"""

    def __init__(self, config):
        """初始化图像处理器"""
        self.config = config

        # 初始化硬件
        self.cam = camera.Camera(
            config.camera_width,
            config.camera_height,
            image.Format.FMT_RGB888
        )
        self.disp = display.Display()
        self.touch = touchscreen.TouchScreen()

        # 矫正参数
        self.corner_points = []

        # 检测参数 - 从配置获取
        self.red_target_threshold = config.red_target_threshold
        self.red_target_min_pixels = config.red_target_min_pixels
        self.red_target_min_area = config.red_target_min_area

        self.green_laser_threshold = config.green_laser_threshold
        self.green_laser_min_pixels = config.green_laser_min_pixels
        self.green_laser_min_area = config.green_laser_min_area

        print("图像处理器初始化完成")

    def calibrate_corners(self):
        """四角标定 - 基于现有的标定功能"""
        print("开始四角标定...")
        print("请使用绿色激光笔依次指向四个角点")

        corner_names = ["左上角", "右上角", "右下角", "左下角"]
        self.corner_points = []

        for corner_name in corner_names:
            print(f"请将绿色激光笔移动到{corner_name}，然后触摸屏幕")

            while True:
                img = self.cam.read()

                # 检测绿色激光笔位置
                laser_pos = self.detect_green_laser(img)
                if laser_pos:
                    img.draw_circle(laser_pos[0], laser_pos[1], 5, image.COLOR_GREEN, -1)

                # 显示提示信息
                img.draw_string(10, 10, f"标定{corner_name}", image.COLOR_WHITE, 2)
                img.draw_string(10, 50, "触摸屏幕确认", image.COLOR_WHITE, 1.5)

                self.disp.show(img)

                # 检查触摸事件
                if self.touch.available():
                    touch_data = self.touch.read()
                    if touch_data[2] == 1:  # 按下事件
                        if laser_pos:
                            self.corner_points.append(laser_pos)
                            print(f"{corner_name}标定完成: {laser_pos}")
                            time.sleep(0.5)
                            break
                        else:
                            print("未检测到绿色激光笔，请重新定位")

                if app.need_exit():
                    return False

        print(f"四角标定完成: {self.corner_points}")
        self.config.set_corner_points(self.corner_points)
        return True

    def capture_image(self):
        """捕获图像"""
        try:
            return self.cam.read()
        except Exception as e:
            print(f"图像捕获失败: {e}")
            return None

    def apply_correction(self, img):
        """应用图像矫正 - 基于现有的apply_perspective_correction"""
        if not self.config.correction_enabled or len(self.corner_points) != 4:
            return img

        try:
            # 将角点转换为浮点数列表
            corners = []
            for point in self.corner_points:
                corners.extend([float(point[0]), float(point[1])])

            # 使用rotation_corr进行梯形矫正
            corrected_img = img.rotation_corr(corners=corners)

            # 检查并修复颜色格式问题
            if corrected_img.format() != image.Format.FMT_RGB888:
                print(f"警告: 矫正后图像格式为 {corrected_img.format()}, 尝试转换为RGB888")
                try:
                    # 创建一个新的RGB888格式图像
                    fixed_img = image.Image(corrected_img.width(), corrected_img.height(), image.Format.FMT_RGB888)
                    # 复制像素数据
                    for y in range(corrected_img.height()):
                        for x in range(corrected_img.width()):
                            pixel = corrected_img.get_pixel(x, y)
                            fixed_img.set_pixel(x, y, pixel)
                    return fixed_img
                except:
                    print("颜色格式转换失败，使用原始矫正图像")
                    return corrected_img

            return corrected_img

        except Exception as e:
            print(f"图像矫正失败: {e}")
            return img

    def detect_red_target(self, img):
        """检测红色目标 - 基于现有的blob检测功能"""
        try:
            blobs = img.find_blobs(
                self.red_target_threshold,
                pixels_threshold=self.red_target_min_pixels,
                area_threshold=self.red_target_min_area,
                merge=True
            )

            if blobs:
                # 选择最大的blob作为目标
                largest_blob = max(blobs, key=lambda b: b.pixels())
                return (largest_blob.cx(), largest_blob.cy())

            return None

        except Exception as e:
            print(f"红色目标检测失败: {e}")
            return None

    def detect_green_laser(self, img):
        """检测绿色激光 - 基于现有的detect_red_laser功能"""
        try:
            blobs = img.find_blobs(
                self.green_laser_threshold,
                pixels_threshold=self.green_laser_min_pixels,
                area_threshold=self.green_laser_min_area,
                merge=True
            )

            if blobs:
                # 选择最大的blob作为激光点
                largest_blob = max(blobs, key=lambda b: b.pixels())
                return (largest_blob.cx(), largest_blob.cy())

            return None

        except Exception as e:
            print(f"绿色激光检测失败: {e}")
            return None

    def calculate_offset(self, target_pos, laser_pos):
        """计算目标和激光之间的偏移"""
        if not target_pos or not laser_pos:
            return None

        offset_x = target_pos[0] - laser_pos[0]
        offset_y = target_pos[1] - laser_pos[1]
        distance = math.sqrt(offset_x**2 + offset_y**2)

        return {
            'offset_x': offset_x,
            'offset_y': offset_y,
            'distance': distance,
            'angle': math.atan2(offset_y, offset_x)
        }

    def display_image(self, img):
        """显示图像"""
        try:
            self.disp.show(img)
        except Exception as e:
            print(f"图像显示失败: {e}")

    def update_red_threshold(self, threshold):
        """更新红色目标检测阈值"""
        self.red_target_threshold = threshold
        print(f"红色目标阈值已更新: {threshold}")

    def update_green_threshold(self, threshold):
        """更新绿色激光检测阈值"""
        self.green_laser_threshold = threshold
        print(f"绿色激光阈值已更新: {threshold}")

    def get_image_center(self):
        """获取图像中心点"""
        return (self.config.camera_width // 2, self.config.camera_height // 2)

    def is_position_valid(self, pos):
        """检查位置是否在有效范围内"""
        if not pos:
            return False

        x, y = pos
        return (0 <= x < self.config.camera_width and
                0 <= y < self.config.camera_height)

    def close(self):
        """关闭图像处理器"""
        try:
            # 关闭摄像头
            if hasattr(self, 'cam'):
                del self.cam

            # 关闭显示器
            if hasattr(self, 'disp'):
                del self.disp

            # 关闭触摸屏
            if hasattr(self, 'touch'):
                del self.touch

            print("图像处理器已关闭")
        except Exception as e:
            print(f"关闭图像处理器时发生错误: {e}")

    def get_detection_stats(self):
        """获取检测统计信息"""
        return {
            'red_threshold': self.red_target_threshold,
            'green_threshold': self.green_laser_threshold,
            'corner_points': self.corner_points,
            'correction_enabled': self.config.correction_enabled
        }