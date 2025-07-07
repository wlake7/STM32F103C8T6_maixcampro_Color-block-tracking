#!/usr/bin/env python3
"""
测试模块导入
验证所有模块是否可以正常导入
"""

def test_imports():
    """测试所有模块导入"""
    print("开始测试模块导入...")
    
    try:
        print("1. 测试config模块...")
        from config import Config
        config = Config()
        print("   ✅ config模块导入成功")
        
        print("2. 测试communication模块...")
        from communication import Communication
        print("   ✅ communication模块导入成功")
        
        print("3. 测试image_processor模块...")
        from image_processor import ImageProcessor
        print("   ✅ image_processor模块导入成功")
        
        print("4. 测试laser_tracker模块...")
        from laser_tracker import LaserTracker
        print("   ✅ laser_tracker模块导入成功")
        
        print("5. 测试完整初始化...")
        tracker = LaserTracker(config)
        print("   ✅ LaserTracker初始化成功")
        
        print("\n🎉 所有模块导入测试通过！")
        return True
        
    except ImportError as e:
        print(f"   ❌ 导入错误: {e}")
        return False
    except Exception as e:
        print(f"   ❌ 其他错误: {e}")
        return False

if __name__ == "__main__":
    success = test_imports()
    if success:
        print("\n系统准备就绪，可以运行main.py")
    else:
        print("\n请检查模块导入问题")
