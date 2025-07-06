/**
 * @file PID.c
 * @brief STM32端PID控制器模块实现
 * @author AI Assistant
 * @date 2025-07-06
 */

#include "PID.h"
#include <string.h>
#include <math.h>

/* 默认PID参数 */
#define DEFAULT_KP_HORIZONTAL       2.0f    // 水平默认Kp
#define DEFAULT_KI_HORIZONTAL       0.1f    // 水平默认Ki
#define DEFAULT_KD_HORIZONTAL       0.5f    // 水平默认Kd
#define DEFAULT_KP_VERTICAL         2.5f    // 垂直默认Kp
#define DEFAULT_KI_VERTICAL         0.15f   // 垂直默认Ki
#define DEFAULT_KD_VERTICAL         0.6f    // 垂直默认Kd
#define DEFAULT_DEADBAND            2.0f    // 默认死区
#define DEFAULT_DERIVATIVE_ALPHA    0.8f    // 默认微分滤波系数

/* 全局变量定义 */
PIDController_t g_pid_horizontal;
PIDController_t g_pid_vertical;
PIDSystemStatus_t g_pid_system = {0};

/* 私有函数声明 */
static void PID_InitDefaultParams(PIDParams_t* params, PIDType_t type);
static float PID_ComputeProportional(PIDController_t* controller);
static float PID_ComputeIntegral(PIDController_t* controller);
static float PID_ComputeDerivative(PIDController_t* controller);
static void PID_UpdateStatistics(PIDController_t* controller);

/**
 * @brief 初始化PID控制器模块
 */
bool PID_Init(void)
{
    // 初始化水平PID控制器
    if (!PID_InitController(&g_pid_horizontal, PID_TYPE_HORIZONTAL)) {
        return false;
    }
    
    // 初始化垂直PID控制器
    if (!PID_InitController(&g_pid_vertical, PID_TYPE_VERTICAL)) {
        return false;
    }
    
    // 初始化系统状态
    g_pid_system.system_enabled = true;
    g_pid_system.total_compute_count = 0;
    g_pid_system.total_saturation_count = 0;
    g_pid_system.system_frequency = 0.0f;
    g_pid_system.last_update_time = PID_GetSystemTime();
    
    return true;
}

/**
 * @brief 初始化单个PID控制器
 */
bool PID_InitController(PIDController_t* controller, PIDType_t type)
{
    if (!controller || type >= PID_TYPE_COUNT) {
        return false;
    }
    
    // 清零控制器结构
    memset(controller, 0, sizeof(PIDController_t));
    
    // 设置基本属性
    controller->type = type;
    controller->state = PID_STATE_DISABLED;
    
    // 初始化默认参数
    PID_InitDefaultParams(&controller->params, type);
    
    // 初始化控制变量
    controller->setpoint = 0.0f;
    controller->input = 0.0f;
    controller->output = 0.0f;
    controller->error = 0.0f;
    controller->last_error = 0.0f;
    controller->integral = 0.0f;
    controller->derivative = 0.0f;
    controller->last_derivative = 0.0f;
    
    // 初始化时间
    controller->last_time = PID_GetSystemTime();
    controller->dt = 0.0f;
    
    // 初始化统计信息
    controller->compute_count = 0;
    controller->saturation_count = 0;
    controller->max_error = 0.0f;
    controller->avg_error = 0.0f;
    controller->error_sum = 0.0f;
    
    return true;
}

/**
 * @brief 初始化默认PID参数
 */
static void PID_InitDefaultParams(PIDParams_t* params, PIDType_t type)
{
    if (!params) {
        return;
    }
    
    // 根据类型设置默认参数
    if (type == PID_TYPE_HORIZONTAL) {
        params->kp = DEFAULT_KP_HORIZONTAL;
        params->ki = DEFAULT_KI_HORIZONTAL;
        params->kd = DEFAULT_KD_HORIZONTAL;
    } else {
        params->kp = DEFAULT_KP_VERTICAL;
        params->ki = DEFAULT_KI_VERTICAL;
        params->kd = DEFAULT_KD_VERTICAL;
    }
    
    // 设置通用参数
    params->output_min = PID_OUTPUT_MIN;
    params->output_max = PID_OUTPUT_MAX;
    params->integral_min = PID_INTEGRAL_MIN;
    params->integral_max = PID_INTEGRAL_MAX;
    params->deadband = DEFAULT_DEADBAND;
    params->enable_integral_windup = true;
    params->enable_derivative_filter = true;
    params->derivative_filter_alpha = DEFAULT_DERIVATIVE_ALPHA;
}

/**
 * @brief 设置PID参数
 */
bool PID_SetParams(PIDType_t type, float kp, float ki, float kd)
{
    PIDController_t* controller = PID_GetController(type);
    if (!controller) {
        return false;
    }
    
    // 参数范围检查
    if (kp < PID_KP_MIN || kp > PID_KP_MAX ||
        ki < PID_KI_MIN || ki > PID_KI_MAX ||
        kd < PID_KD_MIN || kd > PID_KD_MAX) {
        return false;
    }
    
    // 设置参数
    controller->params.kp = kp;
    controller->params.ki = ki;
    controller->params.kd = kd;
    
    // 重置积分项(参数改变时)
    controller->integral = 0.0f;
    
    return true;
}

/**
 * @brief 设置PID输出限制
 */
bool PID_SetOutputLimits(PIDType_t type, float min, float max)
{
    PIDController_t* controller = PID_GetController(type);
    if (!controller || min >= max) {
        return false;
    }
    
    controller->params.output_min = min;
    controller->params.output_max = max;
    
    // 限制当前输出
    controller->output = PID_Constrain(controller->output, min, max);
    
    return true;
}

/**
 * @brief 设置PID积分限制
 */
bool PID_SetIntegralLimits(PIDType_t type, float min, float max)
{
    PIDController_t* controller = PID_GetController(type);
    if (!controller || min >= max) {
        return false;
    }
    
    controller->params.integral_min = min;
    controller->params.integral_max = max;
    
    // 限制当前积分值
    controller->integral = PID_Constrain(controller->integral, min, max);
    
    return true;
}

/**
 * @brief 设置PID死区
 */
bool PID_SetDeadband(PIDType_t type, float deadband)
{
    PIDController_t* controller = PID_GetController(type);
    if (!controller || deadband < 0.0f) {
        return false;
    }
    
    controller->params.deadband = deadband;
    return true;
}

/**
 * @brief 启用/禁用PID控制器
 */
bool PID_Enable(PIDType_t type, bool enable)
{
    PIDController_t* controller = PID_GetController(type);
    if (!controller) {
        return false;
    }
    
    if (enable) {
        controller->state = PID_STATE_ENABLED;
        // 重置时间和积分项
        controller->last_time = PID_GetSystemTime();
        controller->integral = 0.0f;
        controller->last_error = 0.0f;
    } else {
        controller->state = PID_STATE_DISABLED;
        controller->output = 0.0f;
    }
    
    return true;
}

/**
 * @brief 设置PID设定值
 */
bool PID_SetSetpoint(PIDType_t type, float setpoint)
{
    PIDController_t* controller = PID_GetController(type);
    if (!controller) {
        return false;
    }
    
    controller->setpoint = setpoint;
    return true;
}

/**
 * @brief 计算PID输出
 */
float PID_Compute(PIDType_t type, float input)
{
    PIDController_t* controller = PID_GetController(type);
    if (!controller || controller->state != PID_STATE_ENABLED) {
        return 0.0f;
    }
    
    // 更新输入和时间
    controller->input = input;
    uint32_t current_time = PID_GetSystemTime();
    controller->dt = PID_CalculateDeltaTime(current_time, controller->last_time);
    controller->last_time = current_time;
    
    // 计算误差
    controller->error = controller->setpoint - controller->input;
    
    // 应用死区
    float effective_error = PID_ApplyDeadband(controller->error, controller->params.deadband);
    
    // 如果在死区内，输出为0
    if (effective_error == 0.0f) {
        controller->output = 0.0f;
        controller->last_error = controller->error;
        return controller->output;
    }
    
    // 计算PID各项
    float proportional = PID_ComputeProportional(controller);
    float integral = PID_ComputeIntegral(controller);
    float derivative = PID_ComputeDerivative(controller);
    
    // 计算总输出
    controller->output = proportional + integral + derivative;
    
    // 输出限制
    float unconstrained_output = controller->output;
    controller->output = PID_Constrain(controller->output, 
                                     controller->params.output_min, 
                                     controller->params.output_max);
    
    // 检查饱和状态
    if (unconstrained_output != controller->output) {
        controller->state = PID_STATE_SATURATED;
        controller->saturation_count++;
        
        // 积分饱和保护
        if (controller->params.enable_integral_windup) {
            // 如果输出饱和且积分项与误差同号，则不累积积分
            if ((controller->integral > 0 && effective_error > 0) ||
                (controller->integral < 0 && effective_error < 0)) {
                controller->integral -= controller->params.ki * effective_error * controller->dt;
            }
        }
    } else {
        controller->state = PID_STATE_ENABLED;
    }
    
    // 更新统计信息
    PID_UpdateStatistics(controller);
    
    // 保存当前误差
    controller->last_error = controller->error;
    
    return controller->output;
}

/**
 * @brief 计算比例项
 */
static float PID_ComputeProportional(PIDController_t* controller)
{
    return controller->params.kp * controller->error;
}

/**
 * @brief 计算积分项
 */
static float PID_ComputeIntegral(PIDController_t* controller)
{
    if (controller->dt > 0.0f) {
        controller->integral += controller->params.ki * controller->error * controller->dt;

        // 积分限制
        controller->integral = PID_Constrain(controller->integral,
                                           controller->params.integral_min,
                                           controller->params.integral_max);
    }

    return controller->integral;
}

/**
 * @brief 计算微分项
 */
static float PID_ComputeDerivative(PIDController_t* controller)
{
    float derivative = 0.0f;

    if (controller->dt > 0.0f) {
        derivative = controller->params.kd * (controller->error - controller->last_error) / controller->dt;

        // 微分滤波
        if (controller->params.enable_derivative_filter) {
            derivative = PID_LowPassFilter(derivative, controller->last_derivative,
                                         controller->params.derivative_filter_alpha);
        }

        controller->last_derivative = derivative;
    }

    controller->derivative = derivative;
    return derivative;
}

/**
 * @brief 更新统计信息
 */
static void PID_UpdateStatistics(PIDController_t* controller)
{
    controller->compute_count++;

    // 更新最大误差
    float abs_error = fabsf(controller->error);
    if (abs_error > controller->max_error) {
        controller->max_error = abs_error;
    }

    // 更新平均误差
    controller->error_sum += abs_error;
    controller->avg_error = controller->error_sum / controller->compute_count;
}

/**
 * @brief 重置PID控制器
 */
bool PID_Reset(PIDType_t type)
{
    PIDController_t* controller = PID_GetController(type);
    if (!controller) {
        return false;
    }

    controller->error = 0.0f;
    controller->last_error = 0.0f;
    controller->integral = 0.0f;
    controller->derivative = 0.0f;
    controller->last_derivative = 0.0f;
    controller->output = 0.0f;
    controller->last_time = PID_GetSystemTime();

    // 重置统计信息
    controller->compute_count = 0;
    controller->saturation_count = 0;
    controller->max_error = 0.0f;
    controller->avg_error = 0.0f;
    controller->error_sum = 0.0f;

    return true;
}

/**
 * @brief 重置PID积分项
 */
bool PID_ResetIntegral(PIDType_t type)
{
    PIDController_t* controller = PID_GetController(type);
    if (!controller) {
        return false;
    }

    controller->integral = 0.0f;
    return true;
}

/**
 * @brief 获取PID控制器指针
 */
PIDController_t* PID_GetController(PIDType_t type)
{
    switch (type) {
        case PID_TYPE_HORIZONTAL:
            return &g_pid_horizontal;
        case PID_TYPE_VERTICAL:
            return &g_pid_vertical;
        default:
            return NULL;
    }
}

/**
 * @brief 获取PID参数
 */
PIDParams_t* PID_GetParams(PIDType_t type)
{
    PIDController_t* controller = PID_GetController(type);
    return controller ? &controller->params : NULL;
}

/**
 * @brief 获取PID系统状态
 */
PIDSystemStatus_t* PID_GetSystemStatus(void)
{
    return &g_pid_system;
}

/**
 * @brief 更新PID系统状态
 */
void PID_UpdateSystemStatus(void)
{
    uint32_t current_time = PID_GetSystemTime();
    float dt = PID_CalculateDeltaTime(current_time, g_pid_system.last_update_time);

    if (dt > 0.0f) {
        g_pid_system.system_frequency = 1000.0f / dt; // Hz
    }

    g_pid_system.total_compute_count = g_pid_horizontal.compute_count + g_pid_vertical.compute_count;
    g_pid_system.total_saturation_count = g_pid_horizontal.saturation_count + g_pid_vertical.saturation_count;
    g_pid_system.last_update_time = current_time;
}

/**
 * @brief 限制数值范围
 */
float PID_Constrain(float value, float min, float max)
{
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    }
    return value;
}

/**
 * @brief 应用死区处理
 */
float PID_ApplyDeadband(float value, float deadband)
{
    if (fabsf(value) <= deadband) {
        return 0.0f;
    }
    return value;
}

/**
 * @brief 低通滤波器
 */
float PID_LowPassFilter(float current, float previous, float alpha)
{
    return alpha * previous + (1.0f - alpha) * current;
}

/**
 * @brief 获取系统时间(毫秒)
 */
uint32_t PID_GetSystemTime(void)
{
    // 这里应该返回系统时钟，暂时返回0
    // 在实际应用中需要实现系统时钟获取
    static uint32_t fake_time = 0;
    return fake_time++;
}

/**
 * @brief 计算时间差(毫秒)
 */
float PID_CalculateDeltaTime(uint32_t current_time, uint32_t last_time)
{
    if (current_time >= last_time) {
        return (float)(current_time - last_time);
    } else {
        // 处理时钟溢出
        return (float)(0xFFFFFFFF - last_time + current_time + 1);
    }
}

/**
 * @brief PID模块主循环处理
 */
void PID_Process(void)
{
    // 更新系统状态
    PID_UpdateSystemStatus();

    // 这里可以添加其他周期性处理
}

/**
 * @brief 打印PID调试信息
 */
void PID_PrintDebugInfo(PIDType_t type)
{
    PIDController_t* controller = PID_GetController(type);
    if (!controller) {
        return;
    }

    // 这里可以实现调试信息输出
    // 在实际应用中可以通过串口或其他方式输出
}
