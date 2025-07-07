"""
激光追踪系统 - MaixCam端主程序
实现红色色块和绿色激光的实时检测与追踪
"""

from maix import camera, display, image, app, time
from laser_tracker import LaserTracker
from config import Config
import sys

def main():
    """主函数"""
    print("=" * 50)
    print("激光追踪系统启动")
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
    finally:
        print("程序结束")

if __name__ == "__main__":
    main()