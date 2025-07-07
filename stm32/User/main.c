/**
 * @file main.c
 * @brief STM32激光追踪系统主程序
 * @author AI Assistant
 * @date 2025-07-06
 *
 * 集成通信协议、舵机控制、PID控制器等模块，实现完整的激光追踪系统
 */

#include "stm32f10x.h"
#include "Delay.h"
#include "ControlBoard.h"
#include <stdio.h>
#include <string.h>

/* 系统状态定义 */
typedef enum {
    SYSTEM_STATE_INIT = 0,          // 初始化状态
    SYSTEM_STATE_CALIBRATION,       // 标定状态
    SYSTEM_STATE_TRACKING,          // 追踪状态
    SYSTEM_STATE_MANUAL,            // 手动控制状态
    SYSTEM_STATE_ERROR              // 错误状态
} SystemState_t;

/* 系统配置 */
#define SYSTEM_LOOP_FREQUENCY       50          // 主循环频率(Hz)
#define SYSTEM_LOOP_PERIOD          (1000/SYSTEM_LOOP_FREQUENCY)  // 主循环周期(ms)

/* 全局变量 */
static SystemState_t g_system_state = SYSTEM_STATE_CALIBRATION;
static bool g_system_ready = false;
static uint32_t g_last_heartbeat = 0;
static uint32_t g_last_status_update = 0;

/* 测试模式相关变量 */
typedef enum {
    TEST_STEP_H_LEFT = 0,
    TEST_STEP_H_RIGHT,
    TEST_STEP_V_UP,
    TEST_STEP_V_DOWN,
    TEST_STEP_TOP_LEFT,
    TEST_STEP_TOP_RIGHT,
    TEST_STEP_BOTTOM_RIGHT,
    TEST_STEP_BOTTOM_LEFT,
    TEST_STEP_CENTER,
    TEST_STEP_COUNT
} TestStep_t;

static TestStep_t g_test_step = TEST_STEP_H_LEFT;
static uint32_t g_test_last_time = 0;
static bool g_test_mode_active = false;

/* 函数声明 */
static bool System_Init(void);
static void System_MainLoop(void);
uint32_t System_GetTick(void);
static void System_Delay(uint32_t ms);
static void System_TestServoMotors(void);
static void System_UpdateTestMode(void);
static void System_StartTestMode(void);

/**
 * @brief 主函数
 */
int main(void)
{
    // 系统初始化
    if (!System_Init()) {
        g_system_state = SYSTEM_STATE_ERROR;
        while(1); // 初始化失败，停止运行
    }

    // 启动测试模式
    System_StartTestMode();

    // 主循环
    while (1) {
        System_MainLoop();
        System_Delay(SYSTEM_LOOP_PERIOD);
    }
}

/**
 * @brief 系统初始化
 */
static bool System_Init(void)
{
    // 基础延时初始化
    Delay_Init();

    // 控制板通信模块初始化
    if (!ControlBoard_Init()) {
        printf("ControlBoard Init Failed\r\n");
        return false;
    }

    // 基础USART2测试
    printf("USART2 Hardware Test\r\n");
    printf("Sending test data to control board...\r\n");

    // 初始化时间变量
    g_last_heartbeat = System_GetTick();
    g_last_status_update = System_GetTick();

    // 设置系统状态为手动模式（测试模式）
    g_system_state = SYSTEM_STATE_CALIBRATION;
    g_system_ready = true;

    // 显示初始化完成
    OLED_ShowString(3, 1, "Init Complete");
    System_Delay(1000);

    // 自动启动测试模式
    System_StartTestMode();

    return true;
}

/**
 * @brief 系统主循环
 */
static void System_MainLoop(void)
{
    uint32_t current_tick = System_GetTick();

    // 根据系统状态执行相应逻辑
    switch (g_system_state) {
        case SYSTEM_STATE_CALIBRATION:
            // 标定模式 - 舵机移动到中心位置
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1000);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1000);
            break;

        case SYSTEM_STATE_MANUAL:
            // 手动控制模式 - 执行测试模式状态机
            System_UpdateTestMode();
            break;

        default:
            break;
    }

    // 处理控制板模块
    ControlBoard_Process();
}



/**
 * @brief 更新追踪控制
 */
static void System_UpdateTracking(void)
{
    // 计算目标位置与激光位置的差值
    float horizontal_error = (float)(g_target_position.x - g_laser_position.x);
    float vertical_error = (float)(g_target_position.y - g_laser_position.y);

    // PID控制计算
    g_horizontal_output = PID_Compute(PID_TYPE_HORIZONTAL, horizontal_error);
    g_vertical_output = PID_Compute(PID_TYPE_VERTICAL, vertical_error);

    // 将PID输出转换为舵机位置
    static uint16_t current_h_position = 500;  // 水平舵机当前位置
    static uint16_t current_v_position = 500;  // 垂直舵机当前位置

    // 计算新的舵机位置 (基于当前位置调整)
    int16_t new_h_position = current_h_position + (int16_t)(g_horizontal_output * 0.1f);
    int16_t new_v_position = current_v_position + (int16_t)(g_vertical_output * 0.1f);

    // 位置限制 (0-1000)
    if (new_h_position < 0) new_h_position = 0;
    if (new_h_position > 1000) new_h_position = 1000;
    if (new_v_position < 0) new_v_position = 0;
    if (new_v_position > 1000) new_v_position = 1000;

    // 更新当前位置
    current_h_position = new_h_position;
    current_v_position = new_v_position;

    // 控制舵机移动
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, current_h_position, 100);
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, current_v_position, 100);
}



/**
 * @brief 获取系统时钟
 */
uint32_t System_GetTick(void)
{
    // 使用SysTick计数器获取毫秒时间
    // 假设SysTick配置为1ms中断，72MHz系统时钟
    static uint32_t tick_ms = 0;
    static uint32_t last_systick = 0;

    // 简单的毫秒计数器实现
    // 在实际项目中应该使用SysTick中断或HAL_GetTick()
    tick_ms++;
    return tick_ms;
}

/**
 * @brief 系统延时
 */
static void System_Delay(uint32_t ms)
{
    Delay_ms(ms);
}

/**
 * @brief 舵机电机测试函数
 * 让两个舵机循环运动，检测是否能正常控制电机
 */
static void System_TestServoMotors(void)
{
    printf("Starting servo test sequence...\r\n");

    // 位置1: 水平舵机向左，垂直舵机中心
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 200, 1500);
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1500);
    printf("Servo test: H-Left, V-Center\r\n");
    System_Delay(2000);

    // 位置2: 水平舵机向右，垂直舵机中心
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 800, 1500);
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1500);
    printf("Servo test: H-Right, V-Center\r\n");
    System_Delay(2000);

    // 位置3: 水平舵机中心，垂直舵机向上
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1500);
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 200, 1500);
    printf("Servo test: H-Center, V-Up\r\n");
    System_Delay(2000);

    // 位置4: 水平舵机中心，垂直舵机向下
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1500);
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 800, 1500);
    printf("Servo test: H-Center, V-Down\r\n");
    System_Delay(2000);

    // 位置5: 左上角
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 200, 1500);
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 200, 1500);
    printf("Servo test: Top-Left\r\n");
    System_Delay(2000);

    // 位置6: 右上角
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 800, 1500);
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 200, 1500);
    printf("Servo test: Top-Right\r\n");
    System_Delay(2000);

    // 位置7: 右下角
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 800, 1500);
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 800, 1500);
    printf("Servo test: Bottom-Right\r\n");
    System_Delay(2000);

    // 位置8: 左下角
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 200, 1500);
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 800, 1500);
    printf("Servo test: Bottom-Left\r\n");
    System_Delay(2000);

    // 回到中心位置
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1500);
    ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1500);
    printf("Servo test: Center - Test complete\r\n");
    System_Delay(2000);
}

/**
 * @brief 启动测试模式
 */
static void System_StartTestMode(void)
{
    g_test_mode_active = true;
    g_test_step = TEST_STEP_H_LEFT;
    g_test_last_time = System_GetTick();
    g_system_state = SYSTEM_STATE_MANUAL;
    printf("Servo test started\r\n");
}

/**
 * @brief 更新测试模式状态机
 */
static void System_UpdateTestMode(void)
{
    if (!g_test_mode_active) {
        return;
    }

    uint32_t current_time = System_GetTick();

    // 每2秒切换一个测试步骤
    if ((current_time - g_test_last_time) < 2000) {
        return;
    }

    g_test_last_time = current_time;

    switch (g_test_step) {
        case TEST_STEP_H_LEFT:
            // 位置1: 水平舵机向左，垂直舵机中心
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 200, 1500);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1500);
            printf("Servo test: H-Left, V-Center\r\n");
            break;

        case TEST_STEP_H_RIGHT:
            // 位置2: 水平舵机向右，垂直舵机中心
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 800, 1500);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1500);
            printf("Servo test: H-Right, V-Center\r\n");
            break;

        case TEST_STEP_V_UP:
            // 位置3: 水平舵机中心，垂直舵机向上
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1500);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 200, 1500);
            printf("Servo test: H-Center, V-Up\r\n");
            break;

        case TEST_STEP_V_DOWN:
            // 位置4: 水平舵机中心，垂直舵机向下
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1500);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 800, 1500);
            printf("Servo test: H-Center, V-Down\r\n");
            break;

        case TEST_STEP_TOP_LEFT:
            // 位置5: 左上角
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 200, 1500);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 200, 1500);
            printf("Servo test: Top-Left\r\n");
            break;

        case TEST_STEP_TOP_RIGHT:
            // 位置6: 右上角
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 800, 1500);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 200, 1500);
            printf("Servo test: Top-Right\r\n");
            break;

        case TEST_STEP_BOTTOM_RIGHT:
            // 位置7: 右下角
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 800, 1500);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 800, 1500);
            printf("Servo test: Bottom-Right\r\n");
            break;

        case TEST_STEP_BOTTOM_LEFT:
            // 位置8: 左下角
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 200, 1500);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 800, 1500);
            printf("Servo test: Bottom-Left\r\n");
            break;

        case TEST_STEP_CENTER:
            // 回到中心位置，准备下一轮循环
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1500);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1500);
            printf("Servo test: Center - Next cycle\r\n");
            break;

        default:
            g_test_step = TEST_STEP_H_LEFT;
            return;
    }

    // 切换到下一个测试步骤
    g_test_step = (TestStep_t)((g_test_step + 1) % TEST_STEP_COUNT);
}
