/**
 * @file PID.h
 * @brief STM32端PID控制器模块头文件
 * @author AI Assistant
 * @date 2025-07-06
 * 
 * 实现可配置的PID控制器，支持水平和垂直两个独立的PID实例，参数可调
 */

#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"
#include <stdint.h>
#include <stdbool.h>

/* PID参数范围定义 */
#define PID_KP_MIN              0.0f        // Kp最小值
#define PID_KP_MAX              100.0f      // Kp最大值
#define PID_KI_MIN              0.0f        // Ki最小值
#define PID_KI_MAX              50.0f       // Ki最大值
#define PID_KD_MIN              0.0f        // Kd最小值
#define PID_KD_MAX              10.0f       // Kd最大值

/* PID输出限制 */
#define PID_OUTPUT_MIN          -1000.0f    // 输出最小值
#define PID_OUTPUT_MAX          1000.0f     // 输出最大值
#define PID_INTEGRAL_MIN        -500.0f     // 积分项最小值
#define PID_INTEGRAL_MAX        500.0f      // 积分项最大值

/* PID控制器类型 */
typedef enum {
    PID_TYPE_HORIZONTAL = 0,                // 水平PID控制器
    PID_TYPE_VERTICAL = 1,                  // 垂直PID控制器
    PID_TYPE_COUNT                          // PID控制器数量
} PIDType_t;

/* PID控制器状态 */
typedef enum {
    PID_STATE_DISABLED = 0,                 // 禁用状态
    PID_STATE_ENABLED,                      // 启用状态
    PID_STATE_SATURATED,                    // 饱和状态
    PID_STATE_ERROR                         // 错误状态
} PIDState_t;

/* PID参数结构 */
typedef struct {
    float kp;                               // 比例系数
    float ki;                               // 积分系数
    float kd;                               // 微分系数
    float output_min;                       // 输出最小值
    float output_max;                       // 输出最大值
    float integral_min;                     // 积分限制最小值
    float integral_max;                     // 积分限制最大值
    float deadband;                         // 死区范围
    bool enable_integral_windup;            // 是否启用积分饱和保护
    bool enable_derivative_filter;          // 是否启用微分滤波
    float derivative_filter_alpha;          // 微分滤波系数 (0-1)
} PIDControlParams_t;

/* PID控制器结构 */
typedef struct {
    PIDType_t type;                         // 控制器类型
    PIDState_t state;                       // 控制器状态
    PIDControlParams_t params;              // PID参数
    
    // 控制变量
    float setpoint;                         // 设定值
    float input;                            // 输入值
    float output;                           // 输出值
    float error;                            // 当前误差
    float last_error;                       // 上次误差
    float integral;                         // 积分项
    float derivative;                       // 微分项
    float last_derivative;                  // 上次微分项(用于滤波)
    
    // 时间相关
    uint32_t last_time;                     // 上次计算时间
    float dt;                               // 时间间隔
    
    // 统计信息
    uint32_t compute_count;                 // 计算次数
    uint32_t saturation_count;              // 饱和次数
    float max_error;                        // 最大误差
    float avg_error;                        // 平均误差
    float error_sum;                        // 误差累计(用于计算平均值)
} PIDController_t;

/* PID系统状态 */
typedef struct {
    bool system_enabled;                    // 系统启用状态
    uint32_t total_compute_count;           // 总计算次数
    uint32_t total_saturation_count;        // 总饱和次数
    float system_frequency;                 // 系统频率
    uint32_t last_update_time;              // 最后更新时间
} PIDSystemStatus_t;

/* 全局变量声明 */
extern PIDController_t g_pid_horizontal;   // 水平PID控制器
extern PIDController_t g_pid_vertical;     // 垂直PID控制器
extern PIDSystemStatus_t g_pid_system;     // PID系统状态

/* 函数声明 */

/**
 * @brief 初始化PID控制器模块
 * @return 初始化结果
 */
bool PID_Init(void);

/**
 * @brief 初始化单个PID控制器
 * @param controller PID控制器指针
 * @param type 控制器类型
 * @return 初始化结果
 */
bool PID_InitController(PIDController_t* controller, PIDType_t type);

/**
 * @brief 设置PID参数
 * @param type 控制器类型
 * @param kp 比例系数
 * @param ki 积分系数
 * @param kd 微分系数
 * @return 设置结果
 */
bool PID_SetParams(PIDType_t type, float kp, float ki, float kd);

/**
 * @brief 设置PID输出限制
 * @param type 控制器类型
 * @param min 最小输出
 * @param max 最大输出
 * @return 设置结果
 */
bool PID_SetOutputLimits(PIDType_t type, float min, float max);

/**
 * @brief 设置PID积分限制
 * @param type 控制器类型
 * @param min 最小积分值
 * @param max 最大积分值
 * @return 设置结果
 */
bool PID_SetIntegralLimits(PIDType_t type, float min, float max);

/**
 * @brief 设置PID死区
 * @param type 控制器类型
 * @param deadband 死区范围
 * @return 设置结果
 */
bool PID_SetDeadband(PIDType_t type, float deadband);

/**
 * @brief 启用/禁用PID控制器
 * @param type 控制器类型
 * @param enable 启用标志
 * @return 设置结果
 */
bool PID_Enable(PIDType_t type, bool enable);

/**
 * @brief 设置PID设定值
 * @param type 控制器类型
 * @param setpoint 设定值
 * @return 设置结果
 */
bool PID_SetSetpoint(PIDType_t type, float setpoint);

/**
 * @brief 计算PID输出
 * @param type 控制器类型
 * @param input 输入值
 * @return PID输出值
 */
float PID_Compute(PIDType_t type, float input);

/**
 * @brief 重置PID控制器
 * @param type 控制器类型
 * @return 重置结果
 */
bool PID_Reset(PIDType_t type);

/**
 * @brief 重置PID积分项
 * @param type 控制器类型
 * @return 重置结果
 */
bool PID_ResetIntegral(PIDType_t type);

/**
 * @brief 获取PID控制器指针
 * @param type 控制器类型
 * @return 控制器指针
 */
PIDController_t* PID_GetController(PIDType_t type);

/**
 * @brief 获取PID参数
 * @param type 控制器类型
 * @return 参数指针
 */
PIDControlParams_t* PID_GetParams(PIDType_t type);

/**
 * @brief 获取PID系统状态
 * @return 系统状态指针
 */
PIDSystemStatus_t* PID_GetSystemStatus(void);

/**
 * @brief 更新PID系统状态
 */
void PID_UpdateSystemStatus(void);

/**
 * @brief 限制数值范围
 * @param value 输入值
 * @param min 最小值
 * @param max 最大值
 * @return 限制后的值
 */
float PID_Constrain(float value, float min, float max);

/**
 * @brief 应用死区处理
 * @param value 输入值
 * @param deadband 死区范围
 * @return 处理后的值
 */
float PID_ApplyDeadband(float value, float deadband);

/**
 * @brief 低通滤波器
 * @param current 当前值
 * @param previous 前一个值
 * @param alpha 滤波系数 (0-1)
 * @return 滤波后的值
 */
float PID_LowPassFilter(float current, float previous, float alpha);

/**
 * @brief 获取系统时间(毫秒)
 * @return 系统时间
 */
uint32_t PID_GetSystemTime(void);

/**
 * @brief 计算时间差(毫秒)
 * @param current_time 当前时间
 * @param last_time 上次时间
 * @return 时间差
 */
float PID_CalculateDeltaTime(uint32_t current_time, uint32_t last_time);

/**
 * @brief PID模块主循环处理
 * 需要在主循环中定期调用
 */
void PID_Process(void);

/**
 * @brief 打印PID调试信息
 * @param type 控制器类型
 */
void PID_PrintDebugInfo(PIDType_t type);

#endif /* __PID_H */
