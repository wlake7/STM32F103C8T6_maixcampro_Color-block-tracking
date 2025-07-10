"""
运行模式配置文件
修改这个文件来选择要运行的模式
"""

# 运行模式选择
# 1: 激光追踪模式 (完整功能)
# 2: 通信诊断模式 (测试与STM32通信)
# 3: 摄像头测试模式 (测试图像检测)
RUN_MODE = 1  # 当前使用通信诊断模式测试串口1通信

# 模式说明
MODE_DESCRIPTIONS = {
    1: "激光追踪模式 - 完整的激光追踪功能",
    2: "通信诊断模式 - 测试与STM32的串口通信",
    3: "摄像头测试模式 - 测试图像检测功能"
}

def get_run_mode():
    """获取当前运行模式"""
    return RUN_MODE

def get_mode_description(mode):
    """获取模式描述"""
    return MODE_DESCRIPTIONS.get(mode, "未知模式")

def print_mode_info():
    """打印当前模式信息"""
    print("=" * 50)
    print("MaixCam激光追踪系统")
    print("=" * 50)
    print("可用模式:")
    for mode, desc in MODE_DESCRIPTIONS.items():
        marker = " ← 当前模式" if mode == RUN_MODE else ""
        print(f"  {mode}: {desc}{marker}")
    print("=" * 50)
    print(f"当前运行模式: {RUN_MODE} - {get_mode_description(RUN_MODE)}")
    print("要更改模式，请修改 run_config.py 中的 RUN_MODE 变量")
    print("=" * 50)
