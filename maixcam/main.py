"""
激光追踪系统 - MaixCam端主程序
实现红色色块和绿色激光的实时检测与追踪
支持多种运行模式：正常追踪、通信诊断、功能测试
"""

from maix import app, time, pinmap
from laser_tracker import LaserTracker
from config import Config
from run_config import get_run_mode, print_mode_info

def run_laser_tracking():
    """运行激光追踪模式"""
    print("=" * 50)
    print("激光追踪模式")
    print("=" * 50)

    try:
        # 加载配置
        config = Config()
        print("配置加载完成")

        # 初始化激光追踪器
        tracker = LaserTracker(config)
        print("激光追踪器初始化完成")

        # 系统标定
        print("\n开始系统标定...")
        if not tracker.calibrate_system():
            print("系统标定失败，退出程序")
            return
        print("系统标定完成")

        # 启动追踪
        print("\n开始激光追踪...")
        tracker.start_tracking()

    except KeyboardInterrupt:
        print("\n用户中断程序")
    except Exception as e:
        print(f"程序异常: {e}")
        import traceback
        traceback.print_exc()

def run_communication_diagnosis():
    """运行通信诊断模式"""
    print("=" * 50)
    print("通信诊断模式")
    print("=" * 50)

    try:
        from maix import uart
        import struct

        # 初始化串口2
        device = "/dev/ttyS2"
        serial = uart.UART(device, 115200)
        print(f"✓ UART初始化成功: {device}@115200")

        print("开始发送测试数据...")

        # 发送测试数据包
        for i in range(20):
            # 模拟移动的目标
            target_x = 320 + int(50 * (i % 10 - 5))
            target_y = 240 + int(30 * (i % 8 - 4))

            # 模拟追踪的激光
            laser_x = target_x - 20 + int(10 * (i % 3))
            laser_y = target_y - 15 + int(8 * (i % 4))

            # 发送目标位置
            # 数据包格式: [0xAA, 0x55, Length, Command, Data..., Checksum]
            # Length = 纯数据长度（不包含命令）
            target_payload = bytes([
                0x04,  # 数据长度（4字节坐标数据）
                0x01,  # 命令：目标位置
                target_x & 0xFF, (target_x >> 8) & 0xFF,  # X坐标（小端）
                target_y & 0xFF, (target_y >> 8) & 0xFF   # Y坐标（小端）
            ])
            # 计算校验和（从长度字节开始到数据结束）
            checksum = sum(target_payload) & 0xFF
            target_packet = bytes([0xAA, 0x55]) + target_payload + bytes([checksum])
            serial.write(target_packet)

            time.sleep(0.02)

            # 发送激光位置
            laser_payload = bytes([
                0x04,  # 数据长度（4字节坐标数据）
                0x02,  # 命令：激光位置
                laser_x & 0xFF, (laser_x >> 8) & 0xFF,   # X坐标（小端）
                laser_y & 0xFF, (laser_y >> 8) & 0xFF    # Y坐标（小端）
            ])
            # 计算校验和（从长度字节开始到数据结束）
            checksum = sum(laser_payload) & 0xFF
            laser_packet = bytes([0xAA, 0x55]) + laser_payload + bytes([checksum])
            serial.write(laser_packet)

            print(f"第{i+1:2d}组: 目标({target_x:3d},{target_y:3d}) 激光({laser_x:3d},{laser_y:3d})")
            time.sleep(0.08)

        print("✓ 通信诊断完成")

    except Exception as e:
        print(f"✗ 通信诊断失败: {e}")
        import traceback
        traceback.print_exc()

def run_camera_test():
    """运行摄像头测试模式"""
    print("=" * 50)
    print("摄像头测试模式")
    print("=" * 50)

    try:
        from maix import image
        from image_processor import ImageProcessor
        config = Config()

        processor = ImageProcessor(config)
        print("摄像头初始化成功")

        frame_count = 0
        detection_count = 0

        while not app.need_exit() and frame_count < 300:
            img = processor.capture_image()
            if img is None:
                continue

            # 检测红色目标和绿色激光
            red_target = processor.detect_red_target(img)
            green_laser = processor.detect_green_laser(img)

            # 绘制检测结果
            if red_target:
                img.draw_circle(red_target[0], red_target[1], 10, image.COLOR_RED, 3)
                detection_count += 1

            if green_laser:
                img.draw_circle(green_laser[0], green_laser[1], 8, image.COLOR_GREEN, 3)
                detection_count += 1

            # 显示信息
            img.draw_string(10, 10, "Camera Test", image.COLOR_WHITE, 2)
            img.draw_string(10, 40, f"Frame: {frame_count}", image.COLOR_WHITE, 1.5)
            img.draw_string(10, 65, f"Detections: {detection_count}", image.COLOR_WHITE, 1.5)

            processor.display_image(img)
            frame_count += 1

        processor.close()
        print("✓ 摄像头测试完成")

    except Exception as e:
        print(f"✗ 摄像头测试失败: {e}")
        import traceback
        traceback.print_exc()

def main():
    """主函数 - 模式选择入口"""
    # 显示模式信息
    print_mode_info()

    # 获取运行模式
    run_mode = get_run_mode()

    # 配置串口2引脚映射（所有模式都需要）
    pinmap.set_pin_function("A29", "UART2_RX")
    pinmap.set_pin_function("A28", "UART2_TX")

    try:
        if run_mode == 1:
            print("启动激光追踪模式...")
            run_laser_tracking()
        elif run_mode == 2:
            print("启动通信诊断模式...")
            run_communication_diagnosis()
        elif run_mode == 3:
            print("启动摄像头测试模式...")
            run_camera_test()
        else:
            print("无效模式配置，默认运行激光追踪模式")
            run_laser_tracking()

    except KeyboardInterrupt:
        print("\n用户中断程序")
    except Exception as e:
        print(f"程序异常: {e}")
        import traceback
        traceback.print_exc()
    finally:
        print("程序结束")

if __name__ == "__main__":
    main()