/**
 * @file test_control_board.c
 * @brief 控制板通信模块测试程序
 * @version 1.0
 * @date 2024-01-01
 * 
 * 测试控制板通信功能，验证舵机控制和位置读取
 */

#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "ControlBoard.h"
#include <stdio.h>

/* 测试配置 */
#define TEST_SERVO_ID_H     1   // 水平舵机ID
#define TEST_SERVO_ID_V     2   // 垂直舵机ID
#define TEST_POSITION_MIN   0   // 最小位置
#define TEST_POSITION_MAX   1000 // 最大位置
#define TEST_POSITION_CENTER 500 // 中心位置

/* 测试状态 */
typedef enum {
    TEST_STATE_INIT = 0,
    TEST_STATE_BASIC_MOVE,
    TEST_STATE_POSITION_READ,
    TEST_STATE_MULTI_SERVO,
    TEST_STATE_BATTERY_TEST,
    TEST_STATE_COMPLETE,
    TEST_STATE_ERROR
} TestState_t;

/* 全局变量 */
static TestState_t g_test_state = TEST_STATE_INIT;
static uint32_t g_test_start_time = 0;
static uint32_t g_test_step_time = 0;
static uint8_t g_test_step = 0;

/* 函数声明 */
static void Test_Init(void);
static void Test_BasicMove(void);
static void Test_PositionRead(void);
static void Test_MultiServo(void);
static void Test_BatteryTest(void);
static void Test_DisplayResults(void);
static void Test_UpdateDisplay(void);

/**
 * @brief 控制板测试主函数
 */
int main(void)
{
    // 系统初始化
    Test_Init();
    
    // 测试主循环
    while (1) {
        uint32_t current_time = System_GetTick();
        
        switch (g_test_state) {
            case TEST_STATE_INIT:
                OLED_ShowString(1, 1, "CtrlBoard Test");
                OLED_ShowString(2, 1, "Initializing...");
                System_Delay(2000);
                g_test_state = TEST_STATE_BASIC_MOVE;
                g_test_start_time = current_time;
                break;
                
            case TEST_STATE_BASIC_MOVE:
                Test_BasicMove();
                break;
                
            case TEST_STATE_POSITION_READ:
                Test_PositionRead();
                break;
                
            case TEST_STATE_MULTI_SERVO:
                Test_MultiServo();
                break;
                
            case TEST_STATE_BATTERY_TEST:
                Test_BatteryTest();
                break;
                
            case TEST_STATE_COMPLETE:
                Test_DisplayResults();
                break;
                
            case TEST_STATE_ERROR:
                OLED_ShowString(3, 1, "Test Failed!");
                LED1_On();
                System_Delay(1000);
                LED1_Off();
                System_Delay(1000);
                break;
                
            default:
                g_test_state = TEST_STATE_ERROR;
                break;
        }
        
        // 处理控制板通信
        ControlBoard_Process();
        
        // 更新显示
        Test_UpdateDisplay();
        
        System_Delay(50);
    }
}

/**
 * @brief 测试初始化
 */
static void Test_Init(void)
{
    // 基础模块初始化
    OLED_Init();
    LED_Init();
    
    // 显示启动信息
    OLED_Clear();
    OLED_ShowString(1, 1, "Control Board");
    OLED_ShowString(2, 1, "Test Program");
    System_Delay(1000);
    
    // 控制板初始化
    if (!ControlBoard_Init()) {
        OLED_ShowString(3, 1, "Init Failed!");
        g_test_state = TEST_STATE_ERROR;
        return;
    }
    
    OLED_ShowString(3, 1, "Init OK");
    System_Delay(1000);
}

/**
 * @brief 基础舵机移动测试
 */
static void Test_BasicMove(void)
{
    static uint8_t step = 0;
    uint32_t current_time = System_GetTick();
    
    if (current_time - g_test_step_time < 2000) {
        return; // 等待2秒
    }
    
    switch (step) {
        case 0:
            OLED_ShowString(2, 1, "Basic Move Test");
            ControlBoard_MoveServo(TEST_SERVO_ID_H, TEST_POSITION_CENTER, 1000);
            step++;
            break;
            
        case 1:
            ControlBoard_MoveServo(TEST_SERVO_ID_V, TEST_POSITION_CENTER, 1000);
            step++;
            break;
            
        case 2:
            ControlBoard_MoveServo(TEST_SERVO_ID_H, TEST_POSITION_MIN, 1000);
            step++;
            break;
            
        case 3:
            ControlBoard_MoveServo(TEST_SERVO_ID_H, TEST_POSITION_MAX, 1000);
            step++;
            break;
            
        case 4:
            ControlBoard_MoveServo(TEST_SERVO_ID_H, TEST_POSITION_CENTER, 1000);
            step = 0;
            g_test_state = TEST_STATE_POSITION_READ;
            break;
    }
    
    g_test_step_time = current_time;
}

/**
 * @brief 位置读取测试
 */
static void Test_PositionRead(void)
{
    static uint8_t step = 0;
    uint32_t current_time = System_GetTick();
    
    if (current_time - g_test_step_time < 1000) {
        return; // 等待1秒
    }
    
    switch (step) {
        case 0:
            OLED_ShowString(2, 1, "Position Test");
            // 读取多个舵机位置
            uint8_t servo_ids[] = {TEST_SERVO_ID_H, TEST_SERVO_ID_V};
            ControlBoard_ReadMultiServoPositions(servo_ids, 2);
            step++;
            break;
            
        case 1:
            // 检查是否收到位置数据
            if (ControlBoard_IsCommOK()) {
                step = 0;
                g_test_state = TEST_STATE_MULTI_SERVO;
            } else {
                // 重试
                step = 0;
            }
            break;
    }
    
    g_test_step_time = current_time;
}

/**
 * @brief 多舵机控制测试
 */
static void Test_MultiServo(void)
{
    static uint8_t step = 0;
    uint32_t current_time = System_GetTick();
    
    if (current_time - g_test_step_time < 2000) {
        return; // 等待2秒
    }
    
    switch (step) {
        case 0:
            OLED_ShowString(2, 1, "Multi Servo Test");
            // 多舵机同时控制
            ServoMoveParam_t servos[2];
            servos[0].id = TEST_SERVO_ID_H;
            servos[0].position = TEST_POSITION_MIN;
            servos[1].id = TEST_SERVO_ID_V;
            servos[1].position = TEST_POSITION_MAX;
            ControlBoard_MoveMultiServos(servos, 2, 1500);
            step++;
            break;
            
        case 1:
            // 反向移动
            ServoMoveParam_t servos2[2];
            servos2[0].id = TEST_SERVO_ID_H;
            servos2[0].position = TEST_POSITION_MAX;
            servos2[1].id = TEST_SERVO_ID_V;
            servos2[1].position = TEST_POSITION_MIN;
            ControlBoard_MoveMultiServos(servos2, 2, 1500);
            step++;
            break;
            
        case 2:
            // 回到中心
            ServoMoveParam_t servos3[2];
            servos3[0].id = TEST_SERVO_ID_H;
            servos3[0].position = TEST_POSITION_CENTER;
            servos3[1].id = TEST_SERVO_ID_V;
            servos3[1].position = TEST_POSITION_CENTER;
            ControlBoard_MoveMultiServos(servos3, 2, 1000);
            step = 0;
            g_test_state = TEST_STATE_BATTERY_TEST;
            break;
    }
    
    g_test_step_time = current_time;
}

/**
 * @brief 电池电压测试
 */
static void Test_BatteryTest(void)
{
    static uint8_t step = 0;
    uint32_t current_time = System_GetTick();
    
    if (current_time - g_test_step_time < 1000) {
        return; // 等待1秒
    }
    
    switch (step) {
        case 0:
            OLED_ShowString(2, 1, "Battery Test");
            ControlBoard_GetBatteryVoltage();
            step++;
            break;
            
        case 1:
            // 检查是否收到电压数据
            ControlBoardStats_t* stats = ControlBoard_GetStats();
            if (stats->last_battery_voltage > 0) {
                char voltage_str[16];
                sprintf(voltage_str, "V:%dmV", stats->last_battery_voltage);
                OLED_ShowString(3, 1, voltage_str);
                step = 0;
                g_test_state = TEST_STATE_COMPLETE;
            } else {
                // 重试
                step = 0;
            }
            break;
    }
    
    g_test_step_time = current_time;
}

/**
 * @brief 显示测试结果
 */
static void Test_DisplayResults(void)
{
    OLED_Clear();
    OLED_ShowString(1, 1, "Test Complete!");
    
    ControlBoardStats_t* stats = ControlBoard_GetStats();
    char stats_str[16];
    
    sprintf(stats_str, "Sent:%d", stats->packets_sent);
    OLED_ShowString(2, 1, stats_str);
    
    sprintf(stats_str, "Recv:%d", stats->packets_received);
    OLED_ShowString(3, 1, stats_str);
    
    sprintf(stats_str, "Err:%d", stats->packets_error);
    OLED_ShowString(4, 1, stats_str);
    
    // 闪烁LED表示测试完成
    LED1_Turn();
    System_Delay(500);
}

/**
 * @brief 更新显示
 */
static void Test_UpdateDisplay(void)
{
    static uint32_t last_update = 0;
    uint32_t current_time = System_GetTick();
    
    if (current_time - last_update < 500) {
        return; // 500ms更新一次
    }
    
    // 显示通信状态
    if (ControlBoard_IsCommOK()) {
        OLED_ShowString(4, 1, "Comm: OK");
    } else {
        OLED_ShowString(4, 1, "Comm: ERR");
    }
    
    last_update = current_time;
}
