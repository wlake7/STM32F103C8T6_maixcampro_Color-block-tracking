/**
 * @file PIDController.c
 * @brief PID控制器模块实现
 * @version 1.0
 * @date 2025-07-09
 */

#include "PIDController.h"
#include "Delay.h"
#include <string.h>
#include <math.h>

/* 全局变量定义 */
PIDSystem_t g_pid_system;

/**
 * @brief 初始化PID控制器系统
 */
bool PIDController_Init(void)
{
    // 清零系统状态
    memset(&g_pid_system, 0, sizeof(PIDSystem_t));

    // 初始化水平轴PID控制器
    PIDController_SetParams(PID_TYPE_HORIZONTAL, PID_DEFAULT_KP_H, PID_DEFAULT_KI_H, PID_DEFAULT_KD_H);
    PIDController_SetSampleTime(PID_TYPE_HORIZONTAL, PID_DEFAULT_SAMPLE_TIME);
    PIDController_SetEnabled(PID_TYPE_HORIZONTAL, true);

    // 初始化垂直轴PID控制器
    PIDController_SetParams(PID_TYPE_VERTICAL, PID_DEFAULT_KP_V, PID_DEFAULT_KI_V, PID_DEFAULT_KD_V);
    PIDController_SetSampleTime(PID_TYPE_VERTICAL, PID_DEFAULT_SAMPLE_TIME);
    PIDController_SetEnabled(PID_TYPE_VERTICAL, true);

    // 设置系统状态
    g_pid_system.initialized = true;

    PID_DEBUG("PID Controller system initialized");
    return true;
}

/**
 * @brief 反初始化PID控制器系统
 */
void PIDController_DeInit(void)
{
    g_pid_system.initialized = false;
    PID_DEBUG("PID Controller system deinitialized");
}

/**
 * @brief 设置PID参数
 */
bool PIDController_SetParams(PIDType_t type, float kp, float ki, float kd)
{
    if (type >= PID_TYPE_COUNT) {
        return false;
    }

    PIDController_t* controller = &g_pid_system.controllers[type];
    
    controller->params.kp = kp;
    controller->params.ki = ki;
    controller->params.kd = kd;

    PID_DEBUG("PID[%d] params set: Kp=%.3f, Ki=%.3f, Kd=%.3f", type, kp, ki, kd);
    return true;
}

/**
 * @brief 获取PID参数
 */
bool PIDController_GetParams(PIDType_t type, PIDParams_t* params)
{
    if (type >= PID_TYPE_COUNT || !params) {
        return false;
    }

    memcpy(params, &g_pid_system.controllers[type].params, sizeof(PIDParams_t));
    return true;
}

/**
 * @brief 限制输出值范围
 */
float PIDController_Constrain(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/**
 * @brief 应用死区
 */
float PIDController_ApplyDeadzone(float error, float deadzone)
{
    if (fabs(error) < deadzone) {
        return 0.0f;
    }
    return error;
}

/**
 * @brief PID计算
 */
float PIDController_Compute(PIDType_t type, float error)
{
    if (type >= PID_TYPE_COUNT) {
        return 0.0f;
    }

    PIDController_t* controller = &g_pid_system.controllers[type];
    
    if (!controller->enabled) {
        return 0.0f;
    }

    uint32_t current_time = System_GetTick();
    
    // 计算实际采样时间
    if (controller->last_update_time > 0) {
        float actual_dt = (current_time - controller->last_update_time) / 1000.0f;
        controller->params.dt = actual_dt;
    }
    controller->last_update_time = current_time;

    // 应用死区
    error = PIDController_ApplyDeadzone(error, PID_DEADZONE);
    
    // 保存当前误差
    controller->error = error;

    // 计算积分项
    controller->integral += error * controller->params.dt;
    
    // 限制积分项范围，防止积分饱和
    controller->integral = PIDController_Constrain(controller->integral, 
                                                  PID_INTEGRAL_MIN, PID_INTEGRAL_MAX);

    // 计算微分项
    controller->derivative = (error - controller->last_error) / controller->params.dt;

    // 计算PID输出
    controller->output = controller->params.kp * error +
                        controller->params.ki * controller->integral +
                        controller->params.kd * controller->derivative;

    // 限制输出范围
    controller->output = PIDController_Constrain(controller->output, 
                                                PID_OUTPUT_MIN, PID_OUTPUT_MAX);

    // 保存当前误差为下次计算的上次误差
    controller->last_error = error;

    PID_DEBUG("PID[%d]: error=%.2f, integral=%.2f, derivative=%.2f, output=%.2f", 
              type, error, controller->integral, controller->derivative, controller->output);

    return controller->output;
}

/**
 * @brief 更新目标和激光位置，计算PID输出
 */
bool PIDController_Update(float target_x, float target_y, 
                         float laser_x, float laser_y,
                         float* output_h, float* output_v)
{
    if (!output_h || !output_v || !g_pid_system.initialized) {
        return false;
    }

    // 更新系统状态
    g_pid_system.target_x = target_x;
    g_pid_system.target_y = target_y;
    g_pid_system.laser_x = laser_x;
    g_pid_system.laser_y = laser_y;

    // 计算位置误差
    g_pid_system.error_x = target_x - laser_x;
    g_pid_system.error_y = target_y - laser_y;

    // 计算水平轴PID输出
    *output_h = PIDController_Compute(PID_TYPE_HORIZONTAL, g_pid_system.error_x);

    // 计算垂直轴PID输出
    *output_v = PIDController_Compute(PID_TYPE_VERTICAL, g_pid_system.error_y);

    // 更新计数器
    g_pid_system.update_count++;

    PID_DEBUG("PID Update: target(%.1f,%.1f) laser(%.1f,%.1f) error(%.1f,%.1f) output(%.1f,%.1f)",
              target_x, target_y, laser_x, laser_y, 
              g_pid_system.error_x, g_pid_system.error_y, *output_h, *output_v);

    return true;
}

/**
 * @brief 重置PID控制器
 */
void PIDController_Reset(PIDType_t type)
{
    if (type >= PID_TYPE_COUNT) {
        return;
    }

    PIDController_t* controller = &g_pid_system.controllers[type];
    
    controller->error = 0.0f;
    controller->last_error = 0.0f;
    controller->integral = 0.0f;
    controller->derivative = 0.0f;
    controller->output = 0.0f;
    controller->last_update_time = 0;

    PID_DEBUG("PID[%d] reset", type);
}

/**
 * @brief 重置所有PID控制器
 */
void PIDController_ResetAll(void)
{
    for (int i = 0; i < PID_TYPE_COUNT; i++) {
        PIDController_Reset((PIDType_t)i);
    }
    
    g_pid_system.update_count = 0;
    g_pid_system.target_x = 0.0f;
    g_pid_system.target_y = 0.0f;
    g_pid_system.laser_x = 0.0f;
    g_pid_system.laser_y = 0.0f;
    g_pid_system.error_x = 0.0f;
    g_pid_system.error_y = 0.0f;

    PID_DEBUG("All PID controllers reset");
}

/**
 * @brief 使能/禁用PID控制器
 */
void PIDController_SetEnabled(PIDType_t type, bool enabled)
{
    if (type >= PID_TYPE_COUNT) {
        return;
    }

    g_pid_system.controllers[type].enabled = enabled;
    
    if (!enabled) {
        // 禁用时重置控制器状态
        PIDController_Reset(type);
    }

    PID_DEBUG("PID[%d] %s", type, enabled ? "enabled" : "disabled");
}

/**
 * @brief 检查PID控制器是否使能
 */
bool PIDController_IsEnabled(PIDType_t type)
{
    if (type >= PID_TYPE_COUNT) {
        return false;
    }

    return g_pid_system.controllers[type].enabled;
}

/**
 * @brief 设置采样时间
 */
void PIDController_SetSampleTime(PIDType_t type, float dt)
{
    if (type >= PID_TYPE_COUNT || dt <= 0.0f) {
        return;
    }

    g_pid_system.controllers[type].params.dt = dt;
    PID_DEBUG("PID[%d] sample time set to %.3fs", type, dt);
}

/**
 * @brief 获取PID控制器状态
 */
PIDController_t* PIDController_GetController(PIDType_t type)
{
    if (type >= PID_TYPE_COUNT) {
        return NULL;
    }

    return &g_pid_system.controllers[type];
}

/**
 * @brief 获取PID系统状态
 */
PIDSystem_t* PIDController_GetSystem(void)
{
    return &g_pid_system;
}
