/**
 * @file ControlBoard.c
 * @brief 舵机控制板通信协议模块实现
 * @version 1.0
 * @date 2024-01-01
 */

#include "ControlBoard.h"
#include <string.h>
#include "stm32f10x.h"

/* 全局变量定义 */
ControlBoardSystem_t g_control_board_system = {0};

/* 私有变量 */
static uint8_t rx_buffer[CONTROL_BOARD_MAX_PACKET_SIZE];
static uint8_t rx_index = 0;
static bool packet_received = false;
static uint32_t last_receive_time = 0;
static uint32_t last_send_time = 0;

/* 私有函数声明 */
static void ControlBoard_USART2_Init(void);
static void ControlBoard_SendByte(uint8_t data);
static bool ControlBoard_SendPacket(uint8_t command, uint8_t* data, uint8_t data_len);
static bool ControlBoard_WaitResponse(uint8_t expected_cmd, uint32_t timeout_ms);
static void ControlBoard_ParsePacket(uint8_t* packet, uint8_t length);
static uint32_t ControlBoard_GetTick(void);

/**
 * @brief 初始化控制板通信模块
 */
bool ControlBoard_Init(void)
{
    // 清零系统状态
    memset(&g_control_board_system, 0, sizeof(ControlBoardSystem_t));

    // 初始化USART2用于控制板通信 (9600波特率)
    ControlBoard_USART2_Init();

    // 设置初始状态
    g_control_board_system.state = CONTROL_BOARD_STATE_IDLE;
    g_control_board_system.initialized = true;
    g_control_board_system.servo_count = 2; // 默认2个舵机
    
    // 初始化舵机位置信息
    for (int i = 0; i < CONTROL_BOARD_MAX_SERVOS; i++) {
        g_control_board_system.servo_positions[i].id = i + 1;
        g_control_board_system.servo_positions[i].position = 500; // 中心位置
        g_control_board_system.servo_positions[i].valid = false;
    }
    
    CONTROL_BOARD_DEBUG("Control Board initialized");
    return true;
}

/**
 * @brief 反初始化控制板通信模块
 */
void ControlBoard_DeInit(void)
{
    g_control_board_system.initialized = false;
    g_control_board_system.state = CONTROL_BOARD_STATE_IDLE;
    CONTROL_BOARD_DEBUG("Control Board deinitialized");
}

/**
 * @brief 初始化USART2用于控制板通信
 */
static void ControlBoard_USART2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

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

    // 配置USART参数
    USART_InitStructure.USART_BaudRate = CONTROL_BOARD_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    // 使能USART
    USART_Cmd(USART2, ENABLE);
}

/**
 * @brief 发送单个字节到控制板
 */
static void ControlBoard_SendByte(uint8_t data)
{
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    USART_SendData(USART2, data);
}

/**
 * @brief 控制单个舵机移动
 */
bool ControlBoard_MoveServo(uint8_t id, uint16_t position, uint16_t time)
{
    if (!g_control_board_system.initialized) {
        return false;
    }
    
    // 限制参数范围
    if (position > 1000) position = 1000;
    if (time > 30000) time = 30000;
    
    // 构造数据包
    uint8_t data[6];
    data[0] = 1;                    // 舵机个数
    data[1] = time & 0xFF;          // 时间低字节
    data[2] = (time >> 8) & 0xFF;   // 时间高字节
    data[3] = id;                   // 舵机ID
    data[4] = position & 0xFF;      // 位置低字节
    data[5] = (position >> 8) & 0xFF; // 位置高字节
    
    bool result = ControlBoard_SendPacket(CMD_SERVO_MOVE, data, 6);
    
    if (result) {
        g_control_board_system.stats.packets_sent++;
        CONTROL_BOARD_DEBUG("Move servo %d to %d in %dms", id, position, time);
    } else {
        g_control_board_system.stats.packets_error++;
    }
    
    return result;
}

/**
 * @brief 控制多个舵机移动
 */
bool ControlBoard_MoveMultiServos(ServoMoveParam_t* servos, uint8_t count)
{
    if (!g_control_board_system.initialized || !servos || count == 0 || count > CONTROL_BOARD_MAX_SERVOS) {
        return false;
    }
    
    // 构造数据包
    uint8_t data[CONTROL_BOARD_MAX_PACKET_SIZE - 4];
    uint8_t data_len = 0;
    
    data[data_len++] = count;                           // 舵机个数
    data[data_len++] = servos[0].time & 0xFF;           // 时间低字节 (使用第一个舵机的时间)
    data[data_len++] = (servos[0].time >> 8) & 0xFF;    // 时间高字节
    
    // 添加每个舵机的参数
    for (uint8_t i = 0; i < count; i++) {
        if (data_len + 3 > sizeof(data)) break;
        
        data[data_len++] = servos[i].id;                        // 舵机ID
        data[data_len++] = servos[i].position & 0xFF;           // 位置低字节
        data[data_len++] = (servos[i].position >> 8) & 0xFF;    // 位置高字节
    }
    
    bool result = ControlBoard_SendPacket(CMD_SERVO_MOVE, data, data_len);
    
    if (result) {
        g_control_board_system.stats.packets_sent++;
        CONTROL_BOARD_DEBUG("Move %d servos", count);
    } else {
        g_control_board_system.stats.packets_error++;
    }
    
    return result;
}

/**
 * @brief 读取多个舵机位置
 */
bool ControlBoard_ReadMultiServoPositions(uint8_t* ids, uint8_t count, 
                                         ServoPositionInfo_t* positions)
{
    if (!g_control_board_system.initialized || !ids || !positions || count == 0) {
        return false;
    }
    
    // 构造数据包
    uint8_t data[CONTROL_BOARD_MAX_SERVOS + 1];
    data[0] = count;  // 舵机个数
    
    for (uint8_t i = 0; i < count; i++) {
        data[i + 1] = ids[i];  // 舵机ID
    }
    
    bool result = ControlBoard_SendPacket(CMD_MULT_SERVO_POS_READ, data, count + 1);
    
    if (result) {
        // 等待响应
        if (ControlBoard_WaitResponse(CMD_MULT_SERVO_POS_READ, CONTROL_BOARD_TIMEOUT_MS)) {
            g_control_board_system.stats.packets_sent++;
            g_control_board_system.stats.packets_received++;
            CONTROL_BOARD_DEBUG("Read %d servo positions", count);
            return true;
        } else {
            g_control_board_system.stats.timeouts++;
        }
    } else {
        g_control_board_system.stats.packets_error++;
    }
    
    return false;
}

/**
 * @brief 读取单个舵机位置
 */
bool ControlBoard_ReadServoPosition(uint8_t id, uint16_t* position)
{
    if (!position) return false;
    
    uint8_t ids[1] = {id};
    ServoPositionInfo_t pos_info[1];
    
    if (ControlBoard_ReadMultiServoPositions(ids, 1, pos_info)) {
        *position = pos_info[0].position;
        return pos_info[0].valid;
    }
    
    return false;
}

/**
 * @brief 控制多个舵机卸力
 */
bool ControlBoard_UnloadServos(uint8_t* ids, uint8_t count)
{
    if (!g_control_board_system.initialized || !ids || count == 0) {
        return false;
    }
    
    // 构造数据包
    uint8_t data[CONTROL_BOARD_MAX_SERVOS + 1];
    data[0] = count;  // 舵机个数
    
    for (uint8_t i = 0; i < count; i++) {
        data[i + 1] = ids[i];  // 舵机ID
    }
    
    bool result = ControlBoard_SendPacket(CMD_MULT_SERVO_UNLOAD, data, count + 1);
    
    if (result) {
        g_control_board_system.stats.packets_sent++;
        CONTROL_BOARD_DEBUG("Unload %d servos", count);
    } else {
        g_control_board_system.stats.packets_error++;
    }
    
    return result;
}

/**
 * @brief 获取控制板电池电压
 */
bool ControlBoard_GetBatteryVoltage(uint16_t* voltage)
{
    if (!g_control_board_system.initialized || !voltage) {
        return false;
    }
    
    bool result = ControlBoard_SendPacket(CMD_GET_BATTERY_VOLTAGE, NULL, 0);
    
    if (result) {
        // 等待响应
        if (ControlBoard_WaitResponse(CMD_GET_BATTERY_VOLTAGE, CONTROL_BOARD_TIMEOUT_MS)) {
            *voltage = g_control_board_system.stats.last_battery_voltage;
            g_control_board_system.stats.packets_sent++;
            g_control_board_system.stats.packets_received++;
            CONTROL_BOARD_DEBUG("Battery voltage: %dmV", *voltage);
            return true;
        } else {
            g_control_board_system.stats.timeouts++;
        }
    } else {
        g_control_board_system.stats.packets_error++;
    }
    
    return false;
}

/**
 * @brief 运行动作组
 */
bool ControlBoard_RunActionGroup(uint8_t group_id, uint16_t times)
{
    if (!g_control_board_system.initialized) {
        return false;
    }
    
    uint8_t data[3];
    data[0] = group_id;             // 动作组ID
    data[1] = times & 0xFF;         // 次数低字节
    data[2] = (times >> 8) & 0xFF;  // 次数高字节
    
    bool result = ControlBoard_SendPacket(CMD_ACTION_GROUP_RUN, data, 3);
    
    if (result) {
        g_control_board_system.stats.packets_sent++;
        CONTROL_BOARD_DEBUG("Run action group %d, %d times", group_id, times);
    } else {
        g_control_board_system.stats.packets_error++;
    }
    
    return result;
}

/**
 * @brief 停止动作组
 */
bool ControlBoard_StopActionGroup(void)
{
    if (!g_control_board_system.initialized) {
        return false;
    }
    
    bool result = ControlBoard_SendPacket(CMD_ACTION_GROUP_STOP, NULL, 0);
    
    if (result) {
        g_control_board_system.stats.packets_sent++;
        CONTROL_BOARD_DEBUG("Stop action group");
    } else {
        g_control_board_system.stats.packets_error++;
    }
    
    return result;
}

/**
 * @brief 设置动作组速度
 */
bool ControlBoard_SetActionGroupSpeed(uint8_t group_id, uint16_t speed_percent)
{
    if (!g_control_board_system.initialized) {
        return false;
    }
    
    uint8_t data[3];
    data[0] = group_id;                         // 动作组ID
    data[1] = speed_percent & 0xFF;             // 速度低字节
    data[2] = (speed_percent >> 8) & 0xFF;      // 速度高字节
    
    bool result = ControlBoard_SendPacket(CMD_ACTION_GROUP_SPEED, data, 3);
    
    if (result) {
        g_control_board_system.stats.packets_sent++;
        CONTROL_BOARD_DEBUG("Set action group %d speed to %d%%", group_id, speed_percent);
    } else {
        g_control_board_system.stats.packets_error++;
    }
    
    return result;
}

/**
 * @brief 发送数据包到控制板
 */
static bool ControlBoard_SendPacket(uint8_t command, uint8_t* data, uint8_t data_len)
{
    if (data_len > CONTROL_BOARD_MAX_PACKET_SIZE - 4) {
        return false;
    }

    // 构造数据包
    uint8_t packet[CONTROL_BOARD_MAX_PACKET_SIZE];
    uint8_t packet_len = 0;

    packet[packet_len++] = CONTROL_BOARD_HEADER1;   // 帧头1
    packet[packet_len++] = CONTROL_BOARD_HEADER2;   // 帧头2
    packet[packet_len++] = data_len + 2;            // 数据长度 (命令+参数+长度本身)
    packet[packet_len++] = command;                 // 命令

    // 添加参数数据
    if (data && data_len > 0) {
        memcpy(&packet[packet_len], data, data_len);
        packet_len += data_len;
    }

    // 发送数据包
    for (uint8_t i = 0; i < packet_len; i++) {
        ControlBoard_SendByte(packet[i]);
    }

    last_send_time = ControlBoard_GetTick();
    g_control_board_system.state = CONTROL_BOARD_STATE_BUSY;

    return true;
}

/**
 * @brief 等待控制板响应
 */
static bool ControlBoard_WaitResponse(uint8_t expected_cmd, uint32_t timeout_ms)
{
    uint32_t start_time = ControlBoard_GetTick();

    while ((ControlBoard_GetTick() - start_time) < timeout_ms) {
        if (packet_received) {
            packet_received = false;

            // 检查是否是期望的响应
            if (rx_buffer[3] == expected_cmd) {
                ControlBoard_ParsePacket(rx_buffer, rx_index);
                rx_index = 0;
                g_control_board_system.state = CONTROL_BOARD_STATE_IDLE;
                return true;
            }
        }

        // 简单延时 (实际应用中可以使用更精确的延时)
        for (volatile int i = 0; i < 1000; i++);
    }

    g_control_board_system.state = CONTROL_BOARD_STATE_TIMEOUT;
    return false;
}

/**
 * @brief 解析接收到的数据包
 */
static void ControlBoard_ParsePacket(uint8_t* packet, uint8_t length)
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
                    for (uint8_t j = 0; j < CONTROL_BOARD_MAX_SERVOS; j++) {
                        if (g_control_board_system.servo_positions[j].id == servo_id) {
                            g_control_board_system.servo_positions[j].position = position;
                            g_control_board_system.servo_positions[j].valid = true;
                            break;
                        }
                    }
                }
            }
            break;

        case CMD_GET_BATTERY_VOLTAGE:
            if (data_len >= 2) {
                g_control_board_system.stats.last_battery_voltage =
                    data[0] | (data[1] << 8);
                g_control_board_system.stats.last_update_time = ControlBoard_GetTick();
            }
            break;

        case CMD_ACTION_GROUP_RUN:
        case CMD_ACTION_GROUP_STOP:
        case CMD_ACTION_GROUP_COMPLETE:
            // 动作组状态更新
            CONTROL_BOARD_DEBUG("Action group event: cmd=%d", command);
            break;

        default:
            CONTROL_BOARD_DEBUG("Unknown command response: %d", command);
            break;
    }
}

/**
 * @brief 处理控制板数据接收 (在串口中断中调用)
 */
void ControlBoard_IRQHandler(uint8_t data)
{
    static uint8_t state = 0;
    static uint8_t expected_length = 0;

    switch (state) {
        case 0:  // 等待第一个帧头
            if (data == CONTROL_BOARD_HEADER1) {
                rx_buffer[0] = data;
                state = 1;
            }
            break;

        case 1:  // 等待第二个帧头
            if (data == CONTROL_BOARD_HEADER2) {
                rx_buffer[1] = data;
                state = 2;
            } else {
                state = 0;  // 重新开始
            }
            break;

        case 2:  // 接收数据长度
            rx_buffer[2] = data;
            expected_length = data + 2;  // 加上帧头长度
            rx_index = 3;
            state = 3;
            break;

        case 3:  // 接收数据
            rx_buffer[rx_index++] = data;
            if (rx_index >= expected_length) {
                packet_received = true;
                last_receive_time = ControlBoard_GetTick();
                state = 0;  // 重新开始
            }
            break;

        default:
            state = 0;
            break;
    }

    // 防止缓冲区溢出
    if (rx_index >= CONTROL_BOARD_MAX_PACKET_SIZE) {
        rx_index = 0;
        state = 0;
    }
}

/**
 * @brief 控制板主循环处理
 */
void ControlBoard_Process(void)
{
    uint32_t current_time = ControlBoard_GetTick();

    // 检查通信超时
    if (g_control_board_system.state == CONTROL_BOARD_STATE_BUSY) {
        if ((current_time - last_send_time) > CONTROL_BOARD_TIMEOUT_MS) {
            g_control_board_system.state = CONTROL_BOARD_STATE_TIMEOUT;
            g_control_board_system.stats.timeouts++;
        }
    }

    // 更新通信状态
    g_control_board_system.communication_ok =
        (current_time - last_receive_time) < (CONTROL_BOARD_TIMEOUT_MS * 2);
}

/**
 * @brief 获取控制板状态
 */
ControlBoardState_t ControlBoard_GetState(void)
{
    return g_control_board_system.state;
}

/**
 * @brief 获取控制板统计信息
 */
ControlBoardStats_t* ControlBoard_GetStats(void)
{
    return &g_control_board_system.stats;
}

/**
 * @brief 检查通信是否正常
 */
bool ControlBoard_IsCommOK(void)
{
    return g_control_board_system.communication_ok;
}

/**
 * @brief 重置控制板模块
 */
void ControlBoard_Reset(void)
{
    g_control_board_system.state = CONTROL_BOARD_STATE_IDLE;
    g_control_board_system.communication_ok = false;
    memset(&g_control_board_system.stats, 0, sizeof(ControlBoardStats_t));

    // 重置接收状态
    rx_index = 0;
    packet_received = false;

    CONTROL_BOARD_DEBUG("Control Board reset");
}

/**
 * @brief 获取系统时钟 (需要根据实际系统实现)
 */
static uint32_t ControlBoard_GetTick(void)
{
    // 这里需要根据实际系统的时钟函数实现
    // 例如: return HAL_GetTick(); 或者使用SysTick计数器
    static uint32_t tick_counter = 0;
    return ++tick_counter;  // 临时实现
}
