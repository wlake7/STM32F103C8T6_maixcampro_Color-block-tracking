/**
 * @file test_servo_function.c
 * @brief 舵机测试功能验证文件
 * @author AI Assistant
 * @date 2025-07-07
 * 
 * 用于验证新添加的舵机测试功能的语法正确性
 */

#include "stm32f10x.h"
#include <stdio.h>
#include <stdbool.h>

// 模拟依赖的头文件定义
#define CONTROL_BOARD_SERVO_ID_HORIZONTAL   2
#define CONTROL_BOARD_SERVO_ID_VERTICAL     1

// 模拟函数声明
bool ControlBoard_MoveServo(uint8_t id, uint16_t position, uint16_t time);
uint8_t Key_GetNum(void);
void OLED_ShowString(uint8_t line, uint8_t column, char* string);
void LED_On(void);
void LED_Off(void);
uint32_t System_GetTick(void);

// 模拟函数实现
bool ControlBoard_MoveServo(uint8_t id, uint16_t position, uint16_t time) {
    printf("舵机%d移动到位置%d，时间%dms\n", id, position, time);
    return true;
}

uint8_t Key_GetNum(void) {
    static uint8_t key_state = 0;
    return key_state;
}

void OLED_ShowString(uint8_t line, uint8_t column, char* string) {
    printf("OLED[%d,%d]: %s\n", line, column, string);
}

void LED_On(void) {
    printf("LED开启\n");
}

void LED_Off(void) {
    printf("LED关闭\n");
}

uint32_t System_GetTick(void) {
    static uint32_t tick = 0;
    return tick += 100;  // 模拟时间递增
}

/**
 * @brief 舵机电机测试函数 (从main.c复制)
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

/**
 * @brief 测试主函数
 */
int main(void)
{
    printf("舵机测试功能验证\n");
    printf("==================\n");
    
    // 模拟测试几个周期
    for (int i = 0; i < 10; i++) {
        System_TestServoMotors();
        // 模拟延时
        for (volatile int j = 0; j < 1000000; j++);
    }
    
    printf("测试完成\n");
    return 0;
}
