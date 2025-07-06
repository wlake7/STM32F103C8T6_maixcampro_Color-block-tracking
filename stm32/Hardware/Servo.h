/**
 * @file Servo.h
 * @brief STM32端舵机控制模块头文件
 * @author AI Assistant
 * @date 2025-07-06
 * 
 * 实现Huaner LX-224舵机通信协议，支持位置控制、参数配置、状态查询等功能
 */

#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"
#include <stdint.h>
#include <stdbool.h>

/* 舵机协议定义 */
#define SERVO_HEADER_BYTE1          0x55    // 帧头第一字节
#define SERVO_HEADER_BYTE2          0x55    // 帧头第二字节
#define SERVO_BROADCAST_ID          0xFE    // 广播ID
#define SERVO_MAX_DATA_SIZE         8       // 最大数据长度
#define SERVO_MAX_PACKET_SIZE       16      // 最大包长度

/* 舵机ID定义 */
#define SERVO_ID_VERTICAL           1       // 垂直舵机ID
#define SERVO_ID_HORIZONTAL         2       // 水平舵机ID

/* 舵机角度范围 */
#define SERVO_ANGLE_MIN             0       // 最小角度值
#define SERVO_ANGLE_MAX             1000    // 最大角度值 (对应240度)
#define SERVO_ANGLE_CENTER          500     // 中心角度值 (对应120度)

/* 舵机时间范围 */
#define SERVO_TIME_MIN              0       // 最小时间(ms)
#define SERVO_TIME_MAX              30000   // 最大时间(ms)

/* 舵机命令定义 */
typedef enum {
    SERVO_MOVE_TIME_WRITE           = 1,    // 位置时间控制写
    SERVO_MOVE_TIME_READ            = 2,    // 位置时间控制读
    SERVO_MOVE_TIME_WAIT_WRITE      = 7,    // 位置时间等待写
    SERVO_MOVE_TIME_WAIT_READ       = 8,    // 位置时间等待读
    SERVO_MOVE_START                = 11,   // 开始运动
    SERVO_MOVE_STOP                 = 12,   // 停止运动
    SERVO_ID_WRITE                  = 13,   // ID写入
    SERVO_ID_READ                   = 14,   // ID读取
    SERVO_ANGLE_OFFSET_ADJUST       = 17,   // 角度偏差调整
    SERVO_ANGLE_OFFSET_WRITE        = 18,   // 角度偏差写入
    SERVO_ANGLE_OFFSET_READ         = 19,   // 角度偏差读取
    SERVO_ANGLE_LIMIT_WRITE         = 20,   // 角度限制写入
    SERVO_ANGLE_LIMIT_READ          = 21,   // 角度限制读取
    SERVO_VIN_LIMIT_WRITE           = 22,   // 电压限制写入
    SERVO_VIN_LIMIT_READ            = 23,   // 电压限制读取
    SERVO_TEMP_MAX_LIMIT_WRITE      = 24,   // 温度限制写入
    SERVO_TEMP_MAX_LIMIT_READ       = 25,   // 温度限制读取
    SERVO_TEMP_READ                 = 26,   // 温度读取
    SERVO_VIN_READ                  = 27,   // 电压读取
    SERVO_POS_READ                  = 28,   // 位置读取
    SERVO_OR_MOTOR_MODE_WRITE       = 29,   // 模式写入
    SERVO_OR_MOTOR_MODE_READ        = 30,   // 模式读取
    SERVO_LOAD_OR_UNLOAD_WRITE      = 31,   // 加载/卸载写入
    SERVO_LOAD_OR_UNLOAD_READ       = 32,   // 加载/卸载读取
    SERVO_LED_CTRL_WRITE            = 33,   // LED控制写入
    SERVO_LED_CTRL_READ             = 34,   // LED控制读取
    SERVO_LED_ERROR_WRITE           = 35,   // LED错误写入
    SERVO_LED_ERROR_READ            = 36    // LED错误读取
} ServoCommand_t;

/* 舵机状态 */
typedef enum {
    SERVO_STATE_IDLE = 0,                   // 空闲状态
    SERVO_STATE_MOVING,                     // 运动中
    SERVO_STATE_WAITING,                    // 等待状态
    SERVO_STATE_ERROR                       // 错误状态
} ServoState_t;

/* 舵机模式 */
typedef enum {
    SERVO_MODE_POSITION = 0,                // 位置控制模式
    SERVO_MODE_MOTOR = 1                    // 电机控制模式
} ServoMode_t;

/* 舵机数据包结构 */
typedef struct {
    uint8_t header[2];                      // 帧头 [0x55, 0x55]
    uint8_t id;                             // 舵机ID
    uint8_t length;                         // 数据长度
    uint8_t command;                        // 命令字
    uint8_t data[SERVO_MAX_DATA_SIZE];      // 数据
    uint8_t checksum;                       // 校验和
} ServoPacket_t;

/* 舵机位置控制结构 */
typedef struct {
    uint16_t angle;                         // 目标角度 (0-1000)
    uint16_t time;                          // 运动时间 (ms)
} ServoPosition_t;

/* 舵机状态信息结构 */
typedef struct {
    uint8_t id;                             // 舵机ID
    ServoState_t state;                     // 当前状态
    uint16_t current_angle;                 // 当前角度
    uint16_t target_angle;                  // 目标角度
    uint16_t voltage;                       // 当前电压
    uint8_t temperature;                    // 当前温度
    bool is_loaded;                         // 是否加载
    uint32_t last_update;                   // 最后更新时间
} ServoStatus_t;

/* 舵机统计信息 */
typedef struct {
    uint32_t commands_sent;                 // 发送命令数
    uint32_t responses_received;            // 接收响应数
    uint32_t checksum_errors;               // 校验错误数
    uint32_t timeout_errors;                // 超时错误数
} ServoStats_t;

/* 全局变量声明 */
extern ServoStatus_t g_servo_vertical;     // 垂直舵机状态
extern ServoStatus_t g_servo_horizontal;   // 水平舵机状态
extern ServoStats_t g_servo_stats;         // 舵机统计信息

/* 函数声明 */

/**
 * @brief 初始化舵机控制模块
 * @param baudrate 波特率 (默认115200)
 * @return 初始化结果
 */
bool Servo_Init(uint32_t baudrate);

/**
 * @brief 发送舵机命令包
 * @param id 舵机ID
 * @param cmd 命令字
 * @param data 数据指针
 * @param length 数据长度
 * @return 发送结果
 */
bool Servo_SendCommand(uint8_t id, ServoCommand_t cmd, uint8_t* data, uint8_t length);

/**
 * @brief 控制舵机移动到指定位置
 * @param id 舵机ID
 * @param angle 目标角度 (0-1000)
 * @param time 运动时间 (ms)
 * @return 控制结果
 */
bool Servo_MoveToPosition(uint8_t id, uint16_t angle, uint16_t time);

/**
 * @brief 控制舵机移动到指定位置(等待模式)
 * @param id 舵机ID
 * @param angle 目标角度 (0-1000)
 * @param time 运动时间 (ms)
 * @return 控制结果
 */
bool Servo_MoveToPositionWait(uint8_t id, uint16_t angle, uint16_t time);

/**
 * @brief 启动舵机运动
 * @param id 舵机ID
 * @return 控制结果
 */
bool Servo_StartMove(uint8_t id);

/**
 * @brief 停止舵机运动
 * @param id 舵机ID
 * @return 控制结果
 */
bool Servo_StopMove(uint8_t id);

/**
 * @brief 读取舵机当前位置
 * @param id 舵机ID
 * @return 读取结果
 */
bool Servo_ReadPosition(uint8_t id);

/**
 * @brief 读取舵机状态
 * @param id 舵机ID
 * @return 读取结果
 */
bool Servo_ReadStatus(uint8_t id);

/**
 * @brief 设置舵机加载状态
 * @param id 舵机ID
 * @param load 是否加载 (true=加载, false=卸载)
 * @return 设置结果
 */
bool Servo_SetLoad(uint8_t id, bool load);

/**
 * @brief 设置舵机角度偏差
 * @param id 舵机ID
 * @param offset 偏差值 (-125 ~ 125)
 * @return 设置结果
 */
bool Servo_SetAngleOffset(uint8_t id, int8_t offset);

/**
 * @brief 计算舵机命令校验和
 * @param data 数据指针
 * @param length 数据长度
 * @return 校验和
 */
uint8_t Servo_CalculateChecksum(uint8_t* data, uint8_t length);

/**
 * @brief 验证舵机响应包
 * @param packet 数据包指针
 * @return 验证结果
 */
bool Servo_ValidateResponse(ServoPacket_t* packet);

/**
 * @brief 获取舵机状态
 * @param id 舵机ID
 * @return 舵机状态指针
 */
ServoStatus_t* Servo_GetStatus(uint8_t id);

/**
 * @brief 获取舵机统计信息
 * @return 统计信息指针
 */
ServoStats_t* Servo_GetStats(void);

/**
 * @brief 重置舵机统计信息
 */
void Servo_ResetStats(void);

/**
 * @brief 舵机模块主循环处理
 * 需要在主循环中定期调用
 */
void Servo_Process(void);

/**
 * @brief 处理舵机响应数据
 * @param data 接收数据
 * @param length 数据长度
 */
void Servo_ProcessResponse(uint8_t* data, uint8_t length);

/**
 * @brief 角度值转换 (0-1000 <-> 0-240度)
 * @param angle_raw 原始角度值 (0-1000)
 * @return 实际角度 (度)
 */
float Servo_ConvertAngleToFloat(uint16_t angle_raw);

/**
 * @brief 角度值转换 (0-240度 -> 0-1000)
 * @param angle_float 实际角度 (度)
 * @return 原始角度值 (0-1000)
 */
uint16_t Servo_ConvertFloatToAngle(float angle_float);

/**
 * @brief 检查舵机响应超时
 * @param timeout_ms 超时时间(毫秒)
 * @return 是否超时
 */
bool Servo_CheckTimeout(uint32_t timeout_ms);

#endif /* __SERVO_H */
