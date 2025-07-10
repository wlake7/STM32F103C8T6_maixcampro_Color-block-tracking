#include "LaserTracker.h"
#include "ServoControl.h"
#include "Timer.h"
#include "Delay.h"
#include <string.h>

/**
 * @file LaserTracker.c
 * @brief 激光追踪控制模块实现
 * @version 1.0
 * @date 2025-07-09
 */

/* 全局激光追踪系统状态 */
static LaserTracker_t g_laser_tracker;



/* 内部函数声明 */
static void PID_Init(PID_Controller_t* pid, float kp, float ki, float kd, float max_output);
static float PID_Calculate(PID_Controller_t* pid, float setpoint, float measured);
static uint16_t Position_ToServoPos(int16_t image_pos, uint8_t is_horizontal);

/**
 * @brief 初始化激光追踪系统
 */
bool LaserTracker_Init(void)
{
    // 清零追踪系统状态
    memset(&g_laser_tracker, 0, sizeof(LaserTracker_t));

    // 初始化PID控制器
    // 水平PID参数 (根据实际调试调整)
    PID_Init(&g_laser_tracker.pid_h, 8.0f, 0.1f, 0.5f, 200.0f);
    
    // 垂直PID参数 (根据实际调试调整)
    PID_Init(&g_laser_tracker.pid_v, 8.0f, 0.1f, 0.5f, 200.0f);

    // 设置舵机初始位置为中心
    g_laser_tracker.servo_h_pos = SERVO_POS_CENTER;
    g_laser_tracker.servo_v_pos = SERVO_POS_CENTER;

    // 等待系统稳定
    Delay_ms(1000);

    // 舵机回到中心位置
    ServoBoard_MoveHV(SERVO_POS_CENTER, SERVO_POS_CENTER, 1000);
    Delay_ms(1500);

    // 激活追踪
    g_laser_tracker.tracking_active = 1;
    g_laser_tracker.last_update_time = Timer_GetSystemTick();

    return true;
}

/**
 * @brief 反初始化激光追踪系统
 */
void LaserTracker_DeInit(void)
{
    g_laser_tracker.tracking_active = 0;
    
    // 舵机回到中心位置
    ServoBoard_MoveHV(SERVO_POS_CENTER, SERVO_POS_CENTER, 1000);
    Delay_ms(1000);
}

/**
 * @brief 激光追踪主处理函数
 */
void LaserTracker_Process(void)
{
    uint32_t current_time = Timer_GetSystemTick();
    
    if (!g_laser_tracker.tracking_active) {
        return;
    }
    
    // 检查是否有新的位置数据
    if (g_laser_tracker.target_pos.valid && g_laser_tracker.laser_pos.valid) {
        // 计算水平方向PID输出
        // 目标：让激光位置接近目标位置，所以setpoint是目标位置，measured是激光位置
        float h_output = PID_Calculate(&g_laser_tracker.pid_h,
                                      (float)g_laser_tracker.target_pos.x,
                                      (float)g_laser_tracker.laser_pos.x);

        // 计算垂直方向PID输出
        float v_output = PID_Calculate(&g_laser_tracker.pid_v,
                                      (float)g_laser_tracker.target_pos.y,
                                      (float)g_laser_tracker.laser_pos.y);
        
        // 更新舵机位置
        int16_t new_h_pos = (int16_t)g_laser_tracker.servo_h_pos + (int16_t)h_output;
        int16_t new_v_pos = (int16_t)g_laser_tracker.servo_v_pos + (int16_t)v_output;

        // 位置限幅
        if (new_h_pos < SERVO_POS_MIN) new_h_pos = SERVO_POS_MIN;
        if (new_h_pos > SERVO_POS_MAX) new_h_pos = SERVO_POS_MAX;
        if (new_v_pos < SERVO_POS_MIN) new_v_pos = SERVO_POS_MIN;
        if (new_v_pos > SERVO_POS_MAX) new_v_pos = SERVO_POS_MAX;

        g_laser_tracker.servo_h_pos = (uint16_t)new_h_pos;
        g_laser_tracker.servo_v_pos = (uint16_t)new_v_pos;

        // 发送舵机控制命令
        ServoBoard_MoveHV(g_laser_tracker.servo_h_pos, g_laser_tracker.servo_v_pos, 100);

        // 调试输出（可选，用于诊断）
        // 注意：在实际使用中可能需要注释掉以避免影响性能
        static uint32_t debug_counter = 0;
        if (++debug_counter % 10 == 0) {  // 每10次输出一次，避免过多输出
            // 这里可以添加调试输出，但需要确保有输出方式（如LED指示或预留的调试接口）
        }
        
        // 清除有效标志，等待新数据
        g_laser_tracker.target_pos.valid = 0;
        g_laser_tracker.laser_pos.valid = 0;
        
        g_laser_tracker.last_update_time = current_time;
    }
    
    // 超时检测（1秒无数据则停止追踪）
    if ((current_time - g_laser_tracker.last_update_time) > 1000) {
        if (g_laser_tracker.tracking_active) {
            // 回到中心位置
            ServoBoard_MoveHV(SERVO_POS_CENTER, SERVO_POS_CENTER, 500);
            g_laser_tracker.servo_h_pos = SERVO_POS_CENTER;
            g_laser_tracker.servo_v_pos = SERVO_POS_CENTER;
        }
    }
}

/**
 * @brief 获取追踪状态
 */
bool LaserTracker_IsActive(void)
{
    return g_laser_tracker.tracking_active;
}

/**
 * @brief 设置追踪状态
 */
void LaserTracker_SetActive(bool active)
{
    g_laser_tracker.tracking_active = active ? 1 : 0;
    
    if (!active) {
        // 停止追踪时回到中心位置
        ServoBoard_MoveHV(SERVO_POS_CENTER, SERVO_POS_CENTER, 500);
        g_laser_tracker.servo_h_pos = SERVO_POS_CENTER;
        g_laser_tracker.servo_v_pos = SERVO_POS_CENTER;
    }
}

/**
 * @brief 更新目标位置
 */
void LaserTracker_UpdateTargetPosition(int16_t x, int16_t y)
{
    g_laser_tracker.target_pos.x = x;
    g_laser_tracker.target_pos.y = y;
    g_laser_tracker.target_pos.valid = 1;
}

/**
 * @brief 更新激光位置
 */
void LaserTracker_UpdateLaserPosition(int16_t x, int16_t y)
{
    g_laser_tracker.laser_pos.x = x;
    g_laser_tracker.laser_pos.y = y;
    g_laser_tracker.laser_pos.valid = 1;
}

/**
 * @brief 更新PID参数
 */
void LaserTracker_UpdatePIDParams(float kp_h, float ki_h, float kd_h, 
                                  float kp_v, float ki_v, float kd_v)
{
    g_laser_tracker.pid_h.kp = kp_h;
    g_laser_tracker.pid_h.ki = ki_h;
    g_laser_tracker.pid_h.kd = kd_h;
    g_laser_tracker.pid_v.kp = kp_v;
    g_laser_tracker.pid_v.ki = ki_v;
    g_laser_tracker.pid_v.kd = kd_v;
}

/**
 * @brief 获取舵机位置
 */
void LaserTracker_GetServoPosition(uint16_t* h_pos, uint16_t* v_pos)
{
    if (h_pos) *h_pos = g_laser_tracker.servo_h_pos;
    if (v_pos) *v_pos = g_laser_tracker.servo_v_pos;
}

/**
 * @brief PID控制器初始化
 */
static void PID_Init(PID_Controller_t* pid, float kp, float ki, float kd, float max_output)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->error = 0.0f;
    pid->last_error = 0.0f;
    pid->integral = 0.0f;
    pid->output = 0.0f;
    pid->max_output = max_output;
    pid->max_integral = max_output * 0.5f;  // 积分限幅为输出限幅的一半
}

/**
 * @brief PID控制计算
 */
static float PID_Calculate(PID_Controller_t* pid, float setpoint, float measured)
{
    // 计算误差
    pid->error = setpoint - measured;
    
    // 积分项计算（带限幅）
    pid->integral += pid->error;
    if (pid->integral > pid->max_integral) {
        pid->integral = pid->max_integral;
    } else if (pid->integral < -pid->max_integral) {
        pid->integral = -pid->max_integral;
    }
    
    // 微分项计算
    float derivative = pid->error - pid->last_error;
    
    // PID输出计算
    pid->output = pid->kp * pid->error + pid->ki * pid->integral + pid->kd * derivative;
    
    // 输出限幅
    if (pid->output > pid->max_output) {
        pid->output = pid->max_output;
    } else if (pid->output < -pid->max_output) {
        pid->output = -pid->max_output;
    }
    
    // 保存当前误差为下次的上次误差
    pid->last_error = pid->error;
    
    return pid->output;
}

/**
 * @brief 图像坐标转换为舵机位置
 */
static uint16_t Position_ToServoPos(int16_t image_pos, uint8_t is_horizontal)
{
    uint16_t servo_pos;
    
    if (is_horizontal) {
        // 水平方向：图像X坐标转换为舵机位置
        servo_pos = (uint16_t)((float)image_pos * (SERVO_POS_MAX - SERVO_POS_MIN) / IMAGE_WIDTH + SERVO_POS_MIN);
    } else {
        // 垂直方向：图像Y坐标转换为舵机位置（注意Y轴可能需要反向）
        servo_pos = (uint16_t)(SERVO_POS_MAX - (float)image_pos * (SERVO_POS_MAX - SERVO_POS_MIN) / IMAGE_HEIGHT);
    }
    
    // 限幅
    if (servo_pos < SERVO_POS_MIN) servo_pos = SERVO_POS_MIN;
    if (servo_pos > SERVO_POS_MAX) servo_pos = SERVO_POS_MAX;
    
    return servo_pos;
}
