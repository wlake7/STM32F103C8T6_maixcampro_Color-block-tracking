/**
 * @file ServoBoard.h
 * @brief 舵机控制板通信模块头文件
 * @version 1.0
 * @date 2025-07-09
 * 
 * 实现与舵机控制板的串口通信协议
 * 控制水平和垂直舵机的运动
 */

#ifndef __SERVO_BOARD_H
#define __SERVO_BOARD_H

#include "stm32f10x.h"
#include <stdbool.h>
#include <stdint.h>

/* 舵机控制板通信配置 */
#define SERVO_UART                  USART2          // 使用USART2与舵机控制板通信
#define SERVO_UART_BAUDRATE         9600            // 波特率9600
#define SERVO_UART_TX_PIN           GPIO_Pin_2      // PA2 - TX
#define SERVO_UART_RX_PIN           GPIO_Pin_3      // PA3 - RX
#define SERVO_UART_GPIO_PORT        GPIOA
#define SERVO_UART_IRQ              USART2_IRQn

/* 控制板协议常量 */
#define SERVO_BOARD_HEADER1         0x55            // 帧头1
#define SERVO_BOARD_HEADER2         0x55            // 帧头2
#define SERVO_MAX_PACKET_SIZE       32              // 最大数据包大小
#define SERVO_COMM_TIMEOUT_MS       1000            // 通信超时时间
#define SERVO_MAX_SERVOS            6               // 最大舵机数量

/* 舵机ID定义 */
#define SERVO_ID_VERTICAL           1               // 垂直舵机ID
#define SERVO_ID_HORIZONTAL         2               // 水平舵机ID

/* 舵机位置范围 */
#define SERVO_POSITION_MIN          0               // 最小位置
#define SERVO_POSITION_MAX          1000            // 最大位置
#define SERVO_POSITION_CENTER       500             // 中心位置

/* 控制板命令定义 */
typedef enum {
    CMD_SERVO_MOVE              = 3,    // 控制舵机转动
    CMD_ACTION_GROUP_RUN        = 6,    // 动作组运行
    CMD_ACTION_GROUP_STOP       = 7,    // 动作组停止
    CMD_ACTION_GROUP_COMPLETE   = 8,    // 动作组完成
    CMD_ACTION_GROUP_SPEED      = 11,   // 动作组速度
    CMD_GET_BATTERY_VOLTAGE     = 15,   // 获取电池电压
    CMD_MULT_SERVO_UNLOAD       = 20,   // 多舵机卸力
    CMD_MULT_SERVO_POS_READ     = 21,   // 多舵机位置读取
} ServoBoardCommand_t;

/* 舵机控制参数结构 */
typedef struct {
    uint8_t id;                         // 舵机ID
    uint16_t position;                  // 目标位置 (0-1000)
    uint16_t time;                      // 运动时间 (ms)
} ServoMoveParam_t;

/* 舵机位置信息结构 */
typedef struct {
    uint8_t id;                         // 舵机ID
    uint16_t position;                  // 当前位置 (0-1000)
    bool valid;                         // 数据有效性
    uint32_t timestamp;                 // 时间戳
} ServoPositionInfo_t;

/* 舵机控制板状态枚举 */
typedef enum {
    SERVO_BOARD_STATE_IDLE = 0,         // 空闲状态
    SERVO_BOARD_STATE_BUSY,             // 忙碌状态
    SERVO_BOARD_STATE_ERROR,            // 错误状态
    SERVO_BOARD_STATE_TIMEOUT           // 超时状态
} ServoBoardState_t;

/* 舵机控制板统计信息 */
typedef struct {
    uint32_t packets_sent;              // 发送包数量
    uint32_t packets_received;          // 接收包数量
    uint32_t packets_error;             // 错误包数量
    uint32_t timeouts;                  // 超时次数
    uint32_t last_battery_voltage;      // 最后电池电压(mV)
    uint32_t last_update_time;          // 最后更新时间
} ServoBoardStats_t;

/* 舵机控制板系统状态 */
typedef struct {
    ServoBoardState_t state;            // 当前状态
    bool initialized;                   // 初始化状态
    bool communication_ok;              // 通信状态
    uint8_t servo_count;                // 舵机数量
    ServoPositionInfo_t servo_positions[SERVO_MAX_SERVOS]; // 舵机位置
    ServoBoardStats_t stats;            // 统计信息
    uint16_t current_h_position;        // 当前水平位置
    uint16_t current_v_position;        // 当前垂直位置
} ServoBoardSystem_t;

/* 全局变量声明 */
extern ServoBoardSystem_t g_servo_board_system;

/* 函数声明 */

/**
 * @brief 初始化舵机控制板通信模块
 * @return true: 成功, false: 失败
 */
bool ServoBoard_Init(void);

/**
 * @brief 反初始化舵机控制板通信模块
 */
void ServoBoard_DeInit(void);

/**
 * @brief 控制单个舵机移动
 * @param id 舵机ID
 * @param position 目标位置 (0-1000)
 * @param time 运动时间 (ms)
 * @return true: 成功, false: 失败
 */
bool ServoBoard_MoveServo(uint8_t id, uint16_t position, uint16_t time);

/**
 * @brief 控制多个舵机移动
 * @param servos 舵机参数数组
 * @param count 舵机数量
 * @return true: 成功, false: 失败
 */
bool ServoBoard_MoveMultiServos(ServoMoveParam_t* servos, uint8_t count);

/**
 * @brief 控制水平和垂直舵机移动
 * @param h_position 水平舵机位置 (0-1000)
 * @param v_position 垂直舵机位置 (0-1000)
 * @param time 运动时间 (ms)
 * @return true: 成功, false: 失败
 */
bool ServoBoard_MoveHV(uint16_t h_position, uint16_t v_position, uint16_t time);

/**
 * @brief 启用/禁用OLED调试显示
 * @param enable true: 启用, false: 禁用
 */
void ServoBoard_EnableOLEDDebug(bool enable);

/**
 * @brief 根据PID输出控制舵机
 * @param pid_output_h 水平PID输出
 * @param pid_output_v 垂直PID输出
 * @return true: 成功, false: 失败
 */
bool ServoBoard_ControlByPID(float pid_output_h, float pid_output_v);

/**
 * @brief 读取单个舵机位置
 * @param id 舵机ID
 * @param position 返回的位置值
 * @return true: 成功, false: 失败
 */
bool ServoBoard_ReadServoPosition(uint8_t id, uint16_t* position);

/**
 * @brief 控制多个舵机卸力
 * @param ids 舵机ID数组
 * @param count 舵机数量
 * @return true: 成功, false: 失败
 */
bool ServoBoard_UnloadServos(uint8_t* ids, uint8_t count);

/**
 * @brief 获取控制板电池电压
 * @param voltage 返回的电压值 (mV)
 * @return true: 成功, false: 失败
 */
bool ServoBoard_GetBatteryVoltage(uint16_t* voltage);

/**
 * @brief 处理舵机控制板数据接收 (在串口中断中调用)
 * @param data 接收到的数据
 */
void ServoBoard_IRQHandler(uint8_t data);

/**
 * @brief 舵机控制板主循环处理
 * 在主循环中定期调用
 */
void ServoBoard_Process(void);

/**
 * @brief 获取舵机控制板状态
 * @return 舵机控制板状态
 */
ServoBoardState_t ServoBoard_GetState(void);

/**
 * @brief 获取舵机控制板统计信息
 * @return 统计信息指针
 */
ServoBoardStats_t* ServoBoard_GetStats(void);

/**
 * @brief 检查通信是否正常
 * @return true: 正常, false: 异常
 */
bool ServoBoard_IsCommOK(void);

/**
 * @brief 重置舵机控制板模块
 */
void ServoBoard_Reset(void);

/**
 * @brief 舵机回到中心位置
 * @return true: 成功, false: 失败
 */
bool ServoBoard_ReturnToCenter(void);

/**
 * @brief 停止所有舵机运动
 * @return true: 成功, false: 失败
 */
bool ServoBoard_StopAll(void);

/* 位置转换宏 */
#define SERVO_ANGLE_TO_POSITION(angle) ((uint16_t)((angle) * 1000 / 240))
#define SERVO_POSITION_TO_ANGLE(pos)   ((float)(pos) * 240.0f / 1000.0f)

/* PID输出到舵机位置的转换 */
#define PID_OUTPUT_TO_POSITION_OFFSET(output) ((int16_t)((output) * 0.5f))

/* 调试宏 */
#ifdef DEBUG_SERVO_BOARD
#define SERVO_BOARD_DEBUG(fmt, ...) printf("[ServoBoard] " fmt "\r\n", ##__VA_ARGS__)
#else
#define SERVO_BOARD_DEBUG(fmt, ...)
#endif

#endif /* __SERVO_BOARD_H */
