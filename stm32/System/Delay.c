#include "stm32f10x.h"
#include "Timer.h"

/**
  * @brief  系统时钟获取函数
  * @param  无
  * @retval 当前系统毫秒计数
  *
  * 修改说明：
  * - 改为调用Timer模块的Timer_GetSystemTick()
  * - 时间基准从SysTick改为TIM1
  */
uint32_t System_GetTick(void)
{
    return Timer_GetSystemTick();
}

/**
  * @brief  SysTick中断处理函数
  * @param  无
  * @retval 无
  *
  * 修改说明：
  * - 移除时间计数功能，SysTick专用于延时
  * - 系统时间计数由TIM1负责
  */
void SysTick_Handler(void)
{
    // SysTick现在专用于延时功能，不再计数系统时间
    // 系统时间由Timer模块的TIM1负责
}

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
