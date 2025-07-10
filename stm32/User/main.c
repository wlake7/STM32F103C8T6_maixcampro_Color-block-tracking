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
#include "OLED.h"
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
#define MODE_SERVO_DEBUG    4   // 舵机专项调试模式
#define MODE_CONTROL_TEST   5   // 控制方向测试模式
#define MODE_DEBUG          6   // 调试模式 (预留)

/* 当前运行模式 */
#define CURRENT_MODE       MODE_LASER_TRACK
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
#elif CURRENT_MODE == MODE_SERVO_DEBUG
static void ServoDebug_Process(void);
static void ServoDebug_Init(void);
#elif CURRENT_MODE == MODE_CONTROL_TEST
static void ControlTest_Process(void);
static void ControlTest_Init(void);
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
        CameraComm_Process(); // 处理摄像头通信数据
        LaserTracker_Process();

        // LED心跳指示
        static uint32_t last_led_time = 0;
        if ((System_GetTick() - last_led_time) > 1000) {
            last_led_time = System_GetTick();
            LED_Toggle();
        }

        Delay_ms(20);  // 50Hz主循环，提高响应速度
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

#elif CURRENT_MODE == MODE_SERVO_DEBUG
    // 舵机专项调试初始化
    ServoDebug_Init();

    // 主循环
    while (1) {
        ServoDebug_Process();

        // LED心跳指示
        static uint32_t last_led_time = 0;
        if ((System_GetTick() - last_led_time) > 1000) {
            last_led_time = System_GetTick();
            LED_Toggle();
        }

        Delay_ms(1000);  // 1Hz主循环，便于观察
    }

#elif CURRENT_MODE == MODE_CONTROL_TEST
    // 控制方向测试初始化
    ControlTest_Init();

    // 主循环
    while (1) {
        ControlTest_Process();

        // LED心跳指示
        static uint32_t last_led_time = 0;
        if ((System_GetTick() - last_led_time) > 1000) {
            last_led_time = System_GetTick();
            LED_Toggle();
        }

        Delay_ms(2000);  // 2秒一次测试
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

    // OLED初始化
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(1, 1, "STM32 Laser Track");
    OLED_ShowString(2, 1, "Initializing...");

    // 舵机控制板初始化
    ServoBoard_Init();

#if CURRENT_MODE == MODE_LASER_TRACK || CURRENT_MODE == MODE_COMM_DEBUG
    // 摄像头通信初始化
    CameraComm_Init();
#endif

    // 显示初始化完成
    OLED_ShowString(2, 1, "Init Complete   ");
    OLED_ShowString(3, 1, "Mode: ");
#if CURRENT_MODE == MODE_SERVO_TEST
    OLED_ShowString(3, 7, "SERVO_TEST");
#elif CURRENT_MODE == MODE_LASER_TRACK
    OLED_ShowString(3, 7, "LASER_TRACK");
#elif CURRENT_MODE == MODE_COMM_DEBUG
    OLED_ShowString(3, 7, "COMM_DEBUG");
#elif CURRENT_MODE == MODE_SERVO_DEBUG
    OLED_ShowString(3, 7, "SERVO_DEBUG");
#elif CURRENT_MODE == MODE_CONTROL_TEST
    OLED_ShowString(3, 7, "CTRL_TEST");
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
static void 
CommDebug_Init(void)
{
    // OLED显示调试模式信息
    OLED_Clear();
    OLED_ShowString(1, 1, "COMM DEBUG MODE");
    OLED_ShowString(2, 1, "Waiting data...");
    OLED_ShowString(3, 1, "RX: 0");
    OLED_ShowString(4, 1, "Servo: 500,500");

    // 启用舵机OLED调试
    ServoBoard_EnableOLEDDebug(true);

    // 初始化摄像头通信，在系统初始化中已经初始化了，所有我注释掉了
    //CameraComm_Init();

    // 舵机回到中心位置
    OLED_ShowString(2, 1, "Servo centering");
    ServoBoard_ReturnToCenter();
    Delay_ms(2000);  // 延长等待时间，观察OLED显示

    // 显示就绪状态
    OLED_Clear();
    OLED_ShowString(1, 1, "COMM DEBUG READY");
    OLED_ShowString(2, 1, "Waiting MaixCam");
    OLED_ShowString(3, 1, "RX: 0");
    OLED_ShowString(4, 1, "Servo: 500,500");

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
    // 首先处理摄像头通信数据
    CameraComm_Process();

    // 检查通信状态
    bool comm_ok = CameraComm_IsCommOK();
    CameraCommStats_t* stats = CameraComm_GetStats();

    // 更新OLED显示通信状态
    static uint32_t last_display_update = 0;
    uint32_t current_time = System_GetTick();

    if ((current_time - last_display_update) > 200) {  // 每200ms更新一次显示
        last_display_update = current_time;

        // 第1行：通信状态
        if (comm_ok) {
            OLED_ShowString(1, 1, "COMM: OK      ");
        } else {
            OLED_ShowString(1, 1, "COMM: TIMEOUT ");
        }

        // 第2行：接收统计
        OLED_ShowString(2, 1, "RX:");
        OLED_ShowNum(2, 4, stats->packets_received, 4);
        OLED_ShowString(2, 9, "ERR:");
        OLED_ShowNum(2, 13, stats->packets_error, 3);

        // 第3行和第4行：最新数据
        TrackingData_t camera_data;
        if (CameraComm_GetLatestData(&camera_data)) {
            // 第3行：目标位置
            OLED_ShowString(3, 1, "T:");
            if (camera_data.target.valid) {
                OLED_ShowSignedNum(3, 3, camera_data.target.x, 3);
                OLED_ShowString(3, 6, ",");
                OLED_ShowSignedNum(3, 7, camera_data.target.y, 3);
            } else {
                OLED_ShowString(3, 3, "---,---");
            }

            // 第4行：激光位置
            OLED_ShowString(4, 1, "L:");
            if (camera_data.laser.valid) {
                OLED_ShowSignedNum(4, 3, camera_data.laser.x, 3);
                OLED_ShowString(4, 6, ",");
                OLED_ShowSignedNum(4, 7, camera_data.laser.y, 3);
            } else {
                OLED_ShowString(4, 3, "---,---");
            }

            // 如果有有效数据，进行舵机测试
            if (camera_data.target.valid) {
                // 简单的舵机响应测试：根据目标位置移动舵机
                uint16_t servo_h = (uint16_t)((float)camera_data.target.x * 1000.0f / 640.0f);
                uint16_t servo_v = (uint16_t)((float)camera_data.target.y * 1000.0f / 480.0f);

                // 限幅
                if (servo_h > 1000) servo_h = 1000;
                if (servo_v > 1000) servo_v = 1000;

                // 发送舵机命令
                ServoBoard_MoveHV(servo_h, servo_v, 200);

                // 显示舵机位置
                OLED_ShowString(3, 11, "S:");
                OLED_ShowNum(3, 13, servo_h, 3);
                OLED_ShowString(4, 11, "S:");
                OLED_ShowNum(4, 13, servo_v, 3);

                // LED闪烁指示收到数据
                LED_SetState(1);
                Delay_ms(10);
                LED_SetState(0);
            }
        } else {
            // 没有数据时显示等待状态
            OLED_ShowString(3, 1, "T: Waiting... ");
            OLED_ShowString(4, 1, "L: Waiting... ");
        }
    }

    // 每5秒输出统计信息（通过LED闪烁模式）
    static uint32_t last_stats_time = 0;
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

#if CURRENT_MODE == MODE_SERVO_DEBUG

/* 舵机调试相关变量 */
static uint32_t g_servo_test_step = 0;
static uint32_t g_servo_test_count = 0;

/**
 * @brief 舵机专项调试初始化
 */
static void ServoDebug_Init(void)
{
    // OLED显示调试模式信息
    OLED_Clear();
    OLED_ShowString(1, 1, "SERVO DEBUG MODE");
    OLED_ShowString(2, 1, "Testing servo...");
    OLED_ShowString(3, 1, "Step: 0");
    OLED_ShowString(4, 1, "Count: 0");

    // 启用舵机OLED调试
    ServoBoard_EnableOLEDDebug(true);

    // 舵机回到中心位置
    OLED_ShowString(2, 1, "Centering...   ");
    ServoBoard_ReturnToCenter();
    Delay_ms(2000);

    // 显示就绪状态
    OLED_ShowString(2, 1, "Ready to test  ");

    // LED指示初始化完成
    for (int i = 0; i < 3; i++) {
        LED_SetState(1);
        Delay_ms(200);
        LED_SetState(0);
        Delay_ms(200);
    }
}

/**
 * @brief 舵机专项调试处理函数
 */
static void ServoDebug_Process(void)
{
    g_servo_test_count++;

    // 更新OLED显示
    OLED_ShowString(3, 1, "Step:");
    OLED_ShowNum(3, 6, g_servo_test_step, 2);
    OLED_ShowString(4, 1, "Count:");
    OLED_ShowNum(4, 7, g_servo_test_count, 4);

    switch (g_servo_test_step) {
        case 0:
            // 测试中心位置
            OLED_ShowString(2, 1, "Test: CENTER   ");
            ServoBoard_MoveHV(500, 500, 1000);
            break;

        case 1:
            // 测试左上角
            OLED_ShowString(2, 1, "Test: LEFT-UP  ");
            ServoBoard_MoveHV(200, 200, 1000);
            break;

        case 2:
            // 测试右上角
            OLED_ShowString(2, 1, "Test: RIGHT-UP ");
            ServoBoard_MoveHV(800, 200, 1000);
            break;

        case 3:
            // 测试右下角
            OLED_ShowString(2, 1, "Test: RIGHT-DN ");
            ServoBoard_MoveHV(800, 800, 1000);
            break;

        case 4:
            // 测试左下角
            OLED_ShowString(2, 1, "Test: LEFT-DN  ");
            ServoBoard_MoveHV(200, 800, 1000);
            break;

        case 5:
            // 测试水平扫描
            OLED_ShowString(2, 1, "Test: H-SCAN   ");
            ServoBoard_MoveHV(100 + (g_servo_test_count % 800), 500, 200);
            break;

        case 6:
            // 测试垂直扫描
            OLED_ShowString(2, 1, "Test: V-SCAN   ");
            ServoBoard_MoveHV(500, 100 + (g_servo_test_count % 800), 200);
            break;

        default:
            // 回到中心，重新开始
            OLED_ShowString(2, 1, "Test: RESTART  ");
            ServoBoard_MoveHV(500, 500, 1000);
            g_servo_test_step = 0;
            return;
    }

    // 每10次循环切换到下一个测试步骤
    if (g_servo_test_count % 10 == 0) {
        g_servo_test_step++;
        if (g_servo_test_step > 6) {
            g_servo_test_step = 0;
        }
    }

    // LED闪烁指示活动
    LED_SetState(1);
}

#endif

#if CURRENT_MODE == MODE_CONTROL_TEST

/* 控制测试相关变量 */
static uint32_t g_control_test_step = 0;

/**
 * @brief 控制方向测试初始化
 */
static void ControlTest_Init(void)
{
    // OLED显示测试模式信息
    OLED_Clear();
    OLED_ShowString(1, 1, "CONTROL TEST");
    OLED_ShowString(2, 1, "Testing direction");
    OLED_ShowString(3, 1, "Step: 0");
    OLED_ShowString(4, 1, "Watch laser move");

    // 初始化激光追踪系统
    LaserTracker_Init();

    // 舵机回到中心位置
    ServoBoard_ReturnToCenter();
    Delay_ms(2000);

    g_control_test_step = 0;

    // LED指示初始化完成
    LED_SetState(1);
    Delay_ms(200);
    LED_SetState(0);
}

/**
 * @brief 控制方向测试处理函数
 * 模拟不同的目标和激光位置，观察舵机移动方向是否正确
 */
static void ControlTest_Process(void)
{
    // 更新OLED显示
    OLED_ShowString(3, 1, "Step:");
    OLED_ShowNum(3, 6, g_control_test_step, 2);

    switch (g_control_test_step) {
        case 0:
            // 测试1：激光在左，目标在右，舵机应该向右移动
            OLED_ShowString(2, 1, "Test: L->R     ");
            LaserTracker_UpdateLaserPosition(200, 240);   // 激光在左边
            LaserTracker_UpdateTargetPosition(400, 240);  // 目标在右边
            break;

        case 1:
            // 测试2：激光在右，目标在左，舵机应该向左移动
            OLED_ShowString(2, 1, "Test: R->L     ");
            LaserTracker_UpdateLaserPosition(400, 240);   // 激光在右边
            LaserTracker_UpdateTargetPosition(200, 240);  // 目标在左边
            break;

        case 2:
            // 测试3：激光在上，目标在下，舵机应该向下移动
            OLED_ShowString(2, 1, "Test: U->D     ");
            LaserTracker_UpdateLaserPosition(320, 150);   // 激光在上边
            LaserTracker_UpdateTargetPosition(320, 350);  // 目标在下边
            break;

        case 3:
            // 测试4：激光在下，目标在上，舵机应该向上移动
            OLED_ShowString(2, 1, "Test: D->U     ");
            LaserTracker_UpdateLaserPosition(320, 350);   // 激光在下边
            LaserTracker_UpdateTargetPosition(320, 150);  // 目标在上边
            break;

        case 4:
            // 测试5：回到中心
            OLED_ShowString(2, 1, "Test: CENTER   ");
            LaserTracker_UpdateLaserPosition(320, 240);   // 激光在中心
            LaserTracker_UpdateTargetPosition(320, 240);  // 目标在中心
            break;

        default:
            // 重新开始
            g_control_test_step = 0;
            return;
    }

    // 激活追踪
    LaserTracker_SetActive(true);

    // 执行追踪处理
    LaserTracker_Process();

    // 下一步
    g_control_test_step++;
    if (g_control_test_step > 4) {
        g_control_test_step = 0;
    }

    // LED闪烁指示活动
    LED_SetState(1);
    Delay_ms(100);
    LED_SetState(0);
    Delay_ms(50);
    LED_SetState(0);
}

#endif








