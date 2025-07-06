/**
 * @file Communication.c
 * @brief STM32端通信协议模块实现
 * @author AI Assistant
 * @date 2025-07-06
 */

#include "Communication.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include <string.h>

/* 私有变量 */
static uint8_t rx_buffer[COMM_MAX_PACKET_SIZE];     // 接收缓冲区
static uint8_t rx_index = 0;                       // 接收索引
static uint8_t tx_buffer[COMM_MAX_PACKET_SIZE];     // 发送缓冲区
static CommPacket_t current_packet;                // 当前数据包
// static uint32_t last_receive_time = 0;             // 最后接收时间 (暂未使用)

/* 全局变量定义 */
CommState_t g_comm_state = COMM_STATE_IDLE;
CommStats_t g_comm_stats = {0};
CommCallback_t g_comm_callback = NULL;

/* 私有函数声明 */
static void USART_GPIO_Config(void);
static void USART_Config(uint32_t baudrate);
static void Communication_ParsePacket(void);
static void Communication_SendByte(uint8_t data);
static void Communication_SendBytes(uint8_t* data, uint8_t length);

/**
 * @brief 初始化通信模块
 */
bool Communication_Init(uint32_t baudrate, CommCallback_t callback)
{
    // 保存回调函数
    g_comm_callback = callback;
    
    // 初始化GPIO和USART
    USART_GPIO_Config();
    USART_Config(baudrate);
    
    // 初始化状态
    g_comm_state = COMM_STATE_IDLE;
    rx_index = 0;
    last_receive_time = 0;
    
    // 重置统计信息
    Communication_ResetStats();
    
    return true;
}

/**
 * @brief 配置USART GPIO
 */
static void USART_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能GPIOA和USART1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
    
    // 配置PA9 (TX) 为推挽复用输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 配置PA10 (RX) 为浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief 配置USART
 */
static void USART_Config(uint32_t baudrate)
{
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // 配置USART参数
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    
    // 配置NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // 使能接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    // 使能USART
    USART_Cmd(USART1, ENABLE);
}

/**
 * @brief 发送单个字节
 */
static void Communication_SendByte(uint8_t data)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, data);
}

/**
 * @brief 发送多个字节
 */
static void Communication_SendBytes(uint8_t* data, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++) {
        Communication_SendByte(data[i]);
    }
}

/**
 * @brief 计算校验和
 */
uint8_t Communication_CalculateChecksum(uint8_t* data, uint8_t length)
{
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < length; i++) {
        checksum += data[i];
    }
    return checksum & 0xFF;
}

/**
 * @brief 发送数据包
 */
bool Communication_SendPacket(CommCommand_t cmd, uint8_t* data, uint8_t length)
{
    if (length > COMM_MAX_DATA_SIZE) {
        return false;
    }
    
    // 构建数据包
    tx_buffer[0] = COMM_HEADER_BYTE1;
    tx_buffer[1] = COMM_HEADER_BYTE2;
    tx_buffer[2] = length;
    tx_buffer[3] = (uint8_t)cmd;
    
    // 复制数据
    if (data && length > 0) {
        memcpy(&tx_buffer[4], data, length);
    }
    
    // 计算校验和
    uint8_t checksum = Communication_CalculateChecksum(&tx_buffer[2], length + 2);
    tx_buffer[4 + length] = checksum;
    
    // 发送数据包
    Communication_SendBytes(tx_buffer, 5 + length);
    
    // 更新统计
    g_comm_stats.packets_sent++;
    
    return true;
}

/**
 * @brief 发送位置数据
 */
bool Communication_SendPositionData(PositionData_t* target_pos, PositionData_t* laser_pos)
{
    if (!target_pos || !laser_pos) {
        return false;
    }
    
    uint8_t data[16];
    
    // 打包目标位置数据
    data[0] = (uint8_t)(target_pos->x & 0xFF);
    data[1] = (uint8_t)((target_pos->x >> 8) & 0xFF);
    data[2] = (uint8_t)(target_pos->y & 0xFF);
    data[3] = (uint8_t)((target_pos->y >> 8) & 0xFF);
    data[4] = (uint8_t)(target_pos->confidence & 0xFF);
    data[5] = (uint8_t)((target_pos->confidence >> 8) & 0xFF);
    data[6] = (uint8_t)(target_pos->timestamp & 0xFF);
    data[7] = (uint8_t)((target_pos->timestamp >> 8) & 0xFF);
    
    // 打包激光位置数据
    data[8] = (uint8_t)(laser_pos->x & 0xFF);
    data[9] = (uint8_t)((laser_pos->x >> 8) & 0xFF);
    data[10] = (uint8_t)(laser_pos->y & 0xFF);
    data[11] = (uint8_t)((laser_pos->y >> 8) & 0xFF);
    data[12] = (uint8_t)(laser_pos->confidence & 0xFF);
    data[13] = (uint8_t)((laser_pos->confidence >> 8) & 0xFF);
    data[14] = (uint8_t)(laser_pos->timestamp & 0xFF);
    data[15] = (uint8_t)((laser_pos->timestamp >> 8) & 0xFF);
    
    return Communication_SendPacket(CMD_TARGET_POSITION, data, 16);
}

/**
 * @brief 发送PID参数
 */
bool Communication_SendPIDParams(PIDParams_t* params)
{
    if (!params) {
        return false;
    }
    
    uint8_t data[12];
    
    data[0] = (uint8_t)(params->kp_h & 0xFF);
    data[1] = (uint8_t)((params->kp_h >> 8) & 0xFF);
    data[2] = (uint8_t)(params->ki_h & 0xFF);
    data[3] = (uint8_t)((params->ki_h >> 8) & 0xFF);
    data[4] = (uint8_t)(params->kd_h & 0xFF);
    data[5] = (uint8_t)((params->kd_h >> 8) & 0xFF);
    data[6] = (uint8_t)(params->kp_v & 0xFF);
    data[7] = (uint8_t)((params->kp_v >> 8) & 0xFF);
    data[8] = (uint8_t)(params->ki_v & 0xFF);
    data[9] = (uint8_t)((params->ki_v >> 8) & 0xFF);
    data[10] = (uint8_t)(params->kd_v & 0xFF);
    data[11] = (uint8_t)((params->kd_v >> 8) & 0xFF);
    
    return Communication_SendPacket(CMD_PID_PARAMS, data, 12);
}

/**
 * @brief 发送系统状态
 */
bool Communication_SendSystemStatus(SystemStatus_t* status)
{
    if (!status) {
        return false;
    }
    
    uint8_t data[4];
    data[0] = status->system_ready;
    data[1] = status->servo_status;
    data[2] = status->tracking_mode;
    data[3] = status->error_code;
    
    return Communication_SendPacket(CMD_SYSTEM_STATUS, data, 4);
}

/**
 * @brief 发送心跳包
 */
bool Communication_SendHeartbeat(void)
{
    return Communication_SendPacket(CMD_HEARTBEAT, NULL, 0);
}

/**
 * @brief 验证数据包
 */
bool Communication_ValidatePacket(CommPacket_t* packet)
{
    if (!packet) {
        return false;
    }
    
    // 检查帧头
    if (packet->header[0] != COMM_HEADER_BYTE1 || 
        packet->header[1] != COMM_HEADER_BYTE2) {
        return false;
    }
    
    // 检查数据长度
    if (packet->length > COMM_MAX_DATA_SIZE) {
        return false;
    }
    
    // 验证校验和
    uint8_t calculated_checksum = Communication_CalculateChecksum(
        (uint8_t*)&packet->length, packet->length + 2);
    
    return (calculated_checksum == packet->checksum);
}

/**
 * @brief 获取通信状态
 */
CommState_t Communication_GetState(void)
{
    return g_comm_state;
}

/**
 * @brief 获取通信统计信息
 */
CommStats_t* Communication_GetStats(void)
{
    return &g_comm_stats;
}

/**
 * @brief 重置通信统计信息
 */
void Communication_ResetStats(void)
{
    memset(&g_comm_stats, 0, sizeof(CommStats_t));
}

/**
 * @brief 解析数据包
 */
static void Communication_ParsePacket(void)
{
    // 检查最小包长度
    if (rx_index < 5) {
        g_comm_stats.format_errors++;
        return;
    }

    // 构建数据包
    current_packet.header[0] = rx_buffer[0];
    current_packet.header[1] = rx_buffer[1];
    current_packet.length = rx_buffer[2];
    current_packet.command = rx_buffer[3];

    // 检查数据长度
    if (current_packet.length > COMM_MAX_DATA_SIZE ||
        rx_index != (5 + current_packet.length)) {
        g_comm_stats.format_errors++;
        return;
    }

    // 复制数据
    if (current_packet.length > 0) {
        memcpy(current_packet.data, &rx_buffer[4], current_packet.length);
    }

    // 获取校验和
    current_packet.checksum = rx_buffer[4 + current_packet.length];

    // 验证数据包
    if (!Communication_ValidatePacket(&current_packet)) {
        g_comm_stats.checksum_errors++;
        return;
    }

    // 更新统计
    g_comm_stats.packets_received++;

    // 调用回调函数处理数据
    if (g_comm_callback) {
        g_comm_callback((CommCommand_t)current_packet.command,
                       current_packet.data, current_packet.length);
    }
}

/**
 * @brief 串口中断处理函数
 */
void Communication_IRQHandler(uint8_t data)
{
    // 更新接收时间
    last_receive_time = 0; // 这里应该使用系统时钟

    // 状态机处理
    switch (g_comm_state) {
        case COMM_STATE_IDLE:
            if (data == COMM_HEADER_BYTE1) {
                rx_buffer[0] = data;
                rx_index = 1;
                g_comm_state = COMM_STATE_RECEIVING;
            }
            break;

        case COMM_STATE_RECEIVING:
            rx_buffer[rx_index++] = data;

            // 检查缓冲区溢出
            if (rx_index >= COMM_MAX_PACKET_SIZE) {
                g_comm_state = COMM_STATE_IDLE;
                rx_index = 0;
                g_comm_stats.format_errors++;
                break;
            }

            // 检查是否接收完整包
            if (rx_index >= 3) {
                uint8_t expected_length = rx_buffer[2];
                if (rx_index >= (5 + expected_length)) {
                    g_comm_state = COMM_STATE_PROCESSING;
                }
            }
            break;

        case COMM_STATE_PROCESSING:
            // 不应该在处理状态接收数据
            g_comm_state = COMM_STATE_IDLE;
            rx_index = 0;
            break;

        case COMM_STATE_ERROR:
            // 错误状态，重置
            g_comm_state = COMM_STATE_IDLE;
            rx_index = 0;
            break;
    }
}

/**
 * @brief 通信模块主循环处理
 */
void Communication_Process(void)
{
    if (g_comm_state == COMM_STATE_PROCESSING) {
        Communication_ParsePacket();
        g_comm_state = COMM_STATE_IDLE;
        rx_index = 0;
    }
}

/**
 * @brief 检查通信超时
 */
bool Communication_CheckTimeout(uint32_t timeout_ms)
{
    // 这里需要实现系统时钟比较
    // 暂时返回false
    return false;
}

/**
 * @brief USART1中断服务函数
 */
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        uint8_t data = USART_ReceiveData(USART1);
        Communication_IRQHandler(data);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
