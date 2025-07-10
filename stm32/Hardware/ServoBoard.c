/**
 * @file ServoBoard.c
 * @brief 舵机控制板通信模块实现
 * @version 1.0
 * @date 2025-07-09
 */

#include "ServoBoard.h"
#include "Delay.h"
#include "OLED.h"
#include <string.h>

/* 全局变量定义 */
ServoBoardSystem_t g_servo_board_system;

/* 私有变量 */
static uint8_t servo_board_rx_buffer[SERVO_MAX_PACKET_SIZE];
static uint8_t servo_board_rx_index = 0;
static bool packet_received = false;
static uint32_t last_receive_time = 0;
static uint32_t last_send_time = 0;

/* OLED调试显示控制 */
static bool oled_debug_enabled = false;
static uint32_t servo_command_count = 0;

/* 私有函数声明 */
static void ServoBoard_USART2_Init(void);
static void ServoBoard_SendByte(uint8_t data);
static bool ServoBoard_SendPacket(uint8_t command, uint8_t* data, uint8_t data_len);
//static bool ServoBoard_WaitResponse(uint8_t expected_cmd, uint32_t timeout_ms);
static void ServoBoard_ParsePacket(uint8_t* packet, uint8_t length);

/**
 * @brief 启用OLED调试显示
 */
void ServoBoard_EnableOLEDDebug(bool enable)
{
    oled_debug_enabled = enable;
}

/**
 * @brief 初始化舵机控制板通信模块
 */
bool ServoBoard_Init(void)
{
    // 清零系统状态
    memset(&g_servo_board_system, 0, sizeof(ServoBoardSystem_t));

    // 初始化USART2用于舵机控制板通信
    ServoBoard_USART2_Init();

    // 设置初始状态
    g_servo_board_system.state = SERVO_BOARD_STATE_IDLE;
    g_servo_board_system.initialized = true;
    g_servo_board_system.servo_count = 2; // 默认2个舵机
    
    // 初始化舵机位置信息
    for (int i = 0; i < SERVO_MAX_SERVOS; i++) {
        g_servo_board_system.servo_positions[i].id = i + 1;
        g_servo_board_system.servo_positions[i].position = SERVO_POSITION_CENTER;
        g_servo_board_system.servo_positions[i].valid = false;
    }
    
    // 设置当前位置为中心
    g_servo_board_system.current_h_position = SERVO_POSITION_CENTER;
    g_servo_board_system.current_v_position = SERVO_POSITION_CENTER;
    
    SERVO_BOARD_DEBUG("Servo Board initialized");
    return true;
}

/**
 * @brief 反初始化舵机控制板通信模块
 */
void ServoBoard_DeInit(void)
{
    g_servo_board_system.initialized = false;
    g_servo_board_system.state = SERVO_BOARD_STATE_IDLE;
    SERVO_BOARD_DEBUG("Servo Board deinitialized");
}

/**
 * @brief 初始化USART2用于舵机控制板通信
 */
static void ServoBoard_USART2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 使能GPIOA和USART2时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    // 配置PA2 (TX) 为推挽复用输出
    GPIO_InitStructure.GPIO_Pin = SERVO_UART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SERVO_UART_GPIO_PORT, &GPIO_InitStructure);

    // 配置PA3 (RX) 为浮空输入
    GPIO_InitStructure.GPIO_Pin = SERVO_UART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SERVO_UART_GPIO_PORT, &GPIO_InitStructure);

    // 配置USART参数
    USART_InitStructure.USART_BaudRate = SERVO_UART_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(SERVO_UART, &USART_InitStructure);

    // 配置NVIC中断
    NVIC_InitStructure.NVIC_IRQChannel = SERVO_UART_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 使能接收中断
    USART_ITConfig(SERVO_UART, USART_IT_RXNE, ENABLE);

    // 使能USART
    USART_Cmd(SERVO_UART, ENABLE);
}

/**
 * @brief 发送单个字节到舵机控制板
 */
static void ServoBoard_SendByte(uint8_t data)
{
    while (USART_GetFlagStatus(SERVO_UART, USART_FLAG_TXE) == RESET);
    USART_SendData(SERVO_UART, data);
}

/**
 * @brief 发送数据包到舵机控制板
 */
static bool ServoBoard_SendPacket(uint8_t command, uint8_t* data, uint8_t data_len)
{
    if (data_len > SERVO_MAX_PACKET_SIZE - 4) {
        SERVO_BOARD_DEBUG("Data length too large: %d", data_len);
        return false;
    }

    // 构造数据包
    uint8_t packet[SERVO_MAX_PACKET_SIZE];
    uint8_t packet_len = 0;

    packet[packet_len++] = SERVO_BOARD_HEADER1;     // 帧头1
    packet[packet_len++] = SERVO_BOARD_HEADER2;     // 帧头2
    packet[packet_len++] = data_len + 2;            // 数据长度 (参数个数N + 指令1字节 + 长度字段1字节)
    packet[packet_len++] = command;                 // 命令

    // 添加参数数据
    if (data && data_len > 0) {
        memcpy(&packet[packet_len], data, data_len);
        packet_len += data_len;
    }

    // 发送数据包
    for (uint8_t i = 0; i < packet_len; i++) {
        ServoBoard_SendByte(packet[i]);
    }

    last_send_time = System_GetTick();
    g_servo_board_system.state = SERVO_BOARD_STATE_BUSY;

    SERVO_BOARD_DEBUG("Sent packet: cmd=%d, len=%d", command, data_len);
    return true;
}

/**
 * @brief 控制单个舵机移动
 */
bool ServoBoard_MoveServo(uint8_t id, uint16_t position, uint16_t time)
{
    if (!g_servo_board_system.initialized) {
        SERVO_BOARD_DEBUG("ServoBoard not initialized!");
        return false;
    }

    // 限制参数范围
    if (position > SERVO_POSITION_MAX) position = SERVO_POSITION_MAX;
    if (time > 30000) time = 30000;

    SERVO_BOARD_DEBUG("Moving servo %d to position %d in %dms", id, position, time);

    // 构造数据包
    uint8_t data[6];
    data[0] = 1;                        // 舵机个数
    data[1] = time & 0xFF;              // 时间低字节
    data[2] = (time >> 8) & 0xFF;       // 时间高字节
    data[3] = id;                       // 舵机ID
    data[4] = position & 0xFF;          // 位置低字节
    data[5] = (position >> 8) & 0xFF;   // 位置高字节

    bool result = ServoBoard_SendPacket(CMD_SERVO_MOVE, data, 6);

    if (result) {
        g_servo_board_system.stats.packets_sent++;
        
        // 更新当前位置记录
        if (id == SERVO_ID_HORIZONTAL) {
            g_servo_board_system.current_h_position = position;
        } else if (id == SERVO_ID_VERTICAL) {
            g_servo_board_system.current_v_position = position;
        }
        
        SERVO_BOARD_DEBUG("Servo command sent successfully");
    } else {
        g_servo_board_system.stats.packets_error++;
        SERVO_BOARD_DEBUG("Failed to send servo command");
    }

    return result;
}

/**
 * @brief 控制水平和垂直舵机移动
 */
bool ServoBoard_MoveHV(uint16_t h_position, uint16_t v_position, uint16_t time)
{
    if (!g_servo_board_system.initialized) {
        return false;
    }

    // 限制参数范围
    if (h_position > SERVO_POSITION_MAX) h_position = SERVO_POSITION_MAX;
    if (v_position > SERVO_POSITION_MAX) v_position = SERVO_POSITION_MAX;
    if (time > 30000) time = 30000;

    // 构造数据包 - 控制两个舵机
    uint8_t data[9];
    data[0] = 2;                            // 舵机个数
    data[1] = time & 0xFF;                  // 时间低字节
    data[2] = (time >> 8) & 0xFF;           // 时间高字节
    
    // 水平舵机参数
    data[3] = SERVO_ID_HORIZONTAL;          // 水平舵机ID
    data[4] = h_position & 0xFF;            // 位置低字节
    data[5] = (h_position >> 8) & 0xFF;     // 位置高字节
    
    // 垂直舵机参数
    data[6] = SERVO_ID_VERTICAL;            // 垂直舵机ID
    data[7] = v_position & 0xFF;            // 位置低字节
    data[8] = (v_position >> 8) & 0xFF;     // 位置高字节

    bool result = ServoBoard_SendPacket(CMD_SERVO_MOVE, data, 9);

    if (result) {
        g_servo_board_system.stats.packets_sent++;
        g_servo_board_system.current_h_position = h_position;
        g_servo_board_system.current_v_position = v_position;
        servo_command_count++;

        // OLED调试显示
        if (oled_debug_enabled) {
            // 显示舵机命令发送状态
            OLED_ShowString(1, 1, "SERVO CMD SENT");
            OLED_ShowString(2, 1, "H:");
            OLED_ShowNum(2, 3, h_position, 4);
            OLED_ShowString(2, 8, "V:");
            OLED_ShowNum(2, 10, v_position, 4);
            OLED_ShowString(3, 1, "Time:");
            OLED_ShowNum(3, 6, time, 4);
            OLED_ShowString(3, 11, "ms");
            OLED_ShowString(4, 1, "Count:");
            OLED_ShowNum(4, 7, servo_command_count, 5);
        }

        SERVO_BOARD_DEBUG("Move HV: H=%d, V=%d, T=%dms", h_position, v_position, time);
    } else {
        g_servo_board_system.stats.packets_error++;
    }

    return result;
}

/**
 * @brief 根据PID输出控制舵机
 */
bool ServoBoard_ControlByPID(float pid_output_h, float pid_output_v)
{
    // 将PID输出转换为舵机位置偏移
    int16_t h_offset = PID_OUTPUT_TO_POSITION_OFFSET(pid_output_h);
    int16_t v_offset = PID_OUTPUT_TO_POSITION_OFFSET(pid_output_v);
    
    // 计算新的舵机位置
    int16_t new_h_position = g_servo_board_system.current_h_position + h_offset;
    int16_t new_v_position = g_servo_board_system.current_v_position + v_offset;
    
    // 限制位置范围
    if (new_h_position < SERVO_POSITION_MIN) new_h_position = SERVO_POSITION_MIN;
    if (new_h_position > SERVO_POSITION_MAX) new_h_position = SERVO_POSITION_MAX;
    if (new_v_position < SERVO_POSITION_MIN) new_v_position = SERVO_POSITION_MIN;
    if (new_v_position > SERVO_POSITION_MAX) new_v_position = SERVO_POSITION_MAX;
    
    // 控制舵机移动
    return ServoBoard_MoveHV(new_h_position, new_v_position, 100); // 100ms快速响应
}

/**
 * @brief 舵机回到中心位置
 */
bool ServoBoard_ReturnToCenter(void)
{
    return ServoBoard_MoveHV(SERVO_POSITION_CENTER, SERVO_POSITION_CENTER, 1000);
}

/**
 * @brief 停止所有舵机运动
 */
bool ServoBoard_StopAll(void)
{
    // 发送当前位置命令，时间设为0，实现立即停止
    return ServoBoard_MoveHV(g_servo_board_system.current_h_position,
                            g_servo_board_system.current_v_position, 0);
}

/**
 * @brief 处理舵机控制板数据接收 (在串口中断中调用)
 */
void ServoBoard_IRQHandler(uint8_t data)
{
    static uint8_t servo_board_state = 0;
    static uint8_t expected_length = 0;

    switch (servo_board_state) {
        case 0:  // 等待第一个帧头
            if (data == SERVO_BOARD_HEADER1) {
                servo_board_rx_buffer[0] = data;
                servo_board_state = 1;
            }
            break;

        case 1:  // 等待第二个帧头
            if (data == SERVO_BOARD_HEADER2) {
                servo_board_rx_buffer[1] = data;
                servo_board_state = 2;
            } else {
                servo_board_state = 0;  // 重新开始
            }
            break;

        case 2:  // 接收数据长度
            servo_board_rx_buffer[2] = data;
            expected_length = data + 2;  // 加上帧头长度
            servo_board_rx_index = 3;
            servo_board_state = 3;
            break;

        case 3:  // 接收数据
            servo_board_rx_buffer[servo_board_rx_index++] = data;
            if (servo_board_rx_index >= expected_length) {
                packet_received = true;
                last_receive_time = System_GetTick();
                servo_board_state = 0;  // 重新开始
            }
            break;

        default:
            servo_board_state = 0;
            break;
    }

    // 防止缓冲区溢出
    if (servo_board_rx_index >= SERVO_MAX_PACKET_SIZE) {
        servo_board_rx_index = 0;
        servo_board_state = 0;
    }
}

/**
 * @brief 解析接收到的数据包
 */
static void ServoBoard_ParsePacket(uint8_t* packet, uint8_t length)
{
    if (!packet || length < 4) return;

    uint8_t command = packet[3];
    uint8_t data_len = packet[2] - 2;  // 减去命令和长度字节
    uint8_t* data = &packet[4];

    switch (command) {
        case CMD_MULT_SERVO_POS_READ:
            if (data_len >= 1) {
                uint8_t servo_count = data[0];
                uint8_t data_index = 1;

                for (uint8_t i = 0; i < servo_count && data_index + 2 < data_len; i++) {
                    uint8_t servo_id = data[data_index++];
                    uint16_t position = data[data_index] | (data[data_index + 1] << 8);
                    data_index += 2;

                    // 更新舵机位置信息
                    for (uint8_t j = 0; j < SERVO_MAX_SERVOS; j++) {
                        if (g_servo_board_system.servo_positions[j].id == servo_id) {
                            g_servo_board_system.servo_positions[j].position = position;
                            g_servo_board_system.servo_positions[j].valid = true;
                            g_servo_board_system.servo_positions[j].timestamp = System_GetTick();
                            break;
                        }
                    }
                }
            }
            break;

        case CMD_GET_BATTERY_VOLTAGE:
            if (data_len >= 2) {
                g_servo_board_system.stats.last_battery_voltage =
                    data[0] | (data[1] << 8);
                g_servo_board_system.stats.last_update_time = System_GetTick();
            }
            break;

        case CMD_ACTION_GROUP_RUN:
        case CMD_ACTION_GROUP_STOP:
        case CMD_ACTION_GROUP_COMPLETE:
            // 动作组状态更新
            SERVO_BOARD_DEBUG("Action group event: cmd=%d", command);
            break;

        default:
            SERVO_BOARD_DEBUG("Unknown command response: %d", command);
            break;
    }
}

/**
 * @brief 舵机控制板主循环处理
 */
void ServoBoard_Process(void)
{
    uint32_t current_time = System_GetTick();

    // 处理接收到的数据包
    if (packet_received) {
        packet_received = false;
        ServoBoard_ParsePacket(servo_board_rx_buffer, servo_board_rx_index);
        servo_board_rx_index = 0;
        g_servo_board_system.stats.packets_received++;
    }

    // 检查通信超时
    if (g_servo_board_system.state == SERVO_BOARD_STATE_BUSY) {
        if ((current_time - last_send_time) > SERVO_COMM_TIMEOUT_MS) {
            g_servo_board_system.state = SERVO_BOARD_STATE_TIMEOUT;
            g_servo_board_system.stats.timeouts++;
        }
    }

    // 更新通信状态
    g_servo_board_system.communication_ok =
        (current_time - last_receive_time) < (SERVO_COMM_TIMEOUT_MS * 2);
}

/**
 * @brief 获取舵机控制板状态
 */
ServoBoardState_t ServoBoard_GetState(void)
{
    return g_servo_board_system.state;
}

/**
 * @brief 获取舵机控制板统计信息
 */
ServoBoardStats_t* ServoBoard_GetStats(void)
{
    return &g_servo_board_system.stats;
}

/**
 * @brief 检查通信是否正常
 */
bool ServoBoard_IsCommOK(void)
{
    return g_servo_board_system.communication_ok;
}

/**
 * @brief 重置舵机控制板模块
 */
void ServoBoard_Reset(void)
{
    g_servo_board_system.state = SERVO_BOARD_STATE_IDLE;
    g_servo_board_system.communication_ok = false;
    memset(&g_servo_board_system.stats, 0, sizeof(ServoBoardStats_t));

    // 重置接收状态
    servo_board_rx_index = 0;
    packet_received = false;

    SERVO_BOARD_DEBUG("Servo Board reset");
}

/**
 * @brief 读取单个舵机位置
 */
bool ServoBoard_ReadServoPosition(uint8_t id, uint16_t* position)
{
    if (!position) return false;

    uint8_t ids[1] = {id};
    uint8_t data[2];
    data[0] = 1;        // 舵机个数
    data[1] = id;       // 舵机ID

    bool result = ServoBoard_SendPacket(CMD_MULT_SERVO_POS_READ, data, 2);

    if (result) {
        // 等待响应 (简化处理，实际应用中可以使用更复杂的响应机制)
        Delay_ms(50);

        // 从缓存中查找位置信息
        for (uint8_t i = 0; i < SERVO_MAX_SERVOS; i++) {
            if (g_servo_board_system.servo_positions[i].id == id &&
                g_servo_board_system.servo_positions[i].valid) {
                *position = g_servo_board_system.servo_positions[i].position;
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief 获取控制板电池电压
 */
bool ServoBoard_GetBatteryVoltage(uint16_t* voltage)
{
    if (!g_servo_board_system.initialized || !voltage) {
        return false;
    }

    bool result = ServoBoard_SendPacket(CMD_GET_BATTERY_VOLTAGE, NULL, 0);

    if (result) {
        // 等待响应
        Delay_ms(50);
        *voltage = g_servo_board_system.stats.last_battery_voltage;
        g_servo_board_system.stats.packets_sent++;
        SERVO_BOARD_DEBUG("Battery voltage: %dmV", *voltage);
        return true;
    } else {
        g_servo_board_system.stats.packets_error++;
    }

    return false;
}

/**
 * @brief USART2中断处理函数 - 舵机控制板通信
 * 注意：此函数需要在stm32f10x_it.c中声明为extern并调用
 */
void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        uint8_t data = USART_ReceiveData(USART2);

        // 调用舵机控制板中断处理函数
        ServoBoard_IRQHandler(data);

        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}
