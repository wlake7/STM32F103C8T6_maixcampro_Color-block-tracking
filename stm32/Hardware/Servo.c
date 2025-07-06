/**
 * @file Servo.c
 * @brief STM32端舵机控制模块实现
 * @author AI Assistant
 * @date 2025-07-06
 */

#include "Servo.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include <string.h>

/* 私有变量 */
static uint8_t tx_buffer[SERVO_MAX_PACKET_SIZE];    // 发送缓冲区
static uint8_t rx_buffer[SERVO_MAX_PACKET_SIZE];    // 接收缓冲区
static uint8_t rx_index = 0;                       // 接收索引
static ServoPacket_t response_packet;              // 响应数据包
// static uint32_t last_command_time = 0;             // 最后命令时间 (暂未使用)

/* 全局变量定义 */
ServoStatus_t g_servo_vertical = {
    .id = SERVO_ID_VERTICAL,
    .state = SERVO_STATE_IDLE,
    .current_angle = SERVO_ANGLE_CENTER,
    .target_angle = SERVO_ANGLE_CENTER,
    .voltage = 0,
    .temperature = 0,
    .is_loaded = false,
    .last_update = 0
};

ServoStatus_t g_servo_horizontal = {
    .id = SERVO_ID_HORIZONTAL,
    .state = SERVO_STATE_IDLE,
    .current_angle = SERVO_ANGLE_CENTER,
    .target_angle = SERVO_ANGLE_CENTER,
    .voltage = 0,
    .temperature = 0,
    .is_loaded = false,
    .last_update = 0
};

ServoStats_t g_servo_stats = {0};

/* 私有函数声明 */
static void USART2_GPIO_Config(void);
static void USART2_Config(uint32_t baudrate);
static void Servo_SendByte(uint8_t data);
static void Servo_SendBytes(uint8_t* data, uint8_t length);
static void Servo_ParseResponse(void);

/**
 * @brief 初始化舵机控制模块
 */
bool Servo_Init(uint32_t baudrate)
{
    // 初始化GPIO和USART2 (用于舵机通信)
    USART2_GPIO_Config();
    USART2_Config(baudrate);
    
    // 初始化状态
    rx_index = 0;
    last_command_time = 0;
    
    // 重置统计信息
    Servo_ResetStats();
    
    // 初始化舵机 - 设置为加载状态
    Servo_SetLoad(SERVO_ID_VERTICAL, true);
    Servo_SetLoad(SERVO_ID_HORIZONTAL, true);
    
    // 移动到中心位置
    Servo_MoveToPosition(SERVO_ID_VERTICAL, SERVO_ANGLE_CENTER, 1000);
    Servo_MoveToPosition(SERVO_ID_HORIZONTAL, SERVO_ANGLE_CENTER, 1000);
    
    return true;
}

/**
 * @brief 配置USART2 GPIO
 */
static void USART2_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能GPIOA和USART2时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    
    // 配置PA2 (TX) 为推挽复用输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 配置PA3 (RX) 为浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief 配置USART2
 */
static void USART2_Config(uint32_t baudrate)
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
    USART_Init(USART2, &USART_InitStructure);
    
    // 配置NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // 使能接收中断
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    
    // 使能USART
    USART_Cmd(USART2, ENABLE);
}

/**
 * @brief 发送单个字节
 */
static void Servo_SendByte(uint8_t data)
{
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    USART_SendData(USART2, data);
}

/**
 * @brief 发送多个字节
 */
static void Servo_SendBytes(uint8_t* data, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++) {
        Servo_SendByte(data[i]);
    }
}

/**
 * @brief 计算舵机命令校验和
 */
uint8_t Servo_CalculateChecksum(uint8_t* data, uint8_t length)
{
    uint8_t sum = 0;
    for (uint8_t i = 0; i < length; i++) {
        sum += data[i];
    }
    return ~sum; // 取反
}

/**
 * @brief 发送舵机命令包
 */
bool Servo_SendCommand(uint8_t id, ServoCommand_t cmd, uint8_t* data, uint8_t length)
{
    if (length > SERVO_MAX_DATA_SIZE) {
        return false;
    }
    
    // 构建命令包
    tx_buffer[0] = SERVO_HEADER_BYTE1;
    tx_buffer[1] = SERVO_HEADER_BYTE2;
    tx_buffer[2] = id;
    tx_buffer[3] = length + 3; // 数据长度 + ID + Length + Command
    tx_buffer[4] = (uint8_t)cmd;
    
    // 复制数据
    if (data && length > 0) {
        memcpy(&tx_buffer[5], data, length);
    }
    
    // 计算校验和 (从ID开始到数据结束)
    uint8_t checksum = Servo_CalculateChecksum(&tx_buffer[2], length + 3);
    tx_buffer[5 + length] = checksum;
    
    // 发送命令包
    Servo_SendBytes(tx_buffer, 6 + length);
    
    // 更新统计和时间
    g_servo_stats.commands_sent++;
    last_command_time = 0; // 这里应该使用系统时钟
    
    return true;
}

/**
 * @brief 控制舵机移动到指定位置
 */
bool Servo_MoveToPosition(uint8_t id, uint16_t angle, uint16_t time)
{
    if (angle > SERVO_ANGLE_MAX || time > SERVO_TIME_MAX) {
        return false;
    }
    
    uint8_t data[4];
    data[0] = (uint8_t)(angle & 0xFF);          // 角度低字节
    data[1] = (uint8_t)((angle >> 8) & 0xFF);   // 角度高字节
    data[2] = (uint8_t)(time & 0xFF);           // 时间低字节
    data[3] = (uint8_t)((time >> 8) & 0xFF);    // 时间高字节
    
    // 更新目标角度
    ServoStatus_t* status = Servo_GetStatus(id);
    if (status) {
        status->target_angle = angle;
        status->state = SERVO_STATE_MOVING;
    }
    
    return Servo_SendCommand(id, SERVO_MOVE_TIME_WRITE, data, 4);
}

/**
 * @brief 控制舵机移动到指定位置(等待模式)
 */
bool Servo_MoveToPositionWait(uint8_t id, uint16_t angle, uint16_t time)
{
    if (angle > SERVO_ANGLE_MAX || time > SERVO_TIME_MAX) {
        return false;
    }
    
    uint8_t data[4];
    data[0] = (uint8_t)(angle & 0xFF);          // 角度低字节
    data[1] = (uint8_t)((angle >> 8) & 0xFF);   // 角度高字节
    data[2] = (uint8_t)(time & 0xFF);           // 时间低字节
    data[3] = (uint8_t)((time >> 8) & 0xFF);    // 时间高字节
    
    // 更新目标角度
    ServoStatus_t* status = Servo_GetStatus(id);
    if (status) {
        status->target_angle = angle;
        status->state = SERVO_STATE_WAITING;
    }
    
    return Servo_SendCommand(id, SERVO_MOVE_TIME_WAIT_WRITE, data, 4);
}

/**
 * @brief 启动舵机运动
 */
bool Servo_StartMove(uint8_t id)
{
    ServoStatus_t* status = Servo_GetStatus(id);
    if (status && status->state == SERVO_STATE_WAITING) {
        status->state = SERVO_STATE_MOVING;
    }
    
    return Servo_SendCommand(id, SERVO_MOVE_START, NULL, 0);
}

/**
 * @brief 停止舵机运动
 */
bool Servo_StopMove(uint8_t id)
{
    ServoStatus_t* status = Servo_GetStatus(id);
    if (status) {
        status->state = SERVO_STATE_IDLE;
    }
    
    return Servo_SendCommand(id, SERVO_MOVE_STOP, NULL, 0);
}

/**
 * @brief 读取舵机当前位置
 */
bool Servo_ReadPosition(uint8_t id)
{
    return Servo_SendCommand(id, SERVO_POS_READ, NULL, 0);
}

/**
 * @brief 设置舵机加载状态
 */
bool Servo_SetLoad(uint8_t id, bool load)
{
    uint8_t data[1];
    data[0] = load ? 1 : 0;
    
    ServoStatus_t* status = Servo_GetStatus(id);
    if (status) {
        status->is_loaded = load;
    }
    
    return Servo_SendCommand(id, SERVO_LOAD_OR_UNLOAD_WRITE, data, 1);
}

/**
 * @brief 设置舵机角度偏差
 */
bool Servo_SetAngleOffset(uint8_t id, int8_t offset)
{
    if (offset < -125 || offset > 125) {
        return false;
    }
    
    uint8_t data[1];
    data[0] = (uint8_t)offset; // 强制转换为unsigned char
    
    return Servo_SendCommand(id, SERVO_ANGLE_OFFSET_ADJUST, data, 1);
}

/**
 * @brief 获取舵机状态
 */
ServoStatus_t* Servo_GetStatus(uint8_t id)
{
    if (id == SERVO_ID_VERTICAL) {
        return &g_servo_vertical;
    } else if (id == SERVO_ID_HORIZONTAL) {
        return &g_servo_horizontal;
    }
    return NULL;
}

/**
 * @brief 获取舵机统计信息
 */
ServoStats_t* Servo_GetStats(void)
{
    return &g_servo_stats;
}

/**
 * @brief 重置舵机统计信息
 */
void Servo_ResetStats(void)
{
    memset(&g_servo_stats, 0, sizeof(ServoStats_t));
}

/**
 * @brief 角度值转换 (0-1000 -> 0-240度)
 */
float Servo_ConvertAngleToFloat(uint16_t angle_raw)
{
    return (float)angle_raw * 240.0f / 1000.0f;
}

/**
 * @brief 角度值转换 (0-240度 -> 0-1000)
 */
uint16_t Servo_ConvertFloatToAngle(float angle_float)
{
    uint16_t angle = (uint16_t)(angle_float * 1000.0f / 240.0f);
    if (angle > SERVO_ANGLE_MAX) {
        angle = SERVO_ANGLE_MAX;
    }
    return angle;
}

/**
 * @brief 验证舵机响应包
 */
bool Servo_ValidateResponse(ServoPacket_t* packet)
{
    if (!packet) {
        return false;
    }

    // 检查帧头
    if (packet->header[0] != SERVO_HEADER_BYTE1 ||
        packet->header[1] != SERVO_HEADER_BYTE2) {
        return false;
    }

    // 检查数据长度
    if (packet->length > SERVO_MAX_DATA_SIZE + 3) {
        return false;
    }

    // 验证校验和
    uint8_t calculated_checksum = Servo_CalculateChecksum(
        (uint8_t*)&packet->id, packet->length);

    return (calculated_checksum == packet->checksum);
}

/**
 * @brief 解析舵机响应
 */
static void Servo_ParseResponse(void)
{
    // 检查最小包长度
    if (rx_index < 6) {
        g_servo_stats.checksum_errors++;
        return;
    }

    // 构建响应包
    response_packet.header[0] = rx_buffer[0];
    response_packet.header[1] = rx_buffer[1];
    response_packet.id = rx_buffer[2];
    response_packet.length = rx_buffer[3];
    response_packet.command = rx_buffer[4];

    // 检查数据长度
    if (response_packet.length > SERVO_MAX_DATA_SIZE + 3 ||
        rx_index != (response_packet.length + 3)) {
        g_servo_stats.checksum_errors++;
        return;
    }

    // 复制数据
    uint8_t data_length = response_packet.length - 3;
    if (data_length > 0) {
        memcpy(response_packet.data, &rx_buffer[5], data_length);
    }

    // 获取校验和
    response_packet.checksum = rx_buffer[rx_index - 1];

    // 验证响应包
    if (!Servo_ValidateResponse(&response_packet)) {
        g_servo_stats.checksum_errors++;
        return;
    }

    // 更新统计
    g_servo_stats.responses_received++;

    // 处理响应数据
    ServoStatus_t* status = Servo_GetStatus(response_packet.id);
    if (!status) {
        return;
    }

    // 根据命令类型处理响应
    switch (response_packet.command) {
        case SERVO_POS_READ:
            if (data_length >= 2) {
                status->current_angle = response_packet.data[0] |
                                      (response_packet.data[1] << 8);
                status->last_update = 0; // 使用系统时钟
            }
            break;

        case SERVO_VIN_READ:
            if (data_length >= 2) {
                status->voltage = response_packet.data[0] |
                                (response_packet.data[1] << 8);
            }
            break;

        case SERVO_TEMP_READ:
            if (data_length >= 1) {
                status->temperature = response_packet.data[0];
            }
            break;

        case SERVO_LOAD_OR_UNLOAD_READ:
            if (data_length >= 1) {
                status->is_loaded = (response_packet.data[0] != 0);
            }
            break;

        default:
            // 其他命令的响应处理
            break;
    }
}

/**
 * @brief 舵机模块主循环处理
 */
void Servo_Process(void)
{
    // 处理接收到的响应数据
    if (rx_index > 0) {
        Servo_ParseResponse();
        rx_index = 0; // 重置接收索引
    }
}

/**
 * @brief 处理舵机响应数据
 */
void Servo_ProcessResponse(uint8_t* data, uint8_t length)
{
    if (!data || length == 0 || length > SERVO_MAX_PACKET_SIZE) {
        return;
    }

    // 复制数据到接收缓冲区
    memcpy(rx_buffer, data, length);
    rx_index = length;

    // 解析响应
    Servo_ParseResponse();
    rx_index = 0;
}

/**
 * @brief 检查舵机响应超时
 */
bool Servo_CheckTimeout(uint32_t timeout_ms)
{
    // 这里需要实现系统时钟比较
    // 暂时返回false
    return false;
}

/**
 * @brief USART2中断服务函数
 */
void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        uint8_t data = USART_ReceiveData(USART2);

        // 简单的数据接收处理
        if (rx_index < SERVO_MAX_PACKET_SIZE) {
            rx_buffer[rx_index++] = data;
        } else {
            rx_index = 0; // 缓冲区溢出，重置
        }

        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}
