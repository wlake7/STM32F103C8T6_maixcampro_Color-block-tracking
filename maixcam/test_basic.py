"""
基础功能测试脚本
测试摄像头、图像处理和通信的基本功能
"""

from maix import camera, display, image, app, time
from config import Config
from communication import Communication
from image_processor import ImageProcessor

def test_camera():
    """测试摄像头功能"""
    print("=" * 50)
    print("摄像头测试")
    print("=" * 50)
    
    try:
        config = Config()
        
        # 初始化摄像头
        cam = camera.Camera(
            config.camera_width,
            config.camera_height,
            image.Format.FMT_RGB888
        )
        
        # 初始化显示器
        disp = display.Display()
        
        print("摄像头和显示器初始化成功")
        print("按任意键退出摄像头测试...")
        
        frame_count = 0
        start_time = time.time()
        
        while not app.need_exit():
            # 捕获图像
            img = cam.read()
            
            # 显示帧率信息
            frame_count += 1
            if frame_count % 30 == 0:
                elapsed = time.time() - start_time
                fps = frame_count / elapsed
                print(f"FPS: {fps:.1f}")
            
            # 在图像上绘制信息
            img.draw_string(10, 10, "Camera Test", image.COLOR_WHITE, 2)
            img.draw_string(10, 40, f"Frame: {frame_count}", image.COLOR_WHITE, 1.5)
            img.draw_string(10, 65, "Press any key to exit", image.COLOR_WHITE, 1.5)
            
            # 显示图像
            disp.show(img)
            
            # 简单的退出检测
            if frame_count > 300:  # 10秒后自动退出
                break
        
        print("摄像头测试完成")
        return True
        
    except Exception as e:
        print(f"摄像头测试失败: {e}")
        return False

def test_image_detection():
    """测试图像检测功能"""
    print("=" * 50)
    print("图像检测测试")
    print("=" * 50)
    
    try:
        config = Config()
        processor = ImageProcessor(config)
        
        print("图像处理器初始化成功")
        print("开始检测红色目标和绿色激光...")
        print("按任意键退出检测测试...")
        
        frame_count = 0
        detection_count = 0
        
        while not app.need_exit() and frame_count < 300:
            # 捕获图像
            img = processor.capture_image()
            if img is None:
                continue
            
            # 检测红色目标
            red_target = processor.detect_red_target(img)
            
            # 检测绿色激光
            green_laser = processor.detect_green_laser(img)
            
            # 绘制检测结果
            if red_target:
                img.draw_circle(red_target[0], red_target[1], 10, image.COLOR_RED, 3)
                img.draw_string(red_target[0] + 15, red_target[1] - 10,
                              "Red Target", image.COLOR_RED, 1.5)
                detection_count += 1
            
            if green_laser:
                img.draw_circle(green_laser[0], green_laser[1], 8, image.COLOR_GREEN, 3)
                img.draw_string(green_laser[0] + 15, green_laser[1] - 10,
                              "Green Laser", image.COLOR_GREEN, 1.5)
                detection_count += 1
            
            # 绘制连接线
            if red_target and green_laser:
                img.draw_line(red_target[0], red_target[1],
                             green_laser[0], green_laser[1],
                             image.COLOR_YELLOW, 2)
                
                # 计算偏移
                offset = processor.calculate_offset(red_target, green_laser)
                if offset:
                    img.draw_string(10, 100, 
                                  f"Offset: ({offset['offset_x']:.1f}, {offset['offset_y']:.1f})",
                                  image.COLOR_WHITE, 1.5)
                    img.draw_string(10, 125,
                                  f"Distance: {offset['distance']:.1f}",
                                  image.COLOR_WHITE, 1.5)
            
            # 显示状态信息
            img.draw_string(10, 10, "Detection Test", image.COLOR_WHITE, 2)
            img.draw_string(10, 40, f"Frame: {frame_count}", image.COLOR_WHITE, 1.5)
            img.draw_string(10, 65, f"Detections: {detection_count}", image.COLOR_WHITE, 1.5)
            
            # 显示图像
            processor.display_image(img)
            
            frame_count += 1
        
        processor.close()
        print("图像检测测试完成")
        return True
        
    except Exception as e:
        print(f"图像检测测试失败: {e}")
        return False

def test_communication_only():
    """仅测试通信功能"""
    print("=" * 50)
    print("通信功能测试")
    print("=" * 50)
    
    try:
        config = Config()
        comm = Communication(config)
        
        if not comm.is_connected:
            print("通信初始化失败")
            return False
        
        print("通信初始化成功")
        
        # 发送测试数据
        for i in range(5):
            target_pos = (320 + i*10, 240 + i*5)
            laser_pos = (300 + i*8, 220 + i*3)
            
            success = comm.send_position_data(target_pos, laser_pos)
            print(f"发送测试数据 {i+1}: {'成功' if success else '失败'}")
            time.sleep(0.5)
        
        # 显示统计
        stats = comm.get_communication_stats()
        print(f"通信统计: 成功{stats['sent_packets']}, 失败{stats['failed_packets']}")
        
        comm.close()
        return True
        
    except Exception as e:
        print(f"通信测试失败: {e}")
        return False

def main():
    """主测试函数"""
    print("MaixCam基础功能测试")
    print("请选择测试项目:")
    print("1. 摄像头测试")
    print("2. 图像检测测试") 
    print("3. 通信功能测试")
    print("4. 全部测试")
    
    choice = input("请输入选择 (1-4): ").strip()
    
    if choice == "1":
        test_camera()
    elif choice == "2":
        test_image_detection()
    elif choice == "3":
        test_communication_only()
    elif choice == "4":
        print("开始全部测试...")
        test_camera()
        test_image_detection()
        test_communication_only()
    else:
        print("无效选择")

if __name__ == "__main__":
    main()
