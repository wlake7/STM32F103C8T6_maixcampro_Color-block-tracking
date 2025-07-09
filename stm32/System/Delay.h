#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

/* 函数声明 */
uint32_t System_GetTick(void);  // 获取系统毫秒计数
void Delay_us(uint32_t us);     // 微秒延时
void Delay_ms(uint32_t ms);     // 毫秒延时
void Delay_s(uint32_t s);       // 秒延时

/* SysTick中断处理函数 */
void SysTick_Handler(void);

#endif
