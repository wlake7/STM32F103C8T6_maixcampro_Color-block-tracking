/**
 * @file main.c
 * @brief STM32舵机控制测试程序
 * @version 1.0
 * @date 2025-07-09
 *
 * 功能：验证STM32是否能驱动舵机运动
 * 硬件：STM32F103C8T6 + 舵机控制板 + 双轴舵机
 * 通信：USART2 (PA2-TX, PA3-RX, 9600bps) 与舵机控制板
 */

#include "stm32f10x.h"
#include "Delay.h"
#include "Timer.h"
#include "CameraComm.h"
#include "LaserTracker.h"
#include "ServoBoard.h"
#include <string.h>

/* 根据修改要求：
 * 修改一：使用定时器1作为系统时间标准，SysTick专用延时
 * 修改二：在主函数中实现STM32端激光追踪功能
 * 修改三：集成摄像头通信和PID控制算法
 */


/* 宏开关模式控制 */
#define MODE_SERVO_TEST     1   // 舵机测试模式
#define MODE_LASER_TRACK    2   // 激光追踪模式
#define MODE_COMM_DEBUG     3   // 通信调试模式
#define MODE_DEBUG          4   // 调试模式 (预留)

/* 当前运行模式 */
#define CURRENT_MODE        MODE_COMM_DEBUG

/* 舵机控制板协议常量 */
#define SERVO_HEADER1       0x55
#define SERVO_HEADER2       0x55
#define CMD_SERVO_MOVE      3





/* LED状态指示 */
#define LED_PIN     GPIO_Pin_13
#define LED_PORT    GPIOC



/* 全局变量 */
static uint8_t g_system_initialized = 0;

/* 舵机测试相关变量 */
typedef enum {
    TEST_STEP_INIT = 0,
    TEST_STEP_CENTER,
    TEST_STEP_H_LEFT,
    TEST_STEP_H_RIGHT,
    TEST_STEP_V_UP,
    TEST_STEP_V_DOWN,
    TEST_STEP_CIRCLE,
    TEST_STEP_COUNT
} ServoTestStep_t;

static ServoTestStep_t g_test_step = TEST_STEP_INIT;
static uint32_t g_last_test_time = 0;
static uint32_t g_test_count = 0;

/* 函数声明 */
static void System_Init(void);
static void LED_Init(void);
static void LED_Toggle(void);
static void LED_SetState(uint8_t on);




#if CURRENT_MODE == MODE_SERVO_TEST
static void ServoTest_Process(void);
static void ServoTest_Init(void);
#elif CURRENT_MODE == MODE_COMM_DEBUG
static void CommDebug_Process(void);
static void CommDebug_Init(void);
#endif

/**
 * @brief 主函数
 */
int main(void)
{
    // 系统初始化
    System_Init();

    // LED指示初始化完成
    LED_SetState(0);  // 熄灭LED
    Delay_ms(500);
    LED_SetState(1);  // 点亮LED
    Delay_ms(500);
    LED_SetState(0);  // 熄灭LED

#if CURRENT_MODE == MODE_SERVO_TEST
    // 舵机测试初始化
    ServoTest_Init();

    // 主循环
    while (1) {
        ServoTest_Process();

        // LED心跳指示
        static uint32_t last_led_time = 0;
        if ((System_GetTick() - last_led_time) > 1000) {
            last_led_time = System_GetTick();
            LED_Toggle();
        }

        Delay_ms(2000);  // 20Hz主循环
    }

#elif CURRENT_MODE == MODE_LASER_TRACK
    // 激光追踪初始化
    LaserTracker_Init();

    // 主循环
    while (1) {
        LaserTracker_Process();

        // LED心跳指示
        static uint32_t last_led_time = 0;
        if ((System_GetTick() - last_led_time) > 1000) {
            last_led_time = System_GetTick();
            LED_Toggle();
        }

        Delay_ms(50);  // 20Hz主循环
    }

#elif CURRENT_MODE == MODE_COMM_DEBUG
    // 通信调试初始化
    CommDebug_Init();

    // 主循环
    while (1) {
        CommDebug_Process();

        // LED心跳指示
        static uint32_t last_led_time = 0;
        if ((System_GetTick() - last_led_time) > 1000) {
            last_led_time = System_GetTick();
            LED_Toggle();
        }

        Delay_ms(100);  // 10Hz主循环
    }

#endif

    return 0;
}

/**
 * @brief 系统初始化
 */
static void System_Init(void)
{
    // 配置SysTick为1ms中断（专用于延时）
    SysTick_Config(SystemCoreClock / 1000);

    // 初始化Timer1作为系统时间基准
    Timer1_Init();

    // LED初始化
    LED_Init();

    // 舵机控制板初始化
    ServoBoard_Init();

#if CURRENT_MODE == MODE_LASER_TRACK || CURRENT_MODE == MODE_COMM_DEBUG
    // 摄像头通信初始化
    CameraComm_Init();
#endif

    g_system_initialized = 1;
}

/**
 * @brief LED初始化
 */
static void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOC时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // 配置PC13为推挽输出
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);

    // 初始状态LED熄灭
    GPIO_SetBits(LED_PORT, LED_PIN);
}

/**
 * @brief LED状态切换
 */
static void LED_Toggle(void)
{
    if (GPIO_ReadOutputDataBit(LED_PORT, LED_PIN)) {
        GPIO_ResetBits(LED_PORT, LED_PIN);  // 点亮LED
    } else {
        GPIO_SetBits(LED_PORT, LED_PIN);    // 熄灭LED
    }
}

/**
 * @brief 设置LED状态
 */
static void LED_SetState(uint8_t on)
{
    if (on) {
        GPIO_ResetBits(LED_PORT, LED_PIN);  // 点亮LED
    } else {
        GPIO_SetBits(LED_PORT, LED_PIN);    // 熄灭LED
    }
}











#if CURRENT_MODE == MODE_SERVO_TEST

/**
 * @brief 舵机测试初始化
 */
static void ServoTest_Init(void)
{
    g_test_step = TEST_STEP_INIT;
    g_last_test_time = System_GetTick();
    g_test_count = 0;

    // 等待系统稳定
    Delay_ms(1000);

    // 舵机回到中心位置
    ServoBoard_ReturnToCenter();
    Delay_ms(1500);
}

/**
 * @brief 舵机测试处理函数
 */
static void ServoTest_Process(void)
{

    switch (g_test_step) {
        case TEST_STEP_INIT:
            // 初始化完成，开始测试
            g_test_step = TEST_STEP_CENTER;
            break;

        case TEST_STEP_CENTER:
            // 回到中心位置
            ServoBoard_ReturnToCenter();
            g_test_step = TEST_STEP_H_LEFT;
            break;

        case TEST_STEP_H_LEFT:
            // 水平舵机向左
            ServoBoard_MoveServo(SERVO_ID_HORIZONTAL, 200, 2000);
            g_test_step = TEST_STEP_H_RIGHT;
            break;

        case TEST_STEP_H_RIGHT:
            // 水平舵机向右
            ServoBoard_MoveServo(SERVO_ID_HORIZONTAL, 800, 2000);
            g_test_step = TEST_STEP_V_UP;
            break;

        case TEST_STEP_V_UP:
            // 垂直舵机向上
            ServoBoard_MoveServo(SERVO_ID_VERTICAL, 200, 2000);
            g_test_step = TEST_STEP_V_DOWN;
            break;

        case TEST_STEP_V_DOWN:
            // 垂直舵机向下
            ServoBoard_MoveServo(SERVO_ID_VERTICAL, 800, 2000);
            g_test_step = TEST_STEP_CIRCLE;
            break;

        case TEST_STEP_CIRCLE:
            // 圆形运动测试
            {
                static uint8_t circle_step = 0;
                uint16_t h_pos, v_pos;

                switch (circle_step) {
                    case 0: h_pos = 300; v_pos = 300; break;  // 左上
                    case 1: h_pos = 700; v_pos = 300; break;  // 右上
                    case 2: h_pos = 700; v_pos = 700; break;  // 右下
                    case 3: h_pos = 300; v_pos = 700; break;  // 左下
                    default: h_pos = 500; v_pos = 500; break; // 中心
                }

                ServoBoard_MoveHV(h_pos, v_pos, 1500);

                circle_step++;
                if (circle_step >= 5) {
                    circle_step = 0;
                    g_test_count++;
                    g_test_step = TEST_STEP_CENTER;
                }
            }
            break;

        default:
            g_test_step = TEST_STEP_CENTER;
            break;
    }
}

#endif

#if CURRENT_MODE == MODE_COMM_DEBUG

/* 通信调试相关变量 */
static uint32_t g_received_packets = 0;
static uint32_t g_target_packets = 0;
static uint32_t g_laser_packets = 0;
static uint32_t g_last_target_x = 0, g_last_target_y = 0;
static uint32_t g_last_laser_x = 0, g_last_laser_y = 0;

/**
 * @brief 通信调试初始化
 */
static void CommDebug_Init(void)
{
    // 初始化摄像头通信
    CameraComm_Init();

    // 舵机回到中心位置
    ServoBoard_ReturnToCenter();
    Delay_ms(1000);

    // LED指示初始化完成
    LED_SetState(1);
    Delay_ms(200);
    LED_SetState(0);
    Delay_ms(200);
    LED_SetState(1);
    Delay_ms(200);
    LED_SetState(0);
}

/**
 * @brief 通信调试处理函数
 */
static void CommDebug_Process(void)
{
    // 检查是否有新的摄像头数据
    TrackingData_t camera_data;
    if (CameraComm_GetLatestData(&camera_data)) {
        g_received_packets++;

        // 检查数据类型并统计
        if (camera_data.target.x != g_last_target_x || camera_data.target.y != g_last_target_y) {
            g_target_packets++;
            g_last_target_x = camera_data.target.x;
            g_last_target_y = camera_data.target.y;
        }

        if (camera_data.laser.x != g_last_laser_x || camera_data.laser.y != g_last_laser_y) {
            g_laser_packets++;
            g_last_laser_x = camera_data.laser.x;
            g_last_laser_y = camera_data.laser.y;
        }

        // 简单的舵机响应测试：根据目标位置移动舵机
        uint16_t servo_h = (uint16_t)((float)camera_data.target.x * 1000.0f / 640.0f);
        uint16_t servo_v = (uint16_t)((float)camera_data.target.y * 1000.0f / 480.0f);

        // 限幅
        if (servo_h > 1000) servo_h = 1000;
        if (servo_v > 1000) servo_v = 1000;

        // 发送舵机命令
        ServoBoard_MoveHV(servo_h, servo_v, 200);

        // LED闪烁指示收到数据
        LED_SetState(1);
        Delay_ms(10);
        LED_SetState(0);
    }

    // 每5秒输出统计信息（通过LED闪烁模式）
    static uint32_t last_stats_time = 0;
    uint32_t current_time = System_GetTick();
    if ((current_time - last_stats_time) > 5000) {
        last_stats_time = current_time;

        // 通过LED闪烁次数指示接收状态
        // 快闪：收到数据包总数/10
        // 慢闪：目标数据包数/5
        uint8_t total_blinks = (g_received_packets / 10) % 10;
        uint8_t target_blinks = (g_target_packets / 5) % 10;

        // 快闪指示总数据包
        for (uint8_t i = 0; i < total_blinks; i++) {
            LED_SetState(1);
            Delay_ms(100);
            LED_SetState(0);
            Delay_ms(100);
        }

        Delay_ms(500);

        // 慢闪指示目标数据包
        for (uint8_t i = 0; i < target_blinks; i++) {
            LED_SetState(1);
            Delay_ms(300);
            LED_SetState(0);
            Delay_ms(300);
        }
    }
}

#endif








