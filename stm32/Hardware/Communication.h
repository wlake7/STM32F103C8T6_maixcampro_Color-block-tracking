/**
 * @file Communication.h
 * @brief STM32端通信协议模块头文件
 * @author AI Assistant
 * @date 2025-07-06
 * 
 * 实现与MaixCam的串口通信协议，支持数据包解析、校验和验证、命令处理等功能
 */

#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "stm32f10x.h"
#include <stdint.h>
#include <stdbool.h>

/* 协议定义 */
#define COMM_HEADER_SIZE        2       // 帧头长度
#define COMM_HEADER_BYTE1       0xAA    // 帧头第一字节
#define COMM_HEADER_BYTE2       0x55    // 帧头第二字节
#define COMM_MAX_DATA_SIZE      64      // 最大数据长度
#define COMM_MAX_PACKET_SIZE    (COMM_HEADER_SIZE + 1 + 1 + COMM_MAX_DATA_SIZE + 1) // 最大包长度

/* 命令定义 */
typedef enum {
    CMD_TARGET_POSITION = 0x01,     // 目标位置数据
    CMD_LASER_POSITION  = 0x02,     // 激光位置数据
    CMD_PID_PARAMS      = 0x03,     // PID参数
    CMD_SYSTEM_STATUS   = 0x04,     // 系统状态
    CMD_CALIBRATION     = 0x05,     // 标定数据
    CMD_HEARTBEAT       = 0x06,     // 心跳包
    CMD_ERROR           = 0xFF      // 错误命令
} CommCommand_t;

/* 通信状态 */
typedef enum {
    COMM_STATE_IDLE = 0,            // 空闲状态
    COMM_STATE_RECEIVING,           // 接收中
    COMM_STATE_PROCESSING,          // 处理中
    COMM_STATE_ERROR                // 错误状态
} CommState_t;

/* 数据包结构 */
typedef struct {
    uint8_t header[COMM_HEADER_SIZE];   // 帧头 [0xAA, 0x55]
    uint8_t length;                     // 数据长度
    uint8_t command;                    // 命令字
    uint8_t data[COMM_MAX_DATA_SIZE];   // 数据
    uint8_t checksum;                   // 校验和
} CommPacket_t;

/* 位置数据结构 */
typedef struct {
    uint16_t x;                         // X坐标
    uint16_t y;                         // Y坐标
    uint16_t confidence;                // 置信度
    uint16_t timestamp;                 // 时间戳
} PositionData_t;

/* PID参数结构 */
typedef struct {
    uint16_t kp_h;                      // 水平Kp (乘以100)
    uint16_t ki_h;                      // 水平Ki (乘以100)
    uint16_t kd_h;                      // 水平Kd (乘以100)
    uint16_t kp_v;                      // 垂直Kp (乘以100)
    uint16_t ki_v;                      // 垂直Ki (乘以100)
    uint16_t kd_v;                      // 垂直Kd (乘以100)
} PIDParams_t;

/* 系统状态结构 */
typedef struct {
    uint8_t system_ready;               // 系统就绪标志
    uint8_t servo_status;               // 舵机状态
    uint8_t tracking_mode;              // 追踪模式
    uint8_t error_code;                 // 错误代码
} SystemStatus_t;

/* 通信统计信息 */
typedef struct {
    uint32_t packets_received;          // 接收包数
    uint32_t packets_sent;              // 发送包数
    uint32_t checksum_errors;           // 校验错误数
    uint32_t format_errors;             // 格式错误数
    uint32_t last_heartbeat;            // 最后心跳时间
} CommStats_t;

/* 回调函数类型定义 */
typedef void (*CommCallback_t)(CommCommand_t cmd, uint8_t* data, uint8_t length);

/* 全局变量声明 */
extern CommState_t g_comm_state;
extern CommStats_t g_comm_stats;
extern CommCallback_t g_comm_callback;

/* 函数声明 */

/**
 * @brief 初始化通信模块
 * @param baudrate 波特率
 * @param callback 数据处理回调函数
 * @return 初始化结果
 */
bool Communication_Init(uint32_t baudrate, CommCallback_t callback);

/**
 * @brief 发送数据包
 * @param cmd 命令字
 * @param data 数据指针
 * @param length 数据长度
 * @return 发送结果
 */
bool Communication_SendPacket(CommCommand_t cmd, uint8_t* data, uint8_t length);

/**
 * @brief 发送位置数据
 * @param target_pos 目标位置
 * @param laser_pos 激光位置
 * @return 发送结果
 */
bool Communication_SendPositionData(PositionData_t* target_pos, PositionData_t* laser_pos);

/**
 * @brief 发送PID参数
 * @param params PID参数
 * @return 发送结果
 */
bool Communication_SendPIDParams(PIDParams_t* params);

/**
 * @brief 发送系统状态
 * @param status 系统状态
 * @return 发送结果
 */
bool Communication_SendSystemStatus(SystemStatus_t* status);

/**
 * @brief 发送心跳包
 * @return 发送结果
 */
bool Communication_SendHeartbeat(void);

/**
 * @brief 处理接收到的数据
 * @param data 接收数据
 * @param length 数据长度
 */
void Communication_ProcessReceiveData(uint8_t* data, uint8_t length);

/**
 * @brief 计算校验和
 * @param data 数据指针
 * @param length 数据长度
 * @return 校验和
 */
uint8_t Communication_CalculateChecksum(uint8_t* data, uint8_t length);

/**
 * @brief 验证数据包
 * @param packet 数据包指针
 * @return 验证结果
 */
bool Communication_ValidatePacket(CommPacket_t* packet);

/**
 * @brief 获取通信状态
 * @return 通信状态
 */
CommState_t Communication_GetState(void);

/**
 * @brief 获取通信统计信息
 * @return 统计信息指针
 */
CommStats_t* Communication_GetStats(void);

/**
 * @brief 重置通信统计信息
 */
void Communication_ResetStats(void);

/**
 * @brief 通信模块主循环处理
 * 需要在主循环中定期调用
 */
void Communication_Process(void);

/**
 * @brief 串口中断处理函数
 * 需要在串口中断中调用
 * @param data 接收到的字节
 */
void Communication_IRQHandler(uint8_t data);

/**
 * @brief 检查通信超时
 * @param timeout_ms 超时时间(毫秒)
 * @return 是否超时
 */
bool Communication_CheckTimeout(uint32_t timeout_ms);

#endif /* __COMMUNICATION_H */
