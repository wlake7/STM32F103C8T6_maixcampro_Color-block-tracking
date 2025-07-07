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
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "Communication.h"
#include "ControlBoard.h"
#include "PID.h"
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
#define SYSTEM_BAUDRATE             115200      // 通信波特率
#define SYSTEM_LOOP_FREQUENCY       50          // 主循环频率(Hz)
#define SYSTEM_LOOP_PERIOD          (1000/SYSTEM_LOOP_FREQUENCY)  // 主循环周期(ms)
#define HEARTBEAT_INTERVAL          1000        // 心跳间隔(ms)
#define STATUS_UPDATE_INTERVAL      100         // 状态更新间隔(ms)
#define OLED_UPDATE_INTERVAL        200         // OLED更新间隔(ms)

/* 全局变量 */
static SystemState_t g_system_state = SYSTEM_STATE_INIT;
static bool g_system_ready = false;
static uint32_t g_last_heartbeat = 0;
static uint32_t g_last_status_update = 0;
static uint32_t g_last_oled_update = 0;
// static uint32_t g_system_tick = 0;  // 系统时钟计数器 (暂未使用)

/* 追踪控制变量 */
static PositionData_t g_target_position = {0};
static PositionData_t g_laser_position = {0};
static float g_horizontal_output = 0.0f;
static float g_vertical_output = 0.0f;

/* 函数声明 */
static bool System_Init(void);
static void System_MainLoop(void);
static void System_ProcessCommunication(void);
static void System_UpdateTracking(void);
static void System_UpdateDisplay(void);
static void System_SendHeartbeat(void);
static void System_SendStatus(void);
static void System_HandleError(void);
static void System_ProcessKeys(void);
static void Communication_DataHandler(CommCommand_t cmd, uint8_t* data, uint8_t length);
static uint32_t System_GetTick(void);
static void System_Delay(uint32_t ms);
static void System_TestServoMotors(void);

/**
 * @brief 主函数
 */
int main(void)
{
    // 系统初始化
    if (!System_Init()) {
        g_system_state = SYSTEM_STATE_ERROR;
    }

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
    // 基础模块初始化
    OLED_Init();
    LED_Init();
    Key_Init();

    // 显示启动信息
    OLED_Clear();
    OLED_ShowString(1, 1, "Laser Tracker");
    OLED_ShowString(2, 1, "Initializing...");

    // 通信模块初始化
    if (!Communication_Init(SYSTEM_BAUDRATE, Communication_DataHandler)) {
        OLED_ShowString(3, 1, "Comm Init Failed");
        return false;
    }

    // 控制板通信模块初始化
    if (!ControlBoard_Init()) {
        OLED_ShowString(3, 1, "CtrlBoard Failed");
        return false;
    }

    // PID控制器初始化
    if (!PID_Init()) {
        OLED_ShowString(3, 1, "PID Init Failed");
        return false;
    }

    // 设置PID参数
    PID_SetParams(PID_TYPE_HORIZONTAL, 2.0f, 0.1f, 0.5f);
    PID_SetParams(PID_TYPE_VERTICAL, 2.5f, 0.15f, 0.6f);

    // 启用PID控制器
    PID_Enable(PID_TYPE_HORIZONTAL, true);
    PID_Enable(PID_TYPE_VERTICAL, true);

    // 初始化时间变量
    g_last_heartbeat = System_GetTick();
    g_last_status_update = System_GetTick();
    g_last_oled_update = System_GetTick();

    // 设置系统状态
    g_system_state = SYSTEM_STATE_CALIBRATION;
    g_system_ready = true;

    // 显示初始化完成
    OLED_ShowString(3, 1, "Init Complete");
    System_Delay(1000);

    return true;
}

/**
 * @brief 系统主循环
 */
static void System_MainLoop(void)
{
    uint32_t current_tick = System_GetTick();

    // 更新系统时钟
    // g_system_tick = current_tick;  // 暂未使用

    // 处理通信数据
    System_ProcessCommunication();

    // 处理按键输入
    System_ProcessKeys();

    // 根据系统状态执行相应逻辑
    switch (g_system_state) {
        case SYSTEM_STATE_CALIBRATION:
            // 标定模式 - 舵机移动到中心位置
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1000);
            ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1000);
            break;

        case SYSTEM_STATE_TRACKING:
            // 追踪模式 - 执行PID控制
            System_UpdateTracking();
            break;

        case SYSTEM_STATE_MANUAL:
            // 手动控制模式 - 可以在这里调用舵机测试
            System_TestServoMotors();
            break;

        case SYSTEM_STATE_ERROR:
            // 错误处理
            System_HandleError();
            break;

        default:
            break;
    }

    // 定期发送心跳
    if (current_tick - g_last_heartbeat >= HEARTBEAT_INTERVAL) {
        System_SendHeartbeat();
        g_last_heartbeat = current_tick;
    }

    // 定期发送状态
    if (current_tick - g_last_status_update >= STATUS_UPDATE_INTERVAL) {
        System_SendStatus();
        g_last_status_update = current_tick;
    }

    // 定期更新显示
    if (current_tick - g_last_oled_update >= OLED_UPDATE_INTERVAL) {
        System_UpdateDisplay();
        g_last_oled_update = current_tick;
    }

    // 处理模块
    Communication_Process();
    ControlBoard_Process();
    PID_Process();
}

/**
 * @brief 处理通信数据
 */
static void System_ProcessCommunication(void)
{
    // 通信模块会通过回调函数处理数据
    // 这里可以添加额外的通信处理逻辑
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
 * @brief 更新显示
 */
static void System_UpdateDisplay(void)
{
    char buffer[16];

    OLED_Clear();

    // 显示系统状态
    switch (g_system_state) {
        case SYSTEM_STATE_INIT:
            OLED_ShowString(1, 1, "State: INIT");
            break;
        case SYSTEM_STATE_CALIBRATION:
            OLED_ShowString(1, 1, "State: CALIB");
            break;
        case SYSTEM_STATE_TRACKING:
            OLED_ShowString(1, 1, "State: TRACK");
            break;
        case SYSTEM_STATE_MANUAL:
            OLED_ShowString(1, 1, "State: MANUAL");
            break;
        case SYSTEM_STATE_ERROR:
            OLED_ShowString(1, 1, "State: ERROR");
            break;
    }

    // 显示目标位置
    sprintf(buffer, "T:%d,%d", g_target_position.x, g_target_position.y);
    OLED_ShowString(2, 1, buffer);

    // 显示激光位置
    sprintf(buffer, "L:%d,%d", g_laser_position.x, g_laser_position.y);
    OLED_ShowString(3, 1, buffer);

    // 显示PID输出
    sprintf(buffer, "O:%.1f,%.1f", g_horizontal_output, g_vertical_output);
    OLED_ShowString(4, 1, buffer);
}

/**
 * @brief 发送心跳包
 */
static void System_SendHeartbeat(void)
{
    Communication_SendHeartbeat();
}

/**
 * @brief 发送系统状态
 */
static void System_SendStatus(void)
{
    SystemStatus_t status;
    status.system_ready = g_system_ready ? 1 : 0;
    status.servo_status = ControlBoard_IsCommOK() ? 1 : 0; // 控制板通信状态
    status.tracking_mode = (uint8_t)g_system_state;
    status.error_code = 0;

    Communication_SendSystemStatus(&status);
}

/**
 * @brief 错误处理
 */
static void System_HandleError(void)
{
    // LED闪烁指示错误
    static uint32_t last_led_toggle = 0;
    uint32_t current_tick = System_GetTick();

    if (current_tick - last_led_toggle >= 500) {
        LED1_Turn();
        last_led_toggle = current_tick;
    }

    // 停止所有动作组
    ControlBoard_StopActionGroup();

    // 禁用PID控制器
    PID_Enable(PID_TYPE_HORIZONTAL, false);
    PID_Enable(PID_TYPE_VERTICAL, false);
}

/**
 * @brief 处理按键输入
 */
static void System_ProcessKeys(void)
{
    uint8_t key_num = Key_GetNum();

    if (key_num == 1) {
        // 按键1: 切换系统状态
        switch (g_system_state) {
            case SYSTEM_STATE_CALIBRATION:
                g_system_state = SYSTEM_STATE_TRACKING;
                PID_Enable(PID_TYPE_HORIZONTAL, true);
                PID_Enable(PID_TYPE_VERTICAL, true);
                break;
            case SYSTEM_STATE_TRACKING:
                g_system_state = SYSTEM_STATE_MANUAL;
                PID_Enable(PID_TYPE_HORIZONTAL, false);
                PID_Enable(PID_TYPE_VERTICAL, false);
                break;
            case SYSTEM_STATE_MANUAL:
                g_system_state = SYSTEM_STATE_CALIBRATION;
                break;
            default:
                break;
        }
    }
    else if (key_num == 2) {
        // 按键2: 启动舵机测试
        System_TestServoMotors();
    }
}

/**
 * @brief 通信数据处理回调函数
 */
static void Communication_DataHandler(CommCommand_t cmd, uint8_t* data, uint8_t length)
{
    switch (cmd) {
        case CMD_TARGET_POSITION:
            if (length >= 16) {
                // 解析目标位置数据 (前8字节)
                g_target_position.x = data[0] | (data[1] << 8);
                g_target_position.y = data[2] | (data[3] << 8);
                g_target_position.confidence = data[4] | (data[5] << 8);
                g_target_position.timestamp = data[6] | (data[7] << 8);

                // 解析激光位置数据 (后8字节)
                g_laser_position.x = data[8] | (data[9] << 8);
                g_laser_position.y = data[10] | (data[11] << 8);
                g_laser_position.confidence = data[12] | (data[13] << 8);
                g_laser_position.timestamp = data[14] | (data[15] << 8);
            }
            break;

        case CMD_LASER_POSITION:
            // 激光位置数据已包含在CMD_TARGET_POSITION中，此命令保留备用
            break;

        case CMD_PID_PARAMS:
            if (length >= 12) {
                // 解析PID参数
                uint16_t kp_h = data[0] | (data[1] << 8);
                uint16_t ki_h = data[2] | (data[3] << 8);
                uint16_t kd_h = data[4] | (data[5] << 8);
                uint16_t kp_v = data[6] | (data[7] << 8);
                uint16_t ki_v = data[8] | (data[9] << 8);
                uint16_t kd_v = data[10] | (data[11] << 8);

                // 转换为浮点数 (除以100)
                PID_SetParams(PID_TYPE_HORIZONTAL, kp_h/100.0f, ki_h/100.0f, kd_h/100.0f);
                PID_SetParams(PID_TYPE_VERTICAL, kp_v/100.0f, ki_v/100.0f, kd_v/100.0f);
            }
            break;

        case CMD_CALIBRATION:
            // 进入标定模式
            g_system_state = SYSTEM_STATE_CALIBRATION;
            PID_Reset(PID_TYPE_HORIZONTAL);
            PID_Reset(PID_TYPE_VERTICAL);
            break;

        case CMD_HEARTBEAT:
            // 心跳响应
            break;

        default:
            break;
    }
}

/**
 * @brief 获取系统时钟
 */
static uint32_t System_GetTick(void)
{
    // 这里应该返回系统时钟，暂时使用简单计数器
    static uint32_t tick_counter = 0;
    return tick_counter++;
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
    static bool test_running = false;
    static uint32_t test_start_time = 0;
    static uint8_t test_step = 0;
    uint32_t current_time = System_GetTick();

    // 如果测试未开始，启动测试
    if (!test_running) {
        test_running = true;
        test_start_time = current_time;
        test_step = 0;

        // 显示测试开始信息
        OLED_ShowString(3, 1, "Servo Test Start");
        OLED_ShowString(4, 1, "Press Key2 Stop ");

        // LED指示测试状态
        LED_On();

        printf("开始舵机测试...\r\n");
        return;
    }

    // 检查是否按键停止测试
    if (Key_GetNum() == 2) {
        test_running = false;
        LED_Off();
        OLED_ShowString(3, 1, "Servo Test Stop ");
        OLED_ShowString(4, 1, "               ");
        printf("舵机测试停止\r\n");

        // 舵机回到中心位置
        ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1000);
        ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1000);
        return;
    }

    // 测试循环 - 每2秒切换一个动作
    uint32_t elapsed_time = current_time - test_start_time;
    uint8_t current_step = (elapsed_time / 2000) % 8;  // 8个步骤循环

    if (current_step != test_step) {
        test_step = current_step;

        switch (test_step) {
            case 0:
                // 水平舵机向左，垂直舵机中心
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 200, 1500);
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1500);
                printf("舵机测试: 水平左, 垂直中\r\n");
                break;

            case 1:
                // 水平舵机向右，垂直舵机中心
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 800, 1500);
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 500, 1500);
                printf("舵机测试: 水平右, 垂直中\r\n");
                break;

            case 2:
                // 水平舵机中心，垂直舵机向上
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1500);
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 200, 1500);
                printf("舵机测试: 水平中, 垂直上\r\n");
                break;

            case 3:
                // 水平舵机中心，垂直舵机向下
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 500, 1500);
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 800, 1500);
                printf("舵机测试: 水平中, 垂直下\r\n");
                break;

            case 4:
                // 左上角
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 200, 1500);
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 200, 1500);
                printf("舵机测试: 左上角\r\n");
                break;

            case 5:
                // 右上角
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 800, 1500);
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 200, 1500);
                printf("舵机测试: 右上角\r\n");
                break;

            case 6:
                // 右下角
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 800, 1500);
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 800, 1500);
                printf("舵机测试: 右下角\r\n");
                break;

            case 7:
                // 左下角
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_HORIZONTAL, 200, 1500);
                ControlBoard_MoveServo(CONTROL_BOARD_SERVO_ID_VERTICAL, 800, 1500);
                printf("舵机测试: 左下角\r\n");
                break;
        }

        // 更新OLED显示当前步骤
        char step_str[16];
        sprintf(step_str, "Step: %d/8      ", test_step + 1);
        OLED_ShowString(4, 1, step_str);

        // LED闪烁指示
        if (test_step % 2 == 0) {
            LED_On();
        } else {
            LED_Off();
        }
    }
}
