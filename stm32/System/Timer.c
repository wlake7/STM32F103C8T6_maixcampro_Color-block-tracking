#include "Timer.h"

/**
 * @file Timer.c
 * @brief 定时器1系统时间管理模块实现
 * @version 1.0
 * @date 2025-07-09
 * 
 * 修改说明：
 * - 使用TIM1作为系统时间基准，1ms中断
 * - 替代原SysTick的时间计数功能
 * - SysTick专用于精确延时
 */

/* 全局系统时间计数器 */
static volatile uint32_t g_system_tick_ms = 0;

/**
 * @brief 初始化定时器1作为系统时间基准
 * @param 无
 * @retval 无
 * 
 * 配置说明：
 * - 时钟源：72MHz
 * - 预分频：72-1 (得到1MHz)
 * - 自动重装载：1000-1 (1ms中断)
 */
void Timer1_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // 使能TIM1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    
    // 配置TIM1基本参数
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;           // 自动重装载值 (1ms)
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;          // 预分频 (72MHz -> 1MHz)
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;        // 重复计数器
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    
    // 使能TIM1更新中断
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    
    // 配置NVIC中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // 子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // 启动定时器
    TIM_Cmd(TIM1, ENABLE);
    
    // 重置系统时间计数
    g_system_tick_ms = 0;
}

/**
 * @brief 获取系统毫秒计数
 * @param 无
 * @retval 当前系统毫秒计数
 */
uint32_t Timer_GetSystemTick(void)
{
    return g_system_tick_ms;
}

/**
 * @brief 重置系统时间计数
 * @param 无
 * @retval 无
 */
void Timer_ResetSystemTick(void)
{
    g_system_tick_ms = 0;
}

/**
 * @brief TIM1更新中断处理函数
 * @param 无
 * @retval 无
 * 
 * 注意：此函数需要在stm32f10x_it.c中声明为extern并调用
 * 遵循项目事实第8条要求
 */
void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {
        // 清除中断标志
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
        
        // 系统时间计数递增
        g_system_tick_ms++;
    }
}
