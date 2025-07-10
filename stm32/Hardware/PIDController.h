/**
 * @file PIDController.h
 * @brief PID控制器模块头文件
 * @version 1.0
 * @date 2025-07-09
 * 
 * 实现双轴PID控制器，用于激光追踪系统的舵机控制
 */

#ifndef __PID_CONTROLLER_H
#define __PID_CONTROLLER_H

#include "stm32f10x.h"
#include <stdbool.h>
#include <stdint.h>

/* PID控制器配置 */
#define PID_OUTPUT_MIN          -1000       // PID输出最小值
#define PID_OUTPUT_MAX          1000        // PID输出最大值
#define PID_INTEGRAL_MAX        10000       // 积分项最大值
#define PID_INTEGRAL_MIN        -10000      // 积分项最小值
#define PID_DEADZONE            5           // 死区范围

/* PID控制器类型 */
typedef enum {
    PID_TYPE_HORIZONTAL = 0,    // 水平轴PID
    PID_TYPE_VERTICAL,          // 垂直轴PID
    PID_TYPE_COUNT              // PID控制器数量
} PIDType_t;

/* PID参数结构 */
typedef struct {
    float kp;                   // 比例系数
    float ki;                   // 积分系数
    float kd;                   // 微分系数
    float dt;                   // 采样时间 (秒)
} PIDParams_t;

/* PID控制器状态 */
typedef struct {
    PIDParams_t params;         // PID参数
    float error;                // 当前误差
    float last_error;           // 上次误差
    float integral;             // 积分累积
    float derivative;           // 微分项
    float output;               // 输出值
    bool enabled;               // 使能状态
    uint32_t last_update_time;  // 最后更新时间
} PIDController_t;

/* PID系统状态 */
typedef struct {
    PIDController_t controllers[PID_TYPE_COUNT];    // PID控制器数组
    bool initialized;                               // 初始化状态
    uint32_t update_count;                          // 更新次数
    float target_x, target_y;                       // 目标位置
    float laser_x, laser_y;                         // 激光位置
    float error_x, error_y;                         // 位置误差
} PIDSystem_t;

/* 全局变量声明 */
extern PIDSystem_t g_pid_system;

/* 函数声明 */

/**
 * @brief 初始化PID控制器系统
 * @return true: 成功, false: 失败
 */
bool PIDController_Init(void);

/**
 * @brief 反初始化PID控制器系统
 */
void PIDController_DeInit(void);

/**
 * @brief 设置PID参数
 * @param type PID控制器类型
 * @param kp 比例系数
 * @param ki 积分系数
 * @param kd 微分系数
 * @return true: 成功, false: 失败
 */
bool PIDController_SetParams(PIDType_t type, float kp, float ki, float kd);

/**
 * @brief 获取PID参数
 * @param type PID控制器类型
 * @param params 输出的PID参数
 * @return true: 成功, false: 失败
 */
bool PIDController_GetParams(PIDType_t type, PIDParams_t* params);

/**
 * @brief PID计算
 * @param type PID控制器类型
 * @param error 输入误差
 * @return PID输出值
 */
float PIDController_Compute(PIDType_t type, float error);

/**
 * @brief 更新目标和激光位置，计算PID输出
 * @param target_x 目标X坐标
 * @param target_y 目标Y坐标
 * @param laser_x 激光X坐标
 * @param laser_y 激光Y坐标
 * @param output_h 输出水平控制量
 * @param output_v 输出垂直控制量
 * @return true: 成功, false: 失败
 */
bool PIDController_Update(float target_x, float target_y, 
                         float laser_x, float laser_y,
                         float* output_h, float* output_v);

/**
 * @brief 重置PID控制器
 * @param type PID控制器类型
 */
void PIDController_Reset(PIDType_t type);

/**
 * @brief 重置所有PID控制器
 */
void PIDController_ResetAll(void);

/**
 * @brief 使能/禁用PID控制器
 * @param type PID控制器类型
 * @param enabled 使能状态
 */
void PIDController_SetEnabled(PIDType_t type, bool enabled);

/**
 * @brief 检查PID控制器是否使能
 * @param type PID控制器类型
 * @return true: 使能, false: 禁用
 */
bool PIDController_IsEnabled(PIDType_t type);

/**
 * @brief 设置采样时间
 * @param type PID控制器类型
 * @param dt 采样时间 (秒)
 */
void PIDController_SetSampleTime(PIDType_t type, float dt);

/**
 * @brief 获取PID控制器状态
 * @param type PID控制器类型
 * @return PID控制器状态指针
 */
PIDController_t* PIDController_GetController(PIDType_t type);

/**
 * @brief 获取PID系统状态
 * @return PID系统状态指针
 */
PIDSystem_t* PIDController_GetSystem(void);

/**
 * @brief 限制输出值范围
 * @param value 输入值
 * @param min 最小值
 * @param max 最大值
 * @return 限制后的值
 */
float PIDController_Constrain(float value, float min, float max);

/**
 * @brief 应用死区
 * @param error 误差值
 * @param deadzone 死区范围
 * @return 处理后的误差值
 */
float PIDController_ApplyDeadzone(float error, float deadzone);

/* 默认PID参数 */
#define PID_DEFAULT_KP_H        5.0f        // 水平轴默认Kp
#define PID_DEFAULT_KI_H        0.001f        // 水平轴默认Ki
#define PID_DEFAULT_KD_H        0.001f       // 水平轴默认Kd

#define PID_DEFAULT_KP_V        5.0f        // 垂直轴默认Kp
#define PID_DEFAULT_KI_V        0.001f        // 垂直轴默认Ki
#define PID_DEFAULT_KD_V        0.001f       // 垂直轴默认Kd

#define PID_DEFAULT_SAMPLE_TIME 0.02f       // 默认采样时间 20ms

/* 调试宏 */
#ifdef DEBUG_PID_CONTROLLER
#define PID_DEBUG(fmt, ...) printf("[PID] " fmt "\r\n", ##__VA_ARGS__)
#else
#define PID_DEBUG(fmt, ...)
#endif

#endif /* __PID_CONTROLLER_H */
