#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"

/**
 * @file Timer.h
 * @brief 定时器1系统时间管理模块
 * @version 1.0
 * @date 2025-07-09
 * 
 * 修改说明：
 * - 使用定时器1作为系统时间标准（1ms中断）
 * - SysTick专用于延时功能
 * - 提供毫秒级系统时间计数
 */

/* 函数声明 */
void Timer1_Init(void);                 // 初始化定时器1
uint32_t Timer_GetSystemTick(void);     // 获取系统毫秒计数
void Timer_ResetSystemTick(void);       // 重置系统时间计数

/* 定时器1中断处理函数 */
void TIM1_UP_IRQHandler(void);

/* 时间相关宏定义 */
#define TIMER_1MS_TICKS     1000        // 1ms对应的计数值
#define TIMER_MAX_COUNT     0xFFFFFFFF  // 最大计数值

#endif
