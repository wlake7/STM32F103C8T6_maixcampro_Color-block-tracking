/**
 * @file CameraComm.c
 * @brief 摄像头通信模块实现
 * @version 1.0
 * @date 2025-07-09
 */

#include "CameraComm.h"
#include "LaserTracker.h"
#include "Delay.h"
#include <string.h>

/* 全局变量定义 */
CameraCommSystem_t g_camera_comm_system;

/* 私有变量 */
static uint8_t rx_buffer[CAMERA_MAX_PACKET_SIZE];
static uint8_t rx_index = 0;
static bool packet_received = false;
static uint32_t last_receive_time = 0;
static bool new_data_flag = false;

/* 私有函数声明 */
static void CameraComm_USART1_Init(void);
static void CameraComm_SendByte(uint8_t data);
static bool CameraComm_SendPacket(uint8_t command, uint8_t* data, uint8_t data_len);
static void CameraComm_ParsePacket(uint8_t* packet, uint8_t length);
static uint8_t CameraComm_CalculateChecksum(uint8_t* data, uint8_t length);

/**
 * @brief 初始化摄像头通信模块
 */
bool CameraComm_Init(void)
{
    // 清零系统状态
    memset(&g_camera_comm_system, 0, sizeof(CameraCommSystem_t));

    // 初始化USART1用于摄像头通信
    CameraComm_USART1_Init();

    // 设置初始状态
    g_camera_comm_system.initialized = true;
    g_camera_comm_system.communication_ok = false;
    
    // 重置接收状态
    rx_index = 0;
    packet_received = false;
    new_data_flag = false;
    
    CAMERA_COMM_DEBUG("Camera communication initialized");
    return true;
}

/**
 * @brief 反初始化摄像头通信模块
 */
void CameraComm_DeInit(void)
{
    g_camera_comm_system.initialized = false;
    g_camera_comm_system.communication_ok = false;
    CAMERA_COMM_DEBUG("Camera communication deinitialized");
}

/**
 * @brief 初始化USART1用于摄像头通信
 */
static void CameraComm_USART1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 使能GPIOA和USART1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    // 配置PA9 (TX) 为推挽复用输出
    GPIO_InitStructure.GPIO_Pin = CAMERA_UART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CAMERA_UART_GPIO_PORT, &GPIO_InitStructure);

    // 配置PA10 (RX) 为浮空输入
    GPIO_InitStructure.GPIO_Pin = CAMERA_UART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(CAMERA_UART_GPIO_PORT, &GPIO_InitStructure);

    // 配置USART参数
    USART_InitStructure.USART_BaudRate = CAMERA_UART_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(CAMERA_UART, &USART_InitStructure);

    // 配置NVIC中断
    NVIC_InitStructure.NVIC_IRQChannel = CAMERA_UART_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 使能接收中断
    USART_ITConfig(CAMERA_UART, USART_IT_RXNE, ENABLE);

    // 使能USART
    USART_Cmd(CAMERA_UART, ENABLE);
}

/**
 * @brief 发送单个字节到摄像头
 */
static void CameraComm_SendByte(uint8_t data)
{
    while (USART_GetFlagStatus(CAMERA_UART, USART_FLAG_TXE) == RESET);
    USART_SendData(CAMERA_UART, data);
}

/**
 * @brief 计算校验和
 */
static uint8_t CameraComm_CalculateChecksum(uint8_t* data, uint8_t length)
{
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < length; i++) {
        checksum += data[i];
    }
    return checksum & 0xFF;
}

/**
 * @brief 发送数据包到摄像头
 */
static bool CameraComm_SendPacket(uint8_t command, uint8_t* data, uint8_t data_len)
{
    if (data_len > CAMERA_MAX_PACKET_SIZE - 5) {
        return false;
    }

    // 构造数据包
    uint8_t packet[CAMERA_MAX_PACKET_SIZE];
    uint8_t packet_len = 0;

    packet[packet_len++] = CAMERA_PACKET_HEADER1;   // 帧头1
    packet[packet_len++] = CAMERA_PACKET_HEADER2;   // 帧头2
    packet[packet_len++] = data_len;                // 数据长度
    packet[packet_len++] = command;                 // 命令

    // 添加参数数据
    if (data && data_len > 0) {
        memcpy(&packet[packet_len], data, data_len);
        packet_len += data_len;
    }

    // 计算并添加校验和
    uint8_t checksum = CameraComm_CalculateChecksum(&packet[2], packet_len - 2);
    packet[packet_len++] = checksum;

    // 发送数据包
    for (uint8_t i = 0; i < packet_len; i++) {
        CameraComm_SendByte(packet[i]);
    }

    return true;
}

/**
 * @brief 获取最新的追踪数据
 */
bool CameraComm_GetLatestData(TrackingData_t* data)
{
    if (!data || !new_data_flag) {
        return false;
    }

    // 复制最新数据
    memcpy(data, &g_camera_comm_system.latest_data, sizeof(TrackingData_t));
    new_data_flag = false;  // 清除新数据标志
    
    return true;
}

/**
 * @brief 检查是否有新的追踪数据
 */
bool CameraComm_HasNewData(void)
{
    return new_data_flag;
}

/**
 * @brief 解析接收到的数据包
 */
static void CameraComm_ParsePacket(uint8_t* packet, uint8_t length)
{
    if (!packet || length < 4) return;

    uint8_t command = packet[3];
    uint8_t data_len = packet[2];
    uint8_t* data = &packet[4];

    switch (command) {
        case CMD_TARGET_POSITION:
            if (data_len >= 4) {  // target_x(2) + target_y(2)
                // 解析目标位置数据
                g_camera_comm_system.latest_data.target.x = (int16_t)(data[0] | (data[1] << 8));
                g_camera_comm_system.latest_data.target.y = (int16_t)(data[2] | (data[3] << 8));

                // 设置目标数据有效性
                g_camera_comm_system.latest_data.target.valid = true;
                g_camera_comm_system.latest_data.target.confidence = 100;  // 默认置信度
                g_camera_comm_system.latest_data.target.timestamp = System_GetTick() & 0xFFFF;

                // 更新激光追踪器的目标位置
                LaserTracker_UpdateTargetPosition(g_camera_comm_system.latest_data.target.x,
                                                 g_camera_comm_system.latest_data.target.y);

                CAMERA_COMM_DEBUG("Received target position: (%d,%d)",
                    g_camera_comm_system.latest_data.target.x,
                    g_camera_comm_system.latest_data.target.y);

                // 更新统计信息
                g_camera_comm_system.stats.packets_received++;
                last_receive_time = System_GetTick();
            }
            break;

        case CMD_LASER_POSITION:
            if (data_len >= 4) {  // laser_x(2) + laser_y(2)
                // 解析激光位置数据
                g_camera_comm_system.latest_data.laser.x = (int16_t)(data[0] | (data[1] << 8));
                g_camera_comm_system.latest_data.laser.y = (int16_t)(data[2] | (data[3] << 8));

                // 设置激光数据有效性
                g_camera_comm_system.latest_data.laser.valid = true;

                // 检查是否同时有目标和激光数据
                if (g_camera_comm_system.latest_data.target.valid) {
                    g_camera_comm_system.latest_data.both_detected = true;
                    g_camera_comm_system.latest_data.frame_id++;
                    g_camera_comm_system.last_data_time = System_GetTick();
                    new_data_flag = true;
                }

                // 更新激光追踪器的激光位置
                LaserTracker_UpdateLaserPosition(g_camera_comm_system.latest_data.laser.x,
                                                g_camera_comm_system.latest_data.laser.y);

                CAMERA_COMM_DEBUG("Received laser position: (%d,%d)",
                    g_camera_comm_system.latest_data.laser.x,
                    g_camera_comm_system.latest_data.laser.y);

                // 更新统计信息
                g_camera_comm_system.stats.packets_received++;
                last_receive_time = System_GetTick();
            }
            break;

        case CMD_SYSTEM_STATUS:
            CAMERA_COMM_DEBUG("Received system status");
            break;

        default:
            CAMERA_COMM_DEBUG("Unknown command: %d", command);
            break;
    }
}

/**
 * @brief 处理摄像头数据接收 (在串口中断中调用)
 */
void CameraComm_IRQHandler(uint8_t data)
{
    static uint8_t state = 0;
    static uint8_t expected_length = 0;

    switch (state) {
        case 0:  // 等待第一个帧头
            if (data == CAMERA_PACKET_HEADER1) {
                rx_buffer[0] = data;
                state = 1;
            }
            break;

        case 1:  // 等待第二个帧头
            if (data == CAMERA_PACKET_HEADER2) {
                rx_buffer[1] = data;
                state = 2;
            } else {
                state = 0;  // 重新开始
            }
            break;

        case 2:  // 接收数据长度
            rx_buffer[2] = data;
            expected_length = data + 5;  // 数据长度 + 帧头(2) + 长度(1) + 命令(1) + 校验和(1)
            rx_index = 3;
            state = 3;
            break;

        case 3:  // 接收数据
            rx_buffer[rx_index++] = data;
            if (rx_index >= expected_length) {
                // 验证校验和
                uint8_t received_checksum = rx_buffer[rx_index - 1];
                uint8_t calculated_checksum = CameraComm_CalculateChecksum(&rx_buffer[2], rx_index - 3);
                
                if (received_checksum == calculated_checksum) {
                    packet_received = true;
                    last_receive_time = System_GetTick();
                    g_camera_comm_system.stats.packets_received++;
                    g_camera_comm_system.stats.packets_valid++;
                } else {
                    g_camera_comm_system.stats.packets_error++;
                    CAMERA_COMM_DEBUG("Checksum error: expected %d, got %d", calculated_checksum, received_checksum);
                }
                state = 0;  // 重新开始
            }
            break;

        default:
            state = 0;
            break;
    }

    // 防止缓冲区溢出
    if (rx_index >= CAMERA_MAX_PACKET_SIZE) {
        rx_index = 0;
        state = 0;
        g_camera_comm_system.stats.packets_error++;
    }
}

/**
 * @brief 摄像头通信主循环处理
 */
void CameraComm_Process(void)
{
    uint32_t current_time = System_GetTick();

    // 处理接收到的数据包
    if (packet_received) {
        packet_received = false;
        CameraComm_ParsePacket(rx_buffer, rx_index);
        rx_index = 0;
    }

    // 检查通信超时
    g_camera_comm_system.communication_ok = 
        (current_time - last_receive_time) < CAMERA_COMM_TIMEOUT_MS;
        
    // 更新最后接收时间
    g_camera_comm_system.stats.last_receive_time = last_receive_time;
}

/**
 * @brief 检查通信是否正常
 */
bool CameraComm_IsCommOK(void)
{
    return g_camera_comm_system.communication_ok;
}

/**
 * @brief 获取通信统计信息
 */
CameraCommStats_t* CameraComm_GetStats(void)
{
    return &g_camera_comm_system.stats;
}

/**
 * @brief 重置摄像头通信模块
 */
void CameraComm_Reset(void)
{
    memset(&g_camera_comm_system.stats, 0, sizeof(CameraCommStats_t));
    rx_index = 0;
    packet_received = false;
    new_data_flag = false;
    CAMERA_COMM_DEBUG("Camera communication reset");
}

/**
 * @brief 发送系统状态请求
 */
bool CameraComm_RequestStatus(void)
{
    return CameraComm_SendPacket(CMD_SYSTEM_STATUS, NULL, 0);
}

/**
 * @brief 发送PID参数到摄像头
 */
bool CameraComm_SendPIDParams(float kp_h, float ki_h, float kd_h,
                              float kp_v, float ki_v, float kd_v)
{
    uint8_t data[12];

    // 将浮点数转换为整数 (乘以100保留两位小数)
    uint16_t kp_h_int = (uint16_t)(kp_h * 100);
    uint16_t ki_h_int = (uint16_t)(ki_h * 100);
    uint16_t kd_h_int = (uint16_t)(kd_h * 100);
    uint16_t kp_v_int = (uint16_t)(kp_v * 100);
    uint16_t ki_v_int = (uint16_t)(ki_v * 100);
    uint16_t kd_v_int = (uint16_t)(kd_v * 100);

    // 打包数据
    data[0] = kp_h_int & 0xFF;
    data[1] = (kp_h_int >> 8) & 0xFF;
    data[2] = ki_h_int & 0xFF;
    data[3] = (ki_h_int >> 8) & 0xFF;
    data[4] = kd_h_int & 0xFF;
    data[5] = (kd_h_int >> 8) & 0xFF;
    data[6] = kp_v_int & 0xFF;
    data[7] = (kp_v_int >> 8) & 0xFF;
    data[8] = ki_v_int & 0xFF;
    data[9] = (ki_v_int >> 8) & 0xFF;
    data[10] = kd_v_int & 0xFF;
    data[11] = (kd_v_int >> 8) & 0xFF;

    return CameraComm_SendPacket(CMD_PID_PARAMS, data, 12);
}

/**
 * @brief USART1中断处理函数 - 摄像头通信
 * 注意：此函数需要在stm32f10x_it.c中声明为extern并调用
 */
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        uint8_t data = USART_ReceiveData(USART1);

        // 调用摄像头通信中断处理函数
        CameraComm_IRQHandler(data);

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
