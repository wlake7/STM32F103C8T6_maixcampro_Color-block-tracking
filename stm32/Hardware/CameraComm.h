/**
 * @file CameraComm.h
 * @brief 摄像头通信模块头文件
 * @version 1.0
 * @date 2025-07-09
 * 
 * 实现与MaixCam Pro摄像头的串口通信协议
 * 接收红色目标和绿色激光的坐标数据
 */

#ifndef __CAMERA_COMM_H
#define __CAMERA_COMM_H

#include "stm32f10x.h"
#include <stdbool.h>
#include <stdint.h>

/* 摄像头通信配置 */
#define CAMERA_UART                 USART1          // 使用USART1与摄像头通信
#define CAMERA_UART_BAUDRATE        115200          // 波特率115200
#define CAMERA_UART_TX_PIN          GPIO_Pin_9      // PA9 - TX
#define CAMERA_UART_RX_PIN          GPIO_Pin_10     // PA10 - RX
#define CAMERA_UART_GPIO_PORT       GPIOA
#define CAMERA_UART_IRQ             USART1_IRQn

/* 通信协议配置 */
#define CAMERA_PACKET_HEADER1       0xAA            // 帧头1
#define CAMERA_PACKET_HEADER2       0x55            // 帧头2
#define CAMERA_MAX_PACKET_SIZE      64              // 最大数据包大小
#define CAMERA_COMM_TIMEOUT_MS      10000             // 通信超时时间

/* 命令定义 */
typedef enum {
    CMD_TARGET_POSITION     = 0x01,    // 目标位置数据
    CMD_LASER_POSITION      = 0x02,    // 激光位置数据
    CMD_PID_PARAMS          = 0x03,    // PID参数
    CMD_SYSTEM_STATUS       = 0x04,    // 系统状态
    CMD_CALIBRATION         = 0x05,    // 标定数据
} CameraCommand_t;

/* 位置数据结构 */
typedef struct {
    int16_t x;              // X坐标
    int16_t y;              // Y坐标
    uint16_t confidence;    // 置信度 (0-100)
    uint16_t timestamp;     // 时间戳
    bool valid;             // 数据有效性
} PositionData_t;

/* 追踪数据结构 */
typedef struct {
    PositionData_t target;  // 红色目标位置
    PositionData_t laser;   // 绿色激光位置
    bool both_detected;     // 是否同时检测到目标和激光
    uint32_t frame_id;      // 帧ID
} TrackingData_t;

/* 通信统计信息 */
typedef struct {
    uint32_t packets_received;      // 接收包数量
    uint32_t packets_valid;         // 有效包数量
    uint32_t packets_error;         // 错误包数量
    uint32_t last_receive_time;     // 最后接收时间
    uint32_t communication_errors;  // 通信错误次数
} CameraCommStats_t;

/* 摄像头通信系统状态 */
typedef struct {
    bool initialized;               // 初始化状态
    bool communication_ok;          // 通信状态
    TrackingData_t latest_data;     // 最新追踪数据
    CameraCommStats_t stats;        // 统计信息
    uint32_t last_data_time;        // 最后数据时间
} CameraCommSystem_t;

/* 全局变量声明 */
extern CameraCommSystem_t g_camera_comm_system;

/* 函数声明 */

/**
 * @brief 初始化摄像头通信模块
 * @return true: 成功, false: 失败
 */
bool CameraComm_Init(void);

/**
 * @brief 反初始化摄像头通信模块
 */
void CameraComm_DeInit(void);

/**
 * @brief 获取最新的追踪数据
 * @param data 输出的追踪数据
 * @return true: 有新数据, false: 无新数据
 */
bool CameraComm_GetLatestData(TrackingData_t* data);

/**
 * @brief 检查是否有新的追踪数据
 * @return true: 有新数据, false: 无新数据
 */
bool CameraComm_HasNewData(void);

/**
 * @brief 处理摄像头数据接收 (在串口中断中调用)
 * @param data 接收到的数据
 */
void CameraComm_IRQHandler(uint8_t data);

/**
 * @brief 摄像头通信主循环处理
 * 在主循环中定期调用
 */
void CameraComm_Process(void);

/**
 * @brief 检查通信是否正常
 * @return true: 正常, false: 异常
 */
bool CameraComm_IsCommOK(void);

/**
 * @brief 获取通信统计信息
 * @return 统计信息指针
 */
CameraCommStats_t* CameraComm_GetStats(void);

/**
 * @brief 重置摄像头通信模块
 */
void CameraComm_Reset(void);

/**
 * @brief 发送系统状态请求
 * @return true: 成功, false: 失败
 */
bool CameraComm_RequestStatus(void);

/**
 * @brief 发送PID参数到摄像头
 * @param kp_h 水平Kp
 * @param ki_h 水平Ki  
 * @param kd_h 水平Kd
 * @param kp_v 垂直Kp
 * @param ki_v 垂直Ki
 * @param kd_v 垂直Kd
 * @return true: 成功, false: 失败
 */
bool CameraComm_SendPIDParams(float kp_h, float ki_h, float kd_h, 
                              float kp_v, float ki_v, float kd_v);

/* 调试宏 */
#ifdef DEBUG_CAMERA_COMM
#define CAMERA_COMM_DEBUG(fmt, ...) printf("[CameraComm] " fmt "\r\n", ##__VA_ARGS__)
#else
#define CAMERA_COMM_DEBUG(fmt, ...)
#endif

#endif /* __CAMERA_COMM_H */
