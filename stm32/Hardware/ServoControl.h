#ifndef __SERVO_CONTROL_H
#define __SERVO_CONTROL_H

/**
 * @file ServoControl.h
 * @brief 舵机控制接口重定向
 * @version 1.0
 * @date 2025-07-09
 *
 * 重定向到ServoBoard模块，保持接口兼容性
 */

#include "ServoBoard.h"

/* 兼容性宏定义 */
#define SERVO_POS_MIN       SERVO_POSITION_MIN
#define SERVO_POS_MAX       SERVO_POSITION_MAX
#define SERVO_POS_CENTER    SERVO_POSITION_CENTER

#endif
