/**
 * @file usart2_irq.c
 * @brief USART2中断处理函数
 * @version 1.0
 * @date 2025-07-07
 * 
 * 专门处理USART2中断，调用ControlBoard模块的中断处理函数
 */

#include "stm32f10x.h"
#include "ControlBoard.h"

/**
 * @brief USART2中断服务函数
 */
void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        uint8_t data = USART_ReceiveData(USART2);
        
        // 调用控制板中断处理函数进行协议解析
        ControlBoard_IRQHandler(data);
        
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}
