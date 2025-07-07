from maix import camera, display, image, nn, app, touchscreen, time
import math

class DigitCircleMappingSystem:
    """数字与黑色圆点映射系统"""
    
    def __init__(self):
        # 初始化摄像头和显示器 - 使用较高分辨率以提供足够的图像质量
        self.cam = camera.Camera(640, 480, image.Format.FMT_RGB888)
        self.disp = display.Display()
        self.touch = touchscreen.TouchScreen()

        # 加载数字检测模型
        self.digit_detector = nn.YOLOv8(model="/root/models/digits_yolo_16.mud", dual_buff=True)

        # 四个角点坐标 (左上, 右上, 右下, 左下)
        self.corner_points = []

        # 数字坐标映射关系 - 存储数字及其矫正后的中心坐标
        self.digit_coordinate_mapping = {}

        # 配置参数
        self.red_laser_threshold = [[50, 100, -20, -5, 5, 25]]  # 红色激光笔LAB阈值（保留用于标定）
        
        # YOLO检测参数 - 优化参数以提高检测效果
        self.yolo_conf_threshold = 0.1  # 大幅降低置信度阈值，提高敏感度
        self.yolo_iou_threshold = 0.3   # 降低IOU阈值，减少重叠检测的抑制

        # 备用参数配置
        self.yolo_conf_threshold_backup = 0.05  # 极低置信度用于调试
        self.yolo_conf_threshold_strict = 0.5   # 严格置信度用于最终确认

        # 激光笔检测参数（保留用于标定）
        self.laser_min_pixels = 10
        self.laser_min_area = 15

        # 映射参数
        self.max_mapping_attempts = 50  # 增加最大尝试次数
        self.min_required_mappings = 16  # 必须找到16个数字映射关系
        
        # 调试显示模式
        self.debug_display_mode = False  # 是否显示YOLO输入的cell_img
        self.debug_grid_index = 5  # 默认显示第6个格子(索引5)
        self.debug_cell_images = []  # 存储所有网格图像用于调试

        print("数字圆点映射系统初始化完成")
        print(f"数字检测模型标签: {self.digit_detector.labels}")

    def toggle_debug_display_mode(self):
        """切换调试显示模式"""
        self.debug_display_mode = not self.debug_display_mode
        mode_text = "开启" if self.debug_display_mode else "关闭"
        print(f"调试显示模式已{mode_text}")
        return self.debug_display_mode

    def set_debug_grid_index(self, index):
        """设置要显示的调试网格索引 (0-15)"""
        if 0 <= index <= 15:
            self.debug_grid_index = index
            print(f"调试显示网格设置为第{index+1}个格子")
        else:
            print("网格索引必须在0-15之间")

    def adjust_yolo_parameters(self, mode="sensitive"):
        """调整YOLO检测参数"""
        if mode == "sensitive":
            # 高敏感度模式
            self.yolo_conf_threshold = 0.05
            self.yolo_iou_threshold = 0.2
            print("YOLO参数设置为高敏感度模式")
        elif mode == "balanced":
            # 平衡模式
            self.yolo_conf_threshold = 0.2
            self.yolo_iou_threshold = 0.3
            print("YOLO参数设置为平衡模式")
        elif mode == "strict":
            # 严格模式
            self.yolo_conf_threshold = 0.5
            self.yolo_iou_threshold = 0.5
            print("YOLO参数设置为严格模式")
        else:
            print("无效的模式，可选: sensitive, balanced, strict")

        print(f"当前参数: conf_th={self.yolo_conf_threshold}, iou_th={self.yolo_iou_threshold}")

    def test_yolo_on_saved_images(self):
        """测试YOLO在保存图像上的表现"""
        print("=" * 50)
        print("测试保存图像的YOLO识别效果")
        print("=" * 50)

        import os
        image_dir = "/root/mage_t"

        if not os.path.exists(image_dir):
            print(f"图像目录不存在: {image_dir}")
            return

        # 测试不同的参数配置
        configs = [
            ("极敏感", 0.01, 0.1),
            ("高敏感", 0.05, 0.2),
            ("中敏感", 0.1, 0.3),
            ("平衡", 0.2, 0.4),
            ("严格", 0.5, 0.5)
        ]

        for config_name, conf_th, iou_th in configs:
            print(f"\n{config_name}模式 (conf={conf_th}, iou={iou_th}):")
            total_detections = 0

            for i in range(1, 17):
                image_path = f"{image_dir}/grid_{i}.jpg"
                if os.path.exists(image_path):
                    try:
                        saved_img = image.Image(image_path)
                        yolo_objs = self.digit_detector.detect(saved_img, conf_th=conf_th, iou_th=iou_th)

                        if yolo_objs:
                            total_detections += len(yolo_objs)
                            labels = [self.digit_detector.labels[obj.class_id] for obj in yolo_objs]
                            confidences = [f"{obj.score:.2f}" for obj in yolo_objs]
                            print(f"  网格{i}: {labels} (置信度: {confidences})")
                        else:
                            print(f"  网格{i}: 无检测")
                    except Exception as e:
                        print(f"  网格{i}: 错误 - {e}")

            print(f"  总检测数: {total_detections}")

        print("\n建议:")
        print("- 如果所有模式检测数都很少，可能是模型问题")
        print("- 如果极敏感模式有检测但置信度很低，可能需要重新训练模型")
        print("- 如果图像质量好但检测效果差，检查模型输入尺寸匹配")

    def calibrate_corners(self):
        """手动标定四个角点"""
        corner_names = ["左上角", "右上角", "右下角", "左下角"]
        self.corner_points = []
        
        print("开始四角标定，请将红色激光笔移动到指定位置并触摸屏幕")
        
        for corner_name in corner_names:
            print(f"请将激光笔移动到{corner_name}，然后触摸屏幕")
            
            while True:
                img = self.cam.read()
                
                # 检测红色激光笔位置
                laser_pos = self.detect_red_laser(img)
                if laser_pos:
                    img.draw_circle(laser_pos[0], laser_pos[1], 1, image.COLOR_RED, -1)
                
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
                            print("未检测到激光笔，请重新定位")
                
                if app.need_exit():
                    return False
        
        print(f"四角标定完成: {self.corner_points}")
        return True

    def calibrate_auxiliary_points(self):
        """标定三个辅助分割点"""
        # 辅助点说明：小矩形(1,1), (2,2), (3,3)的右下角点
        auxiliary_names = [
            "小矩形(1,1)右下角",
            "小矩形(2,2)右下角",
            "小矩形(3,3)右下角"
        ]
        self.auxiliary_points = []

        print("开始辅助分割点标定，请将红色激光笔移动到指定位置并触摸屏幕")
        print("这些点用于辅助正确分割4x4网格")

        for point_name in auxiliary_names:
            print(f"请将激光笔移动到{point_name}，然后触摸屏幕")

            while True:
                # 获取当前图像并应用梯形矫正
                img = self.cam.read()
                corrected_img = self.apply_perspective_correction(img)

                # 检测红色激光笔位置（在矫正后的图像上）
                laser_pos = self.detect_red_laser(corrected_img)

                # 绘制已标定的辅助点
                for i, point in enumerate(self.auxiliary_points):
                    corrected_img.draw_circle(point[0], point[1], 8, image.COLOR_BLUE, 2)
                    corrected_img.draw_string(point[0]+10, point[1], f"辅助{i+1}", image.COLOR_BLUE, 1.2)

                # 绘制当前激光笔位置
                if laser_pos:
                    corrected_img.draw_circle(laser_pos[0], laser_pos[1], 5, image.COLOR_RED, -1)

                # 绘制网格线作为参考
                self.draw_reference_grid(corrected_img)

                # 显示提示信息
                corrected_img.draw_string(10, 10, f"标定{point_name}", image.COLOR_WHITE, 1.8)
                corrected_img.draw_string(10, 35, "触摸屏幕确认", image.COLOR_WHITE, 1.3)
                corrected_img.draw_string(10, 60, f"已标定: {len(self.auxiliary_points)}/3", image.COLOR_WHITE, 1.3)

                self.disp.show(corrected_img)

                # 检查触摸事件
                if self.touch.available():
                    touch_data = self.touch.read()
                    if touch_data[2] == 1:  # 按下事件
                        if laser_pos:
                            self.auxiliary_points.append(laser_pos)
                            print(f"{point_name}标定完成: {laser_pos}")
                            time.sleep(0.5)
                            break
                        else:
                            print("未检测到激光笔，请重新定位")

                if app.need_exit():
                    return False

        print(f"辅助分割点标定完成: {self.auxiliary_points}")
        return True

    def draw_reference_grid(self, img):
        """绘制参考网格线"""
        height, width = img.height(), img.width()
        cell_height = height // 4
        cell_width = width // 4

        # 绘制网格线
        for i in range(1, 4):
            # 垂直线
            x = i * cell_width
            img.draw_line(x, 0, x, height, image.COLOR_GRAY, 1)
            # 水平线
            y = i * cell_height
            img.draw_line(0, y, width, y, image.COLOR_GRAY, 1)

        # 标记特殊点位置
        # 小矩形(1,1)右下角 - 第2行第2列的右下角
        point_1_1 = (cell_width * 2, cell_height * 2)
        # 小矩形(2,2)右下角 - 第3行第3列的右下角
        point_2_2 = (cell_width * 3, cell_height * 3)
        # 小矩形(3,3)右下角 - 第4行第4列的右下角
        point_3_3 = (cell_width * 4, cell_height * 4)

        # 绘制参考点
        img.draw_circle(point_1_1[0], point_1_1[1], 6, image.COLOR_YELLOW, 2)
        img.draw_string(point_1_1[0]+8, point_1_1[1]-15, "(1,1)", image.COLOR_YELLOW, 1.0)

        img.draw_circle(point_2_2[0], point_2_2[1], 6, image.COLOR_YELLOW, 2)
        img.draw_string(point_2_2[0]+8, point_2_2[1]-15, "(2,2)", image.COLOR_YELLOW, 1.0)

        img.draw_circle(point_3_3[0], point_3_3[1], 6, image.COLOR_YELLOW, 2)
        img.draw_string(point_3_3[0]+8, point_3_3[1]-15, "(3,3)", image.COLOR_YELLOW, 1.0)

    def detect_red_laser(self, img):
        """检测红色激光笔位置"""
        blobs = img.find_blobs(self.red_laser_threshold, 
                               pixels_threshold=self.laser_min_pixels, 
                               area_threshold=self.laser_min_area,
                               merge=True)
        
        if blobs:
            largest_blob = max(blobs, key=lambda b: b.pixels())
            return (largest_blob.cx(), largest_blob.cy())
        
        return None

    def apply_perspective_correction(self, img):
        """应用梯形矫正"""
        if len(self.corner_points) != 4:
            return img

        # 将角点转换为浮点数列表
        corners = []
        for point in self.corner_points:
            corners.extend([float(point[0]), float(point[1])])

        # 使用rotation_corr进行梯形矫正
        corrected_img = img.rotation_corr(corners=corners)

        # 检查并修复颜色格式问题
        if corrected_img.format() != image.Format.FMT_RGB888:
            print(f"警告: 矫正后图像格式为 {corrected_img.format()}, 尝试转换为RGB888")
            # 如果格式不对，尝试转换
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

    def detect_digits_in_full_image(self, img):
        """在完整图像中检测数字并获得矫正后的中心坐标"""
        digits_found = {}

        print(f"开始在完整图像中检测数字，图像大小: {img.width()}x{img.height()}")

        try:
            # 对完整图像进行YOLO检测
            yolo_objs = self.digit_detector.detect(img,
                                                   conf_th=self.yolo_conf_threshold,
                                                   iou_th=self.yolo_iou_threshold)

            print(f"YOLO检测结果: {len(yolo_objs)} 个对象")

            # 处理每个检测到的数字
            for i, obj in enumerate(yolo_objs):
                try:
                    digit_label = self.digit_detector.labels[obj.class_id]

                    # 计算数字的中心坐标（矫正后的坐标）
                    center_x = obj.x + obj.w // 2
                    center_y = obj.y + obj.h // 2

                    # 处理数字标签
                    digits = self.process_digit_detection(digit_label)

                    for digit in digits:
                        # 如果这个数字还没有被记录，或者当前检测的置信度更高
                        if digit not in digits_found or obj.score > digits_found[digit]['confidence']:
                            digits_found[digit] = {
                                'position': (center_x, center_y),
                                'confidence': obj.score,
                                'bbox': (obj.x, obj.y, obj.w, obj.h)
                            }

                            print(f"检测到数字 {digit}: 位置({center_x}, {center_y}), 置信度:{obj.score:.3f}")

                except (ValueError, IndexError) as e:
                    print(f"处理检测结果 {i} 出错: {e}")
                    continue

        except Exception as e:
            print(f"YOLO检测失败: {e}")
            return {}

        return digits_found

    def fix_image_colors(self, img):
        """修复图像颜色问题"""
        try:
            # 检查图像格式
            if img.format() == image.Format.FMT_RGB888:
                return img

            print(f"检测到图像格式: {img.format()}, 尝试修复颜色")

            # 创建新的RGB888图像
            fixed_img = image.Image(img.width(), img.height(), image.Format.FMT_RGB888)

            # 逐像素复制并修复颜色
            for y in range(img.height()):
                for x in range(img.width()):
                    pixel = img.get_pixel(x, y)

                    # 如果是BGR格式，交换R和B通道
                    if img.format() == image.Format.FMT_BGR888:
                        # 提取RGB分量
                        r = (pixel >> 16) & 0xFF
                        g = (pixel >> 8) & 0xFF
                        b = pixel & 0xFF
                        # 重新组合为RGB
                        fixed_pixel = (r << 16) | (g << 8) | b
                        fixed_img.set_pixel(x, y, fixed_pixel)
                    else:
                        fixed_img.set_pixel(x, y, pixel)

            return fixed_img

        except Exception as e:
            print(f"颜色修复失败: {e}")
            return img

    def build_digit_coordinate_mapping(self):
        """建立数字与坐标的映射关系 - 不再使用图像分割和圆点检测"""
        print("=" * 60)
        print("开始建立数字坐标映射关系")
        print("=" * 60)
        print(f"目标: 找到 {self.min_required_mappings} 个数字的坐标映射")
        print()

        self.digit_coordinate_mapping = {}
        attempt = 0

        while attempt < self.max_mapping_attempts:
            attempt += 1
            print(f"尝试第 {attempt} 次识别...")

            # 获取当前图像并进行矫正
            img = self.cam.read()
            corrected_img = self.apply_perspective_correction(img)

            # 在完整图像中检测数字
            digits = self.detect_digits_in_full_image(corrected_img)

            # 更新映射关系
            for digit, info in digits.items():
                if digit not in self.digit_coordinate_mapping or info['confidence'] > self.digit_coordinate_mapping[digit]['confidence']:
                    self.digit_coordinate_mapping[digit] = info
                    print(f"更新数字 {digit} 的映射: 位置{info['position']}, 置信度{info['confidence']:.3f}")

            current_count = len(self.digit_coordinate_mapping)
            print(f"当前已找到 {current_count}/{self.min_required_mappings} 个数字映射")

            # 检查是否已找到足够的映射关系
            if current_count >= self.min_required_mappings:
                print(f"✅ 成功找到 {current_count} 个数字映射关系！")
                break

            # 显示当前检测结果
            self.display_current_mapping_progress(corrected_img, digits)

            time.sleep(0.5)  # 短暂延迟

        if len(self.digit_coordinate_mapping) < self.min_required_mappings:
            print(f"⚠️  警告: 只找到 {len(self.digit_coordinate_mapping)} 个数字映射，少于要求的 {self.min_required_mappings} 个")
            return False

        # 保存映射关系
        self.save_digit_coordinate_mapping()
        return True

    def display_current_mapping_progress(self, img, current_digits):
        """显示当前映射进度"""
        display_img = img.copy()

        # 绘制已保存的映射关系（绿色）
        for digit, info in self.digit_coordinate_mapping.items():
            pos = info['position']
            bbox = info['bbox']

            # 绘制边界框（绿色表示已保存）
            x, y, w, h = bbox
            display_img.draw_line(x, y, x+w, y, image.COLOR_GREEN, 2)
            display_img.draw_line(x, y, x, y+h, image.COLOR_GREEN, 2)
            display_img.draw_line(x+w, y, x+w, y+h, image.COLOR_GREEN, 2)
            display_img.draw_line(x, y+h, x+w, y+h, image.COLOR_GREEN, 2)

            # 绘制数字标签
            display_img.draw_string(x, y-20, f"{digit}:SAVED", image.COLOR_GREEN, 1.5)

            # 绘制中心点
            display_img.draw_circle(pos[0], pos[1], 3, image.COLOR_GREEN, 2)

        # 绘制当前检测到的数字（黄色表示新检测）
        for digit, info in current_digits.items():
            if digit not in self.digit_coordinate_mapping:
                pos = info['position']
                bbox = info['bbox']

                # 绘制边界框（黄色表示新检测）
                x, y, w, h = bbox
                display_img.draw_line(x, y, x+w, y, image.COLOR_YELLOW, 2)
                display_img.draw_line(x, y, x, y+h, image.COLOR_YELLOW, 2)
                display_img.draw_line(x+w, y, x+w, y+h, image.COLOR_YELLOW, 2)
                display_img.draw_line(x, y+h, x+w, y+h, image.COLOR_YELLOW, 2)

                # 绘制数字标签
                display_img.draw_string(x, y-20, f"{digit}:NEW", image.COLOR_YELLOW, 1.5)

                # 绘制中心点
                display_img.draw_circle(pos[0], pos[1], 3, image.COLOR_YELLOW, 2)

        # 显示进度信息
        progress_text = f"Progress: {len(self.digit_coordinate_mapping)}/{self.min_required_mappings}"
        display_img.draw_string(10, 10, progress_text, image.COLOR_WHITE, 2.0)

        self.disp.show(display_img)

    def save_digit_coordinate_mapping(self):
        """保存数字坐标映射关系"""
        print("\n" + "=" * 50)
        print("数字坐标映射关系:")
        print("=" * 50)

        # 按数字排序显示
        sorted_digits = sorted(self.digit_coordinate_mapping.keys())

        for digit in sorted_digits:
            info = self.digit_coordinate_mapping[digit]
            pos = info['position']
            conf = info['confidence']
            print(f"数字 {digit:2d}: 坐标({pos[0]:3d}, {pos[1]:3d}), 置信度:{conf:.3f}")

        # 保存到文件
        try:
            import json
            mapping_data = {}
            for digit, info in self.digit_coordinate_mapping.items():
                mapping_data[str(digit)] = {
                    'position': info['position'],
                    'confidence': float(info['confidence'])
                }

            with open('/root/digit_coordinate_mapping.json', 'w') as f:
                json.dump(mapping_data, f, indent=2)

            print(f"\n✅ 映射关系已保存到 /root/digit_coordinate_mapping.json")

        except Exception as e:
            print(f"⚠️  保存映射关系失败: {e}")

    def split_image_to_grid(self, img, rows=4, cols=4):
        """将图像分割为4x4网格，使用辅助点进行精确分割"""
        if len(self.auxiliary_points) == 3:
            # 使用辅助点进行精确分割
            return self.split_image_with_auxiliary_points(img, rows, cols)
        else:
            # 使用默认等分分割
            return self.split_image_default(img, rows, cols)

    def split_image_with_auxiliary_points(self, img, rows=4, cols=4):
        """使用辅助点进行精确网格分割"""
        height, width = img.height(), img.width()

        # 获取辅助点坐标
        aux_1_1 = self.auxiliary_points[0]  # 小矩形(1,1)右下角
        aux_2_2 = self.auxiliary_points[1]  # 小矩形(2,2)右下角
        aux_3_3 = self.auxiliary_points[2]  # 小矩形(3,3)右下角

        # 计算网格分割线
        # 垂直分割线
        v_line_1 = aux_1_1[0]  # 第1条垂直线
        v_line_2 = aux_2_2[0]  # 第2条垂直线
        v_line_3 = aux_3_3[0]  # 第3条垂直线

        # 水平分割线
        h_line_1 = aux_1_1[1]  # 第1条水平线
        h_line_2 = aux_2_2[1]  # 第2条水平线
        h_line_3 = aux_3_3[1]  # 第3条水平线

        # 构建网格坐标
        x_coords = [0, v_line_1, v_line_2, v_line_3, width]
        y_coords = [0, h_line_1, h_line_2, h_line_3, height]

        grid_cells = []
        for row in range(rows):
            for col in range(cols):
                x = x_coords[col]
                y = y_coords[row]
                cell_width = x_coords[col + 1] - x
                cell_height = y_coords[row + 1] - y
                
                roi = [x, y, cell_width, cell_height]
                grid_cells.append({
                    'roi': roi,
                    'center': (x + cell_width // 2, y + cell_height // 2),
                    'grid_pos': (row, col),
                    'precise_split': True
                })

        print(f"使用辅助点进行精确分割，网格数量: {len(grid_cells)}")
        return grid_cells

    def split_image_default(self, img, rows=4, cols=4):
        """默认等分网格分割"""
        height, width = img.height(), img.width()
        cell_height = height // rows
        cell_width = width // cols

        grid_cells = []
        for row in range(rows):
            for col in range(cols):
                x = col * cell_width
                y = row * cell_height
                roi = [x, y, cell_width, cell_height]
                grid_cells.append({
                    'roi': roi,
                    'center': (x + cell_width // 2, y + cell_height // 2),
                    'grid_pos': (row, col),
                    'precise_split': False
                })

        print(f"使用默认等分分割，网格数量: {len(grid_cells)}")
        return grid_cells

    def detect_circles_in_image(self, img, grid_cells=None):
        """使用find_circles检测黑色实心圆 - 针对分割后的图像进行检测"""
        all_circles = []

        if grid_cells is None:
            grid_cells = self.split_image_to_grid(img)

        # 对每个网格单元进行圆点检测
        for i, cell in enumerate(grid_cells):
            roi = cell['roi']

            try:
                # 提取网格区域
                cell_img = img.crop(roi[0], roi[1], roi[2], roi[3])

                # 在单个网格中检测圆点
                circles = self.detect_circles_in_cell(cell_img, roi)
                all_circles.extend(circles)

            except Exception as e:
                print(f"网格 {i} 圆点检测失败: {e}")
                continue

        return all_circles

    def detect_circles_in_cell(self, cell_img, roi):
        """在单个网格中检测圆点"""
        circles = []

        try:
            # 使用find_circles检测
            detected_circles = cell_img.find_circles(
                threshold=self.circle_threshold,
                x_margin=self.circle_x_margin,
                y_margin=self.circle_y_margin,
                r_margin=self.circle_r_margin,
                r_min=self.circle_r_min,
                r_max=min(self.circle_r_max, 20)
            )

            # 转换为全局坐标并过滤黑色圆点
            for circle in detected_circles:
                local_x, local_y = circle.x(), circle.y()
                global_x = roi[0] + local_x
                global_y = roi[1] + local_y

                # 检查是否为黑色区域（在原图上检查）
                if self.is_black_area_at_position(global_x, global_y):
                    circles.append((global_x, global_y, circle.r()))

        except Exception as e:
            print(f"find_circles失败，使用blob检测: {e}")
            # 备选方案：使用blob检测
            circles = self.detect_circles_with_blobs_in_cell(cell_img, roi)

        return circles

    def is_black_area_at_position(self, x, y, check_radius=3):
        """检查指定全局坐标位置是否为黑色区域"""
        try:
            # 获取当前图像
            img = self.cam.read()
            corrected_img = self.apply_perspective_correction(img)

            # 检查边界
            if (x < check_radius or y < check_radius or
                x >= corrected_img.width() - check_radius or
                y >= corrected_img.height() - check_radius):
                return False

            roi = [x-check_radius, y-check_radius, check_radius*2, check_radius*2]

            blobs = corrected_img.find_blobs(self.black_circle_threshold,
                                           roi=roi,
                                           pixels_threshold=5,
                                           area_threshold=10)

            return len(blobs) > 0
        except:
            return False

    def detect_circles_with_blobs_in_cell(self, cell_img, roi):
        """在单个网格中使用blob检测圆点"""
        circles = []

        try:
            blobs = cell_img.find_blobs(self.black_circle_threshold,
                                       pixels_threshold=20,
                                       area_threshold=40,
                                       merge=True)

            for blob in blobs:
                # 检查形状是否接近圆形
                roundness = blob.roundness()
                if roundness > 0.4:  # 降低圆形度要求
                    local_x, local_y = blob.cx(), blob.cy()
                    global_x = roi[0] + local_x
                    global_y = roi[1] + local_y
                    radius = max(blob.w(), blob.h()) // 2
                    circles.append((global_x, global_y, radius))

        except Exception as e:
            print(f"blob检测也失败: {e}")

        return circles

    def detect_circles_with_blobs(self, img):
        """使用blob检测作为圆点检测的备选方案"""
        try:
            blobs = img.find_blobs(self.black_circle_threshold,
                                   pixels_threshold=50,
                                   area_threshold=100,
                                   merge=True)

            circles = []
            for blob in blobs:
                # 检查形状是否接近圆形
                roundness = blob.roundness()
                if roundness > 0.5:  # 圆形度阈值
                    radius = max(blob.w(), blob.h()) // 2
                    circles.append((blob.cx(), blob.cy(), radius))

            return circles
        except Exception as e:
            print(f"备选圆点检测也失败: {e}")
            return []

    def is_black_area(self, img, x, y, check_radius=5):
        """检查指定位置是否为黑色区域"""
        roi = [max(0, x-check_radius), max(0, y-check_radius), 
               min(img.width()-x+check_radius, check_radius*2), 
               min(img.height()-y+check_radius, check_radius*2)]
        
        blobs = img.find_blobs(self.black_circle_threshold, 
                               roi=roi,
                               pixels_threshold=10,
                               area_threshold=20)
        
        return len(blobs) > 0

    def process_digit_detection(self, digit_label):
        """处理数字识别结果 - YOLO返回0-9阿拉伯数字"""
        # 清理标签
        clean_label = str(digit_label).strip()

        # YOLO返回0-9，直接转换
        try:
            digit = int(clean_label)
            if 0 <= digit <= 9:
                return [digit]
        except ValueError:
            pass

        return []

    def detect_digits_in_grid(self, img, grid_cells):
        """在网格中检测数字 - 针对每个分割后的图像进行检测"""
        digits_found = {}

        # 清空之前的调试图像
        self.debug_cell_images = []

        # 对每个网格单元进行YOLO检测
        for cell in grid_cells:
            roi = cell['roi']

            # 计算网格编号（1-16）
            grid_num = cell['grid_pos'][0] * 4 + cell['grid_pos'][1] + 1

            # 提取网格区域
            try:
                # 创建ROI区域的子图像
                cell_img = img.crop(roi[0], roi[1], roi[2], roi[3])

                # 修复cell_img的颜色问题
                fixed_cell_img = self.fix_image_colors(cell_img)

                # 保存修复后的cell_img用于调试显示
                self.debug_cell_images.append({
                    'grid_num': grid_num,
                    'cell_img': fixed_cell_img.copy(),
                    'roi': roi,
                    'grid_pos': cell['grid_pos']
                })

                # 保存网格图像用于调试
                try:
                    fixed_cell_img.save(f"/root/mage_t/grid_{grid_num}.jpg")
                    print(f"网格 {grid_num} 图像已保存到 /root/mage_t/grid_{grid_num}.jpg")
                except:
                    pass

                # 对单个网格进行YOLO检测 - 使用修复后的图像
                yolo_objs = self.digit_detector.detect(fixed_cell_img,
                                                       conf_th=self.yolo_conf_threshold,
                                                       iou_th=self.yolo_iou_threshold)

                print(f"网格 {grid_num} YOLO检测结果: {len(yolo_objs)} 个对象")

                # 收集该网格中的所有检测结果
                cell_detections = []
                for obj in yolo_objs:
                    try:
                        digit_label = self.digit_detector.labels[obj.class_id]

                        # 计算在原图中的坐标
                        global_x = roi[0] + obj.x + obj.w // 2
                        global_y = roi[1] + obj.y + obj.h // 2

                        cell_detections.append({
                            'label': digit_label,
                            'position': (global_x, global_y),
                            'confidence': obj.score,
                            'local_pos': (obj.x + obj.w // 2, obj.y + obj.h // 2)
                        })

                        print(f"网格{grid_num}: 检测到数字{digit_label}, 置信度:{obj.score:.2f}, 全局坐标:({global_x}, {global_y})")

                    except (ValueError, IndexError) as e:
                        print(f"处理检测结果出错: {e}")
                        continue

                # 处理该网格的检测结果，使用新的检测逻辑
                detected_digit, _ = self.process_cell_detections(cell_detections)

                # 如果检测到数字，查找该网格内的圆点
                if detected_digit:
                    circle_pos = self.find_circle_in_grid(img, cell['roi'])
                    if circle_pos:
                        digits_found[detected_digit] = circle_pos  # 只记录圆点坐标

            except Exception as e:
                print(f"网格 {grid_num} 检测失败: {e}")
                continue

        return digits_found

    def process_cell_detections(self, detections):
        """处理单个网格的检测结果，新的数字检测逻辑"""
        if len(detections) == 0:
            return None, None

        # 分离数字和0的检测
        digit_detections = []
        zero_detections = []

        for detection in detections:
            label = detection['label']
            if label == '0':
                zero_detections.append(detection)
            else:
                digit_detections.append(detection)

        # 按置信度排序
        digit_detections.sort(key=lambda x: x['confidence'], reverse=True)
        zero_detections.sort(key=lambda x: x['confidence'], reverse=True)

        # 应用新的检测逻辑，不依赖期望数字
        detected_digit = self.apply_detection_logic_without_expectation(
            digit_detections, zero_detections
        )

        return detected_digit, None  # 不记录数字坐标，只返回检测到的数字

    def apply_detection_logic_without_expectation(self, digit_detections, zero_detections):
        """应用新的数字检测逻辑 - 不依赖期望数字，根据检测结果判断"""

        # 如果没有检测到任何数字
        if len(digit_detections) == 0:
            return None

        # 如果只检测到一个数字
        if len(digit_detections) == 1:
            detected_label = digit_detections[0]['label']

            # 对于2-9的单数字，直接返回
            if detected_label in ['2', '3', '4', '5', '6', '7', '8', '9']:
                return int(detected_label)

            # 对于1，需要判断是1还是10
            elif detected_label == '1':
                # 如果0的检测数量较多，则为10
                if len(zero_detections) > len(digit_detections):
                    return 10
                # 如果同时检测到0，也可能是10
                elif len(zero_detections) >= 1:
                    return 10
                # 否则为1
                else:
                    return 1

        # 如果检测到两个数字，尝试组合成双数字
        elif len(digit_detections) >= 2:
            labels = [d['label'] for d in digit_detections[:2]]

            # 检查双数字组合
            if labels.count('1') == 2:
                return 11
            elif '1' in labels and '2' in labels:
                return 12
            elif '1' in labels and '3' in labels:
                return 13
            elif '1' in labels and '4' in labels:
                return 14
            elif '1' in labels and '5' in labels:
                return 15
            elif '1' in labels and '6' in labels:
                return 16

            # 如果无法组合，返回置信度最高的单数字
            detected_label = digit_detections[0]['label']
            if detected_label in ['2', '3', '4', '5', '6', '7', '8', '9']:
                return int(detected_label)
            elif detected_label == '1':
                # 判断1还是10
                if len(zero_detections) > 0:
                    return 10
                else:
                    return 1

        # 检查是否有1和0的组合（10的情况）
        if len(digit_detections) >= 1 and len(zero_detections) >= 1:
            digit_labels = [d['label'] for d in digit_detections]
            if '1' in digit_labels:
                return 10

        return None

    def digit_name_to_number(self, label):
        """将数字标签转换为数字 - YOLO返回0-9阿拉伯数字"""
        try:
            return int(label)
        except ValueError:
            return None

    def try_combine_digits_new_logic(self, labels, expected_digit):
        """新的双数字组合逻辑 - 基于0-9阿拉伯数字标签"""
        # 根据期望数字检查组合
        if expected_digit == 11 and labels.count('1') >= 2:
            return 11
        elif expected_digit == 12 and ('1' in labels and '2' in labels):
            return 12
        elif expected_digit == 13 and ('1' in labels and '3' in labels):
            return 13
        elif expected_digit == 14 and ('1' in labels and '4' in labels):
            return 14
        elif expected_digit == 15 and ('1' in labels and '5' in labels):
            return 15
        elif expected_digit == 16 and ('1' in labels and '6' in labels):
            return 16

        return None

    def find_circle_in_grid(self, img, roi):
        """在指定网格中查找黑色圆点，返回全局坐标"""
        try:
            # 提取网格区域
            cell_img = img.crop(roi[0], roi[1], roi[2], roi[3])

            # 在网格中检测圆点
            circles = self.detect_circles_in_cell(cell_img, roi)

            if circles:
                # 返回第一个检测到的圆点坐标（已经是全局坐标）
                return (circles[0][0], circles[0][1])

            return None

        except Exception as e:
            print(f"网格圆点检测失败: {e}")
            return None

    def try_combine_digits(self, labels):
        """尝试将两个标签组合成双数字"""
        # 双数字组合规则
        combinations = {
            frozenset(['1', '0']): 10,
            frozenset(['1', '1']): 11,
            frozenset(['1', '2']): 12,
            frozenset(['1', '3']): 13,
            frozenset(['1', '4']): 14,
            frozenset(['1', '5']): 15,
            frozenset(['1', '6']): 16
        }

        label_set = frozenset(labels)
        return combinations.get(label_set, None)

    def build_digit_circle_mapping(self):
        """建立数字与黑色圆点的对应关系，必须识别到16个数字"""
        print("开始建立数字与圆点的对应关系...")
        print("必须识别到16个数字才能继续...")

        attempt = 0
        while attempt < self.max_mapping_attempts:
            attempt += 1
            print(f"尝试第 {attempt} 次识别...")

            # 获取当前图像并进行矫正
            img = self.cam.read()
            corrected_img = self.apply_perspective_correction(img)

            # 分割图像为网格
            grid_cells = self.split_image_to_grid(corrected_img)

            # 检测数字和对应网格内的圆点
            print(f"开始检测数字，图像大小: {corrected_img.width()}x{corrected_img.height()}")
            print(f"网格数量: {len(grid_cells)}")

            digits = self.detect_digits_in_grid(corrected_img, grid_cells)

            print(f"检测到 {len(digits)} 个数字及其圆点")
            if len(digits) > 0:
                print("检测到的数字:")
                for digit, pos in digits.items():
                    print(f"  数字 {digit}: 圆点位置 {pos}")
            else:
                print("未检测到任何数字，可能的原因:")
                print("1. 图像质量问题")
                print("2. 模型输入格式不匹配")
                print("3. 置信度阈值过高")
                print("4. 网格分割问题")

            # 显示当前检测结果
            self.display_detection_result(corrected_img, digits, grid_cells)

            # 检查是否识别到16个数字
            if len(digits) == 16:
                print("成功识别到16个数字及其对应圆点！")

                # 直接使用检测结果作为映射关系
                self.digit_circle_mapping = digits.copy()

                print("映射关系建立完成:")
                for digit_num in sorted(self.digit_circle_mapping.keys()):
                    circle_pos = self.digit_circle_mapping[digit_num]
                    print(f"数字 {digit_num} -> 圆点 {circle_pos}")

                return True
            else:
                print(f"只识别到 {len(digits)} 个数字，需要16个。缺少的数字:")
                missing_digits = set(range(1, 17)) - set(digits.keys())
                print(f"缺少: {sorted(missing_digits)}")

            # 等待一段时间再次尝试
            time.sleep(1)

            if app.need_exit():
                return False

        print(f"经过 {self.max_mapping_attempts} 次尝试仍未能识别到16个数字")
        return False

    def display_detection_result(self, img, digits, grid_cells):
        """显示检测结果 - 在各个小矩形中显示检测结果"""
        # 如果是调试模式，显示cell_img而不是矫正后的图像
        if self.debug_display_mode:
            self.display_debug_cell_images()
            return

        # 创建一个显示网格图像的布局
        display_img = img.copy()

        # 为每个网格显示检测结果
        for cell in grid_cells:
            roi = cell['roi']
            grid_pos = cell['grid_pos']

            # 计算网格编号：从左到右，从上到下，1-16
            grid_num = grid_pos[0] * 4 + grid_pos[1] + 1

            # 绘制网格边框
            x, y, w, h = roi[0], roi[1], roi[2], roi[3]
            display_img.draw_line(x, y, x+w, y, image.COLOR_GRAY, 1)  # 上边
            display_img.draw_line(x, y, x, y+h, image.COLOR_GRAY, 1)  # 左边
            display_img.draw_line(x+w, y, x+w, y+h, image.COLOR_GRAY, 1)  # 右边
            display_img.draw_line(x, y+h, x+w, y+h, image.COLOR_GRAY, 1)  # 下边

            # 检查该网格的检测结果
            center_x = roi[0] + roi[2] // 2
            center_y = roi[1] + roi[3] // 2

            # 显示网格编号（使用标准1-16编号）
            display_img.draw_string(roi[0]+2, roi[1]+2, f"{grid_num}", image.COLOR_WHITE, 1.2)

            # 显示网格位置信息（调试用）
            display_img.draw_string(roi[0]+2, roi[1]+20, f"({grid_pos[0]},{grid_pos[1]})", image.COLOR_GRAY, 0.8)

            # 查找该网格中检测到的数字
            detected_digit = None
            circle_pos = None

            # 检查是否有数字被检测到并且圆点在该网格范围内
            for digit, pos in digits.items():
                if pos:
                    cx, cy = pos
                    # 检查圆点是否在当前网格范围内
                    if (roi[0] <= cx <= roi[0] + roi[2] and
                        roi[1] <= cy <= roi[1] + roi[3]):
                        detected_digit = digit
                        circle_pos = pos
                        break

            if detected_digit and circle_pos:
                # 检测成功 - 显示绿色信息
                display_img.draw_string(center_x-15, center_y-10, f"D{detected_digit}", image.COLOR_GREEN, 1.2)
                display_img.draw_string(center_x-10, center_y+5, "OK", image.COLOR_GREEN, 1.0)

                # 绘制检测到的圆点
                cx, cy = circle_pos
                display_img.draw_circle(cx, cy, 6, image.COLOR_GREEN, 2)

                # 用绿色边框标记成功的网格
                display_img.draw_line(x, y, x+w, y, image.COLOR_GREEN, 3)
                display_img.draw_line(x, y, x, y+h, image.COLOR_GREEN, 3)
                display_img.draw_line(x+w, y, x+w, y+h, image.COLOR_GREEN, 3)
                display_img.draw_line(x, y+h, x+w, y+h, image.COLOR_GREEN, 3)
            else:
                # 未检测到数字或圆点
                display_img.draw_string(center_x-15, center_y-5, "EMPTY", image.COLOR_RED, 1.2)

                # 用红色边框标记失败的网格
                display_img.draw_line(x, y, x+w, y, image.COLOR_RED, 2)
                display_img.draw_line(x, y, x, y+h, image.COLOR_RED, 2)
                display_img.draw_line(x+w, y, x+w, y+h, image.COLOR_RED, 2)
                display_img.draw_line(x, y+h, x+w, y+h, image.COLOR_RED, 2)

        # 显示统计信息
        display_img.draw_string(10, 10, f"Mapped: {len(digits)}/16", image.COLOR_WHITE, 1.5)

        # 显示缺少的数字
        if len(digits) < 16:
            missing = set(range(1, 17)) - set(digits.keys())
            missing_str = ",".join(map(str, sorted(list(missing))[:8]))
            display_img.draw_string(10, 35, f"Missing: {missing_str}", image.COLOR_RED, 1.2)
        else:
            display_img.draw_string(10, 35, "All Complete!", image.COLOR_GREEN, 1.5)

        self.disp.show(display_img)

    def display_debug_cell_images(self):
        """显示调试模式下的cell_img图像"""
        if not self.debug_cell_images:
            print("没有可显示的调试图像")
            return

        if self.debug_display_mode:
            # 显示单个网格图像
            if 0 <= self.debug_grid_index < len(self.debug_cell_images):
                debug_info = self.debug_cell_images[self.debug_grid_index]
                cell_img = debug_info['cell_img']
                grid_num = debug_info['grid_num']

                print(f"显示网格 {grid_num}, 原始格式: {cell_img.format()}")

                # 创建显示图像，将cell_img缩放到显示器大小
                display_img = image.Image(self.disp.width(), self.disp.height(), image.Format.FMT_RGB888)
                display_img.clear()

                # 计算缩放比例以适应显示器
                scale_x = self.disp.width() / cell_img.width()
                scale_y = self.disp.height() / cell_img.height()
                scale = min(scale_x, scale_y)

                new_width = int(cell_img.width() * scale)
                new_height = int(cell_img.height() * scale)

                # 缩放cell_img
                scaled_cell_img = cell_img.resize(new_width, new_height)

                # 居中显示
                x_offset = (self.disp.width() - new_width) // 2
                y_offset = (self.disp.height() - new_height) // 2

                # 将缩放后的图像绘制到显示图像上，同时修复颜色
                for y in range(new_height):
                    for x in range(new_width):
                        if (x_offset + x < self.disp.width() and
                            y_offset + y < self.disp.height()):
                            pixel = scaled_cell_img.get_pixel(x, y)

                            # 如果原图是BGR格式，交换R和B通道
                            if cell_img.format() == image.Format.FMT_BGR888:
                                r = (pixel >> 16) & 0xFF
                                g = (pixel >> 8) & 0xFF
                                b = pixel & 0xFF
                                fixed_pixel = (b << 16) | (g << 8) | r  # BGR -> RGB
                                display_img.set_pixel(x_offset + x, y_offset + y, fixed_pixel)
                            else:
                                display_img.set_pixel(x_offset + x, y_offset + y, pixel)

                # 添加标题信息
                display_img.draw_string(10, 10, f"Debug Grid {grid_num}", image.COLOR_WHITE, 2.0)
                display_img.draw_string(10, 40, f"YOLO Input Image", image.COLOR_WHITE, 1.5)
                display_img.draw_string(10, 60, f"Size: {cell_img.width()}x{cell_img.height()}", image.COLOR_WHITE, 1.0)
                display_img.draw_string(10, 80, f"Format: {cell_img.format()}", image.COLOR_WHITE, 1.0)

                self.disp.show(display_img)
                print(f"显示调试网格 {grid_num} 的YOLO输入图像")
            else:
                print(f"调试网格索引 {self.debug_grid_index} 超出范围")

    def create_grid_mosaic_display(self):
        """创建4x4网格拼接显示图像"""
        if not self.debug_cell_images or len(self.debug_cell_images) != 16:
            print("需要16个网格图像才能创建拼接显示")
            return None

        # 假设每个cell_img大小相同，获取第一个的尺寸
        first_cell = self.debug_cell_images[0]['cell_img']
        cell_width = first_cell.width()
        cell_height = first_cell.height()

        # 创建拼接图像
        mosaic_width = cell_width * 4
        mosaic_height = cell_height * 4
        mosaic_img = image.Image(mosaic_width, mosaic_height)
        mosaic_img.clear()

        # 按4x4排列拼接图像
        for i, debug_info in enumerate(self.debug_cell_images):
            if i >= 16:
                break

            cell_img = debug_info['cell_img']
            grid_num = debug_info['grid_num']

            # 计算在拼接图像中的位置
            row = i // 4
            col = i % 4
            x_pos = col * cell_width
            y_pos = row * cell_height

            # 将cell_img复制到拼接图像的对应位置
            for y in range(cell_height):
                for x in range(cell_width):
                    if (x < cell_img.width() and y < cell_img.height()):
                        pixel = cell_img.get_pixel(x, y)
                        mosaic_img.set_pixel(x_pos + x, y_pos + y, pixel)

            # 在每个网格上添加编号
            mosaic_img.draw_string(x_pos + 2, y_pos + 2, str(grid_num), image.COLOR_WHITE, 1.0)

        return mosaic_img

    def display_grid_images(self, img, grid_cells, digits):
        """显示各个小矩形的图像（用于调试）"""
        # 这个函数可以用于详细查看每个网格的检测情况
        for i, cell in enumerate(grid_cells):
            roi = cell['roi']
            try:
                # 提取网格图像
                cell_img = img.crop(roi[0], roi[1], roi[2], roi[3])

                # 在网格图像上绘制检测结果
                grid_pos = cell['grid_pos']
                expected_digit = grid_pos[0] * 4 + grid_pos[1] + 1

                # 检查是否有对应的数字和圆点
                has_digit = expected_digit in digits
                has_circle = digits.get(expected_digit) is not None

                # 绘制状态信息
                status_color = image.COLOR_GREEN if (has_digit and has_circle) else image.COLOR_RED
                cell_img.draw_string(5, 5, f"格{expected_digit}", status_color, 1.0)

                if has_circle:
                    cell_img.draw_string(5, 20, "有圆点", image.COLOR_GREEN, 0.8)
                else:
                    cell_img.draw_string(5, 20, "无圆点", image.COLOR_RED, 0.8)

                # 这里可以选择性地显示单个网格图像
                # self.disp.show(cell_img)  # 如果需要逐个查看

            except Exception as e:
                print(f"显示网格 {i} 失败: {e}")

    def get_target_circle(self, target_digit):
        """获取目标数字对应的圆点坐标"""
        return self.digit_circle_mapping.get(target_digit, None)

    def save_mapping_to_file(self, filename="digit_circle_mapping.txt"):
        """保存映射关系到文件"""
        try:
            with open(filename, 'w') as f:
                f.write("# 数字与圆点映射关系\n")
                f.write("# 格式: 数字 圆点x坐标 圆点y坐标\n")
                for digit, (cx, cy) in sorted(self.digit_circle_mapping.items()):
                    f.write(f"{digit} {cx} {cy}\n")
            print(f"映射关系已保存到 {filename}")
            return True
        except Exception as e:
            print(f"保存映射关系失败: {e}")
            return False

    def test_mapping_system(self):
        """测试数字坐标映射系统 - 新版本：只检测数字坐标"""
        print("=" * 60)
        print("数字坐标映射系统测试")
        print("=" * 60)

        # 步骤1: 四角标定
        print("\n步骤1: 四角标定")
        if not self.calibrate_corners():
            print("四角标定失败，无法继续")
            return False

        # 步骤2: 建立数字坐标映射关系
        print("\n步骤2: 建立数字坐标映射关系")
        success = self.build_digit_coordinate_mapping()

        if success:
            print("✅ 数字坐标映射系统测试成功完成！")
            print(f"成功建立了 {len(self.digit_coordinate_mapping)} 个数字的坐标映射关系")

            # 步骤3: 测试映射查询
            print("\n步骤3: 测试映射查询")
            print("触摸屏幕切换测试数字，长按退出")
            self.test_coordinate_mapping_query()
        else:
            print("❌ 数字坐标映射系统测试失败")

        return success

    def test_coordinate_mapping_query(self):
        """测试坐标映射查询功能"""
        if not self.digit_coordinate_mapping:
            print("没有可用的数字坐标映射")
            return

        available_digits = sorted(self.digit_coordinate_mapping.keys())
        current_index = 0

        print(f"可用数字: {available_digits}")

        while not app.need_exit():
            img = self.cam.read()
            corrected_img = self.apply_perspective_correction(img)

            # 绘制所有映射关系
            for digit, info in self.digit_coordinate_mapping.items():
                pos = info['position']
                confidence = info['confidence']

                # 当前测试数字用黄色，其他用绿色
                current_digit = available_digits[current_index]
                color = image.COLOR_YELLOW if digit == current_digit else image.COLOR_GREEN

                # 绘制数字位置
                corrected_img.draw_circle(pos[0], pos[1], 8, color, 3)
                corrected_img.draw_string(pos[0] + 15, pos[1] - 10,
                                        f"{digit}({confidence:.2f})", color, 1.5)

            # 显示当前测试信息
            current_digit = available_digits[current_index]
            current_pos = self.digit_coordinate_mapping[current_digit]['position']
            corrected_img.draw_string(10, 10, f"Test Digit: {current_digit}", image.COLOR_WHITE, 2.0)
            corrected_img.draw_string(10, 40, f"Position: {current_pos}", image.COLOR_WHITE, 1.5)
            corrected_img.draw_string(10, 60, f"Touch to switch", image.COLOR_WHITE, 1.2)

            self.disp.show(corrected_img)

            # 检查触摸事件
            touch_point = self.touch.read()
            if touch_point is not None:
                # 切换到下一个数字
                current_index = (current_index + 1) % len(available_digits)
                print(f"切换到数字 {available_digits[current_index]}")

                # 等待触摸释放
                while self.touch.read() is not None:
                    time.sleep(0.1)
                time.sleep(0.3)


    def test_grid_layout(self):
        """测试网格布局和编号"""
        print("=" * 50)
        print("网格布局测试")
        print("=" * 50)
        print("显示网格编号和位置，验证网格逻辑是否正确")
        print("同时保存每个网格的图像到 /tmp/grid_X.jpg")
        print("按任意键退出")

        while not app.need_exit():
            img = self.cam.read()
            corrected_img = self.apply_perspective_correction(img)

            # 分割图像为网格
            grid_cells = self.split_image_to_grid(corrected_img)

            # 绘制网格和编号，同时保存网格图像
            for cell in grid_cells:
                roi = cell['roi']
                grid_pos = cell['grid_pos']
                grid_num = grid_pos[0] * 4 + grid_pos[1] + 1

                # 绘制网格边框
                x, y, w, h = roi[0], roi[1], roi[2], roi[3]
                corrected_img.draw_line(x, y, x+w, y, image.COLOR_GREEN, 2)
                corrected_img.draw_line(x, y, x, y+h, image.COLOR_GREEN, 2)
                corrected_img.draw_line(x+w, y, x+w, y+h, image.COLOR_GREEN, 2)
                corrected_img.draw_line(x, y+h, x+w, y+h, image.COLOR_GREEN, 2)

                # 显示网格编号
                center_x = x + w // 2
                center_y = y + h // 2
                corrected_img.draw_string(center_x-10, center_y-10, str(grid_num), image.COLOR_RED, 2.0)

                # 显示行列信息
                corrected_img.draw_string(x+2, y+2, f"R{grid_pos[0]}C{grid_pos[1]}", image.COLOR_BLUE, 1.0)

                # 保存网格图像用于调试
                try:
                    cell_img = corrected_img.crop(roi[0], roi[1], roi[2], roi[3])
                    cell_img.save(f"/tmp/debug_grid_{grid_num}.jpg")
                except Exception as e:
                    print(f"保存网格{grid_num}图像失败: {e}")

            # 显示网格信息
            corrected_img.draw_string(10, 10, f"Grid Count: {len(grid_cells)}", image.COLOR_WHITE, 1.5)
            corrected_img.draw_string(10, 35, "Grid Layout: 4x4 (1-16)", image.COLOR_WHITE, 1.2)
            corrected_img.draw_string(10, 60, "Images saved to /tmp/", image.COLOR_WHITE, 1.2)

            self.disp.show(corrected_img)

            # 打印网格信息
            if len(grid_cells) == 16:
                print("网格布局正确，16个网格:")
                for cell in grid_cells:
                    grid_pos = cell['grid_pos']
                    grid_num = grid_pos[0] * 4 + grid_pos[1] + 1
                    roi = cell['roi']
                    print(f"  网格{grid_num}: 行{grid_pos[0]}列{grid_pos[1]}, ROI({roi[0]}, {roi[1]}, {roi[2]}, {roi[3]})")
                print("网格图像已保存到 /tmp/debug_grid_1.jpg 到 /tmp/debug_grid_16.jpg")
                print("请检查这些图像是否与实际靶纸对应")
            else:
                print(f"网格数量错误: {len(grid_cells)}, 应该是16")

    def check_image_orientation(self):
        """检查图像方向和内容"""
        print("=" * 50)
        print("图像方向检查")
        print("=" * 50)
        print("检查原始图像、矫正后图像和网格分割是否正确")
        print("按任意键退出")

        while not app.need_exit():
            # 获取原始图像
            original_img = self.cam.read()

            # 应用矫正
            corrected_img = self.apply_perspective_correction(original_img)

            # 保存关键图像
            try:
                original_img.save("/tmp/original_image.jpg")
                corrected_img.save("/tmp/corrected_image.jpg")
                print("已保存原始图像到 /tmp/original_image.jpg")
                print("已保存矫正图像到 /tmp/corrected_image.jpg")
            except Exception as e:
                print(f"保存图像失败: {e}")

            # 显示图像信息
            original_img.draw_string(10, 10, "Original Image", image.COLOR_WHITE, 2.0)
            original_img.draw_string(10, 40, f"Size: {original_img.width()}x{original_img.height()}", image.COLOR_WHITE, 1.5)

            # 显示矫正后图像
            corrected_img.draw_string(10, 10, "Corrected Image", image.COLOR_WHITE, 2.0)
            corrected_img.draw_string(10, 40, f"Size: {corrected_img.width()}x{corrected_img.height()}", image.COLOR_WHITE, 1.5)

            # 交替显示两个图像
            self.disp.show(original_img)
            time.sleep(1)
            self.disp.show(corrected_img)
            time.sleep(1)

    def test_yolo_detection(self):
        """测试YOLO检测功能"""
        print("=" * 50)
        print("YOLO检测测试")
        print("=" * 50)
        print(f"模型标签: {self.digit_detector.labels}")
        print(f"置信度阈值: {self.yolo_conf_threshold}")
        print(f"IOU阈值: {self.yolo_iou_threshold}")
        print("按任意键开始测试，长按退出")

        while not app.need_exit():
            img = self.cam.read()

            # 测试整个图像的YOLO检测
            yolo_objs = self.digit_detector.detect(img,
                                                   conf_th=self.yolo_conf_threshold,
                                                   iou_th=self.yolo_iou_threshold)

            # 绘制检测结果
            for obj in yolo_objs:
                try:
                    label = self.digit_detector.labels[obj.class_id]
                    confidence = obj.score

                    # 绘制边界框 - 使用draw_line绘制矩形
                    x, y, w, h = obj.x, obj.y, obj.w, obj.h
                    img.draw_line(x, y, x+w, y, image.COLOR_GREEN, 2)  # 上边
                    img.draw_line(x, y, x, y+h, image.COLOR_GREEN, 2)  # 左边
                    img.draw_line(x+w, y, x+w, y+h, image.COLOR_GREEN, 2)  # 右边
                    img.draw_line(x, y+h, x+w, y+h, image.COLOR_GREEN, 2)  # 下边

                    # 绘制标签和置信度
                    img.draw_string(obj.x, obj.y-20, f"{label}:{confidence:.2f}", image.COLOR_GREEN, 1.5)

                except Exception as e:
                    print(f"绘制检测结果出错: {e}")

            # 显示统计信息
            img.draw_string(10, 10, f"检测到: {len(yolo_objs)} 个对象", image.COLOR_WHITE, 1.5)
            img.draw_string(10, 35, f"图像大小: {img.width()}x{img.height()}", image.COLOR_WHITE, 1.2)

            self.disp.show(img)

            if len(yolo_objs) > 0:
                print(f"检测到 {len(yolo_objs)} 个对象:")
                for obj in yolo_objs:
                    label = self.digit_detector.labels[obj.class_id]
                    print(f"  {label}: 置信度 {obj.score:.2f}, 位置 ({obj.x}, {obj.y}, {obj.w}, {obj.h})")

    def test_debug_display_mode(self):
        """测试调试显示模式"""
        print("=" * 50)
        print("调试显示模式测试")
        print("=" * 50)
        print("这个模式将显示YOLO模型实际输入的cell_img图像")
        print("而不是显示矫正后的完整图像")
        print()

        # 启用调试显示模式
        self.debug_display_mode = True
        print("调试显示模式已启用")

        # 进行四角标定
        print("步骤1: 四角标定")
        if not self.calibrate_corners():
            print("四角标定失败")
            return False

        # 选择分割模式
        print("\n步骤2: 选择分割模式")
        print("1 - 使用辅助点精确分割")
        print("2 - 使用默认均等分割")

        try:
            split_choice = input("请选择分割模式 (1/2): ").strip()
        except:
            split_choice = "1"

        if split_choice == "1":
            print("选择辅助点精确分割模式")
            print("标定小矩形(1,1), (2,2), (3,3)的右下角点以辅助精确分割")
            if not self.calibrate_auxiliary_points():
                print("辅助分割点标定失败，将使用默认均等分割")
                self.auxiliary_points = []
        else:
            print("选择直接均等分割模式")
            self.auxiliary_points = []

        print("\n步骤3: 开始调试显示")
        print("触摸屏幕切换显示的网格")
        print("长按退出调试模式")

        current_grid = 0
        self.debug_grid_index = current_grid

        while not app.need_exit():
            # 捕获图像
            img = self.cam.read()

            # 应用梯形矫正
            corrected_img = self.apply_perspective_correction(img)

            # 分割图像为网格
            grid_cells = self.split_image_to_grid(corrected_img)

            # 检测数字（这会保存cell_img到debug_cell_images）
            digits = self.detect_digits_in_grid(corrected_img, grid_cells)

            # 显示调试图像（会显示当前选择的网格的cell_img）
            self.display_detection_result(corrected_img, digits, grid_cells)

            # 检查触摸事件
            touch_point = self.touch.read()
            if touch_point is not None:
                # 切换到下一个网格
                current_grid = (current_grid + 1) % 16
                self.debug_grid_index = current_grid
                print(f"切换到网格 {current_grid + 1}")

                # 等待触摸释放
                while self.touch.read() is not None:
                    time.sleep(0.1)

                time.sleep(0.3)  # 防止快速切换

        # 恢复正常显示模式
        self.debug_display_mode = False
        print("调试显示模式已关闭")

def main():
    """主函数"""
    print("=" * 50)
    print("数字圆点映射系统测试")
    print("=" * 50)
    print()
    print("功能说明:")
    print("1. 数字坐标映射测试 - 检测数字并建立坐标映射关系")
    print("2. YOLO检测测试 - 测试YOLO数字识别功能")
    print("3. 网格布局测试 - 测试网格分割和编号逻辑")
    print("4. 图像方向检查 - 检查图像矫正和方向问题")
    print("5. 调试显示模式 - 显示YOLO模型实际输入的cell_img")
    print("6. YOLO诊断模式 - 诊断YOLO识别效果差的原因")
    print()
    print("选择测试模式:")
    print("1 - 数字坐标映射测试")
    print("2 - YOLO检测测试")
    print("3 - 网格布局测试")
    print("4 - 图像方向检查")
    print("5 - 调试显示模式")
    print("6 - YOLO诊断模式")
    print()

    try:
        choice = input("请输入选择 (1/2/3/4/5/6): ").strip()
    except:
        choice = "1"

    try:
        # 创建映射系统实例
        system = DigitCircleMappingSystem()

        if choice == "2":
            # 运行YOLO检测测试
            system.test_yolo_detection()
            success = True  # YOLO测试完成
        elif choice == "3":
            # 运行网格布局测试
            system.test_grid_layout()
            success = True  # 网格测试完成
        elif choice == "4":
            # 运行图像方向检查
            system.check_image_orientation()
            success = True  # 图像检查完成
        elif choice == "5":
            # 运行调试显示模式
            system.test_debug_display_mode()
            success = True  # 调试显示完成
        elif choice == "6":
            # 运行YOLO诊断模式
            system.test_yolo_on_saved_images()
            success = True  # YOLO诊断完成
        else:
            # 运行完整映射测试
            success = system.test_mapping_system()

        if success and choice == "1":
            print("\n" + "=" * 50)
            print("映射系统测试完成！")
            print("=" * 50)
            print(f"成功建立 {len(system.digit_circle_mapping)} 个数字-圆点映射关系")
            print("映射关系已保存到文件")
            print()
            print("映射关系详情:")
            for digit in sorted(system.digit_circle_mapping.keys()):
                pos = system.digit_circle_mapping[digit]
                print(f"  数字 {digit:2d} -> 圆点 ({pos[0]:3d}, {pos[1]:3d})")
        else:
            print("\n映射系统测试失败！")

    except KeyboardInterrupt:
        print("\n用户中断测试")
    except Exception as e:
        print(f"\n测试过程中发生错误: {e}")
        import traceback
        traceback.print_exc()
    finally:
        print("\n测试程序结束")

if __name__ == "__main__":
    main()
