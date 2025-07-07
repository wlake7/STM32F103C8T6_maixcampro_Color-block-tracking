/**
 * @file ControlBoard.h
 * @brief 舵机控制板通信协议模块头文件
 * @version 1.0
 * @date 2024-01-01
 * 
 * 实现与舵机控制板的串口通信协议
 * 波特率: 9600
 * 协议格式: 0x55 0x55 + Length + Cmd + Parameters
 */

#ifndef __CONTROL_BOARD_H
#define __CONTROL_BOARD_H

#include "stm32f10x.h"
#include <stdbool.h>
#include <stdint.h>

/* 外部函数声明 */
extern uint32_t System_GetTick(void);

/* 控制板通信配置 */
#define CONTROL_BOARD_BAUDRATE          9600        // 控制板波特率
#define CONTROL_BOARD_MAX_PACKET_SIZE   32          // 最大数据包大小
#define CONTROL_BOARD_TIMEOUT_MS        1000        // 通信超时时间
#define CONTROL_BOARD_RETRY_COUNT       3           // 重试次数

/* 控制板协议常量 */
#define CONTROL_BOARD_HEADER1           0x55        // 帧头1
#define CONTROL_BOARD_HEADER2           0x55        // 帧头2
#define CONTROL_BOARD_MAX_SERVOS        6           // 最大舵机数量

/* 控制板命令定义 */
typedef enum {
    CMD_SERVO_MOVE                  = 3,    // 控制舵机转动
    CMD_ACTION_GROUP_RUN            = 6,    // 动作组运行
    CMD_ACTION_GROUP_STOP           = 7,    // 动作组停止
    CMD_ACTION_GROUP_COMPLETE       = 8,    // 动作组完成
    CMD_ACTION_GROUP_SPEED          = 11,   // 动作组速度
    CMD_GET_BATTERY_VOLTAGE         = 15,   // 获取电池电压
    CMD_MULT_SERVO_UNLOAD           = 20,   // 多舵机卸力
    CMD_MULT_SERVO_POS_READ         = 21,   // 多舵机位置读取
} ControlBoardCommand_t;

/* 舵机控制参数结构 */
typedef struct {
    uint8_t id;                             // 舵机ID
    uint16_t position;                      // 目标位置 (0-1000)
    uint16_t time;                          // 运动时间 (ms)
} ServoMoveParam_t;

/* 舵机位置信息结构 */
typedef struct {
    uint8_t id;                             // 舵机ID
    uint16_t position;                      // 当前位置 (0-1000)
    bool valid;                             // 数据有效性
} ServoPositionInfo_t;

/* 控制板数据包结构 */
typedef struct {
    uint8_t header[2];                      // 帧头 0x55 0x55
    uint8_t length;                         // 数据长度
    uint8_t command;                        // 命令
    uint8_t data[CONTROL_BOARD_MAX_PACKET_SIZE - 4]; // 参数数据
} ControlBoardPacket_t;

/* 控制板状态枚举 */
typedef enum {
    CONTROL_BOARD_STATE_IDLE = 0,           // 空闲状态
    CONTROL_BOARD_STATE_BUSY,               // 忙碌状态
    CONTROL_BOARD_STATE_ERROR,              // 错误状态
    CONTROL_BOARD_STATE_TIMEOUT             // 超时状态
} ControlBoardState_t;

/* 控制板统计信息 */
typedef struct {
    uint32_t packets_sent;                  // 发送包数量
    uint32_t packets_received;              // 接收包数量
    uint32_t packets_error;                 // 错误包数量
    uint32_t timeouts;                      // 超时次数
    uint32_t last_battery_voltage;          // 最后电池电压(mV)
    uint32_t last_update_time;              // 最后更新时间
} ControlBoardStats_t;

/* 控制板系统状态 */
typedef struct {
    ControlBoardState_t state;              // 当前状态
    bool initialized;                       // 初始化状态
    bool communication_ok;                  // 通信状态
    uint8_t servo_count;                    // 舵机数量
    ServoPositionInfo_t servo_positions[CONTROL_BOARD_MAX_SERVOS]; // 舵机位置
    ControlBoardStats_t stats;              // 统计信息
} ControlBoardSystem_t;

/* 全局变量声明 */
extern ControlBoardSystem_t g_control_board_system;

/* 函数声明 */

/**
 * @brief 初始化控制板通信模块
 * @return true: 成功, false: 失败
 */
bool ControlBoard_Init(void);

/**
 * @brief 反初始化控制板通信模块
 */
void ControlBoard_DeInit(void);

/**
 * @brief USART2硬件测试
 */
void ControlBoard_HardwareTest(void);

/**
 * @brief 控制单个舵机移动
 * @param id 舵机ID
 * @param position 目标位置 (0-1000)
 * @param time 运动时间 (ms)
 * @return true: 成功, false: 失败
 */
bool ControlBoard_MoveServo(uint8_t id, uint16_t position, uint16_t time);

/**
 * @brief 控制多个舵机移动
 * @param servos 舵机参数数组
 * @param count 舵机数量
 * @return true: 成功, false: 失败
 */
bool ControlBoard_MoveMultiServos(ServoMoveParam_t* servos, uint8_t count);

/**
 * @brief 读取单个舵机位置
 * @param id 舵机ID
 * @param position 返回的位置值
 * @return true: 成功, false: 失败
 */
bool ControlBoard_ReadServoPosition(uint8_t id, uint16_t* position);

/**
 * @brief 读取多个舵机位置
 * @param ids 舵机ID数组
 * @param count 舵机数量
 * @param positions 返回的位置信息数组
 * @return true: 成功, false: 失败
 */
bool ControlBoard_ReadMultiServoPositions(uint8_t* ids, uint8_t count, 
                                         ServoPositionInfo_t* positions);

/**
 * @brief 控制多个舵机卸力
 * @param ids 舵机ID数组
 * @param count 舵机数量
 * @return true: 成功, false: 失败
 */
bool ControlBoard_UnloadServos(uint8_t* ids, uint8_t count);

/**
 * @brief 获取控制板电池电压
 * @param voltage 返回的电压值 (mV)
 * @return true: 成功, false: 失败
 */
bool ControlBoard_GetBatteryVoltage(uint16_t* voltage);

/**
 * @brief 运行动作组
 * @param group_id 动作组ID
 * @param times 运行次数 (0表示无限次)
 * @return true: 成功, false: 失败
 */
bool ControlBoard_RunActionGroup(uint8_t group_id, uint16_t times);

/**
 * @brief 停止动作组
 * @return true: 成功, false: 失败
 */
bool ControlBoard_StopActionGroup(void);

/**
 * @brief 设置动作组速度
 * @param group_id 动作组ID (0xFF表示所有动作组)
 * @param speed_percent 速度百分比 (例如: 200表示200%)
 * @return true: 成功, false: 失败
 */
bool ControlBoard_SetActionGroupSpeed(uint8_t group_id, uint16_t speed_percent);

/**
 * @brief 处理控制板数据接收
 * 在串口中断中调用
 * @param data 接收到的数据
 */
void ControlBoard_IRQHandler(uint8_t data);

/**
 * @brief 控制板主循环处理
 * 在主循环中定期调用
 */
void ControlBoard_Process(void);

/**
 * @brief 获取控制板状态
 * @return 控制板状态
 */
ControlBoardState_t ControlBoard_GetState(void);

/**
 * @brief 获取控制板统计信息
 * @return 统计信息指针
 */
ControlBoardStats_t* ControlBoard_GetStats(void);

/**
 * @brief 检查通信是否正常
 * @return true: 正常, false: 异常
 */
bool ControlBoard_IsCommOK(void);

/**
 * @brief 重置控制板模块
 */
void ControlBoard_Reset(void);

/* 便捷宏定义 */
#define CONTROL_BOARD_SERVO_ID_HORIZONTAL   2   // 水平舵机ID
#define CONTROL_BOARD_SERVO_ID_VERTICAL     1   // 垂直舵机ID

/* 位置转换宏 */
#define CONTROL_BOARD_ANGLE_TO_POSITION(angle) ((uint16_t)((angle) * 1000 / 240))
#define CONTROL_BOARD_POSITION_TO_ANGLE(pos)   ((float)(pos) * 240.0f / 1000.0f)

/* 调试宏 */
#ifdef DEBUG_CONTROL_BOARD
#define CONTROL_BOARD_DEBUG(fmt, ...) printf("[ControlBoard] " fmt "\r\n", ##__VA_ARGS__)
#else
#define CONTROL_BOARD_DEBUG(fmt, ...)
#endif

#endif /* __CONTROL_BOARD_H */
