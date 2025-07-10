"""
测试所有模块导入是否正确
"""

def test_imports():
    """测试导入"""
    print("测试模块导入...")
    
    try:
        print("1. 测试config导入...")
        from config import Config
        config = Config()
        print("   ✓ config导入成功")
    except Exception as e:
        print(f"   ✗ config导入失败: {e}")
        return False
    
    try:
        print("2. 测试communication导入...")
        from communication import Communication
        comm = Communication(config)
        print("   ✓ communication导入成功")
    except Exception as e:
        print(f"   ✗ communication导入失败: {e}")
        return False
    
    try:
        print("3. 测试image_processor导入...")
        from image_processor import ImageProcessor
        processor = ImageProcessor(config)
        print("   ✓ image_processor导入成功")
    except Exception as e:
        print(f"   ✗ image_processor导入失败: {e}")
        return False
    
    try:
        print("4. 测试laser_tracker导入...")
        from laser_tracker import LaserTracker
        tracker = LaserTracker(config)
        print("   ✓ laser_tracker导入成功")
    except Exception as e:
        print(f"   ✗ laser_tracker导入失败: {e}")
        return False
    
    try:
        print("5. 测试run_config导入...")
        from run_config import get_run_mode, print_mode_info
        mode = get_run_mode()
        print(f"   ✓ run_config导入成功，当前模式: {mode}")
    except Exception as e:
        print(f"   ✗ run_config导入失败: {e}")
        return False
    
    print("\n🎉 所有模块导入测试通过！")
    return True

if __name__ == "__main__":
    test_imports()
