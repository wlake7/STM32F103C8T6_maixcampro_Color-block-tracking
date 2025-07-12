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
    float servo_h_angle;        // 水平舵机角度 (0°-240°)
    float servo_v_angle;        // 垂直舵机角度 (0°-240°)
    uint8_t tracking_active;    // 追踪激活标志
    uint32_t last_update_time;  // 上次更新时间
} LaserTracker_t;

/* 图像坐标范围 */
#define IMAGE_WIDTH         640
#define IMAGE_HEIGHT        480
#define IMAGE_CENTER_X      (IMAGE_WIDTH / 2)
#define IMAGE_CENTER_Y      (IMAGE_HEIGHT / 2)


#define SERVO_POS_CENTER    500
/*=========================================================================================*/
/* PID控制参数宏定义 - 便于调试 */
#define PID_KP_H            0.07f        // 水平轴比例增益 (原 2.0 * 0.4)
#define PID_KI_H            0.001f       // 水平轴积分增益 (原 0.2 * 0.4)
#define PID_KD_H            0.03f        // 水平轴微分增益

#define PID_KP_V            0.07f        // 垂直轴比例增益 (原 1.0 * 0.4)
#define PID_KI_V            0.001f       // 垂直轴积分增益 (原 0.2 * 0.4)
#define PID_KD_V            0.03f        // 垂直轴微分增益

#define PID_MAX_OUTPUT      10.0f       // PID输出限幅 (角度增量，度)
#define PID_MAX_INTEGRAL    5.0f        // PID积分限幅 (输出限幅的50%)
/* 控制算法参数宏定义 - 便于调试 */
#define DEADZONE_PIXELS     30.0f        // 死区像素数，避免小误差抖动
#define MAX_SERVO_INCREMENT 4.0f        // 舵机最大单次角度增量 (度)
#define SERVO_MOVE_TIME     20          // 舵机移动时间(ms) - 快速响应
/* 系统控制参数宏定义 - 便于调试 */
#define DEBUG_UPDATE_DIV    3           // OLED调试显示分频 (每3次更新一次)
//#define CONTROL_FREQUENCY   20          // 控制频率(Hz)主函数延时
//#define CONTROL_PERIOD_MS   (1000/CONTROL_FREQUENCY)  // 控制周期(ms)
//#define TIMEOUT_MS          1000        // 数据超时时间(ms)
/* 坐标转换参数宏定义 - 便于调试 */
//#define PIXEL_TO_SERVO_GAIN 1.0f        // 像素到舵机位置的转换增益，没有


/* 舵机角度参数宏定义 - 便于调试 */
#define SERVO_ANGLE_MIN     0.0f        // 舵机最小角度 (0°)
#define SERVO_ANGLE_MAX     240.0f      // 舵机最大角度 (240°)
#define SERVO_ANGLE_CENTER  120.0f      // 舵机中心角度 (120°)
#define SERVO_SAFE_MIN      10.0f       // 舵机安全最小角度 (10°)
#define SERVO_SAFE_MAX      230.0f      // 舵机安全最大角度 (230°)

/* 像素到角度转换参数宏定义 - 便于调试 */
#define PIXEL_TO_ANGLE_GAIN_H   (SERVO_ANGLE_MAX / IMAGE_WIDTH)    // 水平像素到角度转换增益
#define PIXEL_TO_ANGLE_GAIN_V   (SERVO_ANGLE_MAX / IMAGE_HEIGHT)   // 垂直像素到角度转换增益
#define ERROR_LIMIT_PIXELS      400.0f  // 最大允许误差(像素)

/* 调试开关宏定义 */
#define ENABLE_PID_DEBUG    1           // 启用PID调试输出
#define ENABLE_OLED_DEBUG   1           // 启用OLED调试显示
#define ENABLE_SAFETY_CHECK 0           // 启用安全检查
/*======================================================================================*/
/* 函数声明 */
bool LaserTracker_Init(void);                   // 初始化激光追踪系统
void LaserTracker_Process(void);                // 处理激光追踪逻辑
void LaserTracker_DeInit(void);                 // 反初始化
bool LaserTracker_IsActive(void);               // 获取追踪状态
void LaserTracker_SetActive(bool active);       // 设置追踪状态
void LaserTracker_UpdatePIDParams(float kp_h, float ki_h, float kd_h,
                                  float kp_v, float ki_v, float kd_v);  // 更新PID参数
void LaserTracker_GetServoAngle(float* h_angle, float* v_angle);       // 获取舵机角度
void LaserTracker_GetServoPosition(uint16_t* h_pos, uint16_t* v_pos);  // 获取舵机位置(兼容)

/* 数据更新接口（由CameraComm模块调用） */
void LaserTracker_UpdateTargetPosition(int16_t x, int16_t y);   // 更新目标位置
void LaserTracker_UpdateLaserPosition(int16_t x, int16_t y);    // 更新激光位置

#endif
