#ifndef __LASER_TRACKER_H
#define __LASER_TRACKER_H

#include "stm32f10x.h"
#include <stdbool.h>

/**
 * @file LaserTracker.h
 * @brief 激光追踪控制模块
 * @version 1.0
 * @date 2025-07-09
 * 
 * 功能：
 * - 管理激光追踪系统的高层逻辑
 * - 集成摄像头通信、PID控制、舵机控制
 * - 提供简洁的API接口给主程序调用
 */

/* PID控制器结构体 */
typedef struct {
    float kp, ki, kd;           // PID参数
    float error, last_error;    // 当前和上次误差
    float integral;             // 积分项
    float output;               // 输出值
    float max_output;           // 输出限幅
    float max_integral;         // 积分限幅
} PID_Controller_t;

/* 位置坐标结构体 */
typedef struct {
    int16_t x, y;               // 坐标值
    uint8_t valid;              // 有效标志
} Position_t;

/* 激光追踪系统状态 */
typedef struct {
    Position_t target_pos;      // 红色目标位置
    Position_t laser_pos;       // 绿色激光位置
    PID_Controller_t pid_h;     // 水平PID控制器
    PID_Controller_t pid_v;     // 垂直PID控制器
    uint16_t servo_h_pos;       // 水平舵机位置
    uint16_t servo_v_pos;       // 垂直舵机位置
    uint8_t tracking_active;    // 追踪激活标志
    uint32_t last_update_time;  // 上次更新时间
} LaserTracker_t;

/* 图像坐标范围 */
#define IMAGE_WIDTH         640
#define IMAGE_HEIGHT        480
#define IMAGE_CENTER_X      (IMAGE_WIDTH / 2)
#define IMAGE_CENTER_Y      (IMAGE_HEIGHT / 2)

/* 舵机位置范围 */
#define SERVO_POS_MIN       0
#define SERVO_POS_MAX       1000
#define SERVO_POS_CENTER    500

/* 控制参数 */
#define CONTROL_GAIN        0.1f        // 比例控制增益
#define DEADZONE_PIXELS     5.0f        // 死区像素数
#define MAX_INCREMENT       20.0f       // 最大单次增量

/* 函数声明 */
bool LaserTracker_Init(void);                   // 初始化激光追踪系统
void LaserTracker_Process(void);                // 处理激光追踪逻辑
void LaserTracker_DeInit(void);                 // 反初始化
bool LaserTracker_IsActive(void);               // 获取追踪状态
void LaserTracker_SetActive(bool active);       // 设置追踪状态
void LaserTracker_UpdatePIDParams(float kp_h, float ki_h, float kd_h, 
                                  float kp_v, float ki_v, float kd_v);  // 更新PID参数
void LaserTracker_GetServoPosition(uint16_t* h_pos, uint16_t* v_pos);  // 获取舵机位置

/* 数据更新接口（由CameraComm模块调用） */
void LaserTracker_UpdateTargetPosition(int16_t x, int16_t y);   // 更新目标位置
void LaserTracker_UpdateLaserPosition(int16_t x, int16_t y);    // 更新激光位置

#endif
