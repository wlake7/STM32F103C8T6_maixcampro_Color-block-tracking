#include "LaserTracker.h"
#include "ServoControl.h"
#include "Timer.h"
#include "Delay.h"
#include "OLED.h"
#include <string.h>
#include <math.h>

/**
 * @file LaserTracker.c
 * @brief 激光追踪控制模块实现
 * @version 2.0
 * @date 2025-07-11
 *
 * 更新说明：
 * - 将简单比例控制改为完整PID控制
 * - 控制逻辑：绿色激光追踪红色目标色块
 *   目标位置 = 摄像头识别的红色色块坐标
 *   当前位置 = 摄像头识别的绿色激光坐标
 *   误差计算 = 目标位置 - 激光位置 (经过死区和安全检查)
 *   PID输出 = PID_CalculateWithError(预处理后的误差)
 * - 修正重复计算误差的问题：
 *   原来：error_x计算 + PID内部再次计算误差 (重复且逻辑断层)
 *   现在：error_x计算 + 死区/安全处理 + 直接传入PID (逻辑清晰)
 * - 所有调试参数使用宏定义，便于调试和优化
 * - 增加安全检查和保护机制
 * - 优化OLED显示，显示实际使用的误差和PID输出
 * - 支持调试开关，便于性能优化
 */

/* 全局激光追踪系统状态 */
static LaserTracker_t g_laser_tracker;



/* 内部函数声明 */
static void PID_Init(PID_Controller_t* pid, float kp, float ki, float kd, float max_output);
static float PID_Calculate(PID_Controller_t* pid, float setpoint, float measured);
static float PID_CalculateWithError(PID_Controller_t* pid, float error);
static uint16_t Position_ToServoPos(int16_t image_pos, uint8_t is_horizontal);

/**
 * @brief 初始化激光追踪系统
 */
bool LaserTracker_Init(void)
{
    // OLED显示初始化信息
    OLED_Clear();
    OLED_ShowString(1, 1, "LASER TRACK MODE");
    OLED_ShowString(2, 1, "Initializing...");

    // 清零追踪系统状态
    memset(&g_laser_tracker, 0, sizeof(LaserTracker_t));

    // 初始化PID控制器 - 使用宏定义参数便于调试
    PID_Init(&g_laser_tracker.pid_h, PID_KP_H, PID_KI_H, PID_KD_H, PID_MAX_OUTPUT);
    PID_Init(&g_laser_tracker.pid_v, PID_KP_V, PID_KI_V, PID_KD_V, PID_MAX_OUTPUT);

    // 显示PID参数 - 使用宏定义值
    OLED_ShowString(2, 1, "PID: Kp=");
    OLED_ShowNum(2, 9, (uint32_t)(PID_KP_H * 10), 2);  // 显示2.0为20
    OLED_ShowString(3, 1, "Ki=");
    OLED_ShowNum(3, 4, (uint32_t)(PID_KI_H * 100), 2); // 显示0.01为1
    OLED_ShowString(3, 7, " Kd=");
    OLED_ShowNum(3, 11, (uint32_t)(PID_KD_H * 10), 1); // 显示0.1为1

    // 设置舵机初始位置为中心
    g_laser_tracker.servo_h_pos = SERVO_POS_CENTER;
    g_laser_tracker.servo_v_pos = SERVO_POS_CENTER;

    // 等待系统稳定
    Delay_ms(1000);

    // 舵机回到中心位置
    OLED_ShowString(4, 1, "Centering servo");
    ServoBoard_MoveHV(SERVO_POS_CENTER, SERVO_POS_CENTER, 1000);
    Delay_ms(1500);

    // 激活追踪
    g_laser_tracker.tracking_active = 1;
    g_laser_tracker.last_update_time = Timer_GetSystemTick();

    // 显示就绪状态
    OLED_ShowString(2, 1, "Ready to track ");
    OLED_ShowString(4, 1, "Waiting target ");

    return true;
}

/**
 * @brief 反初始化激光追踪系统
 */
void LaserTracker_DeInit(void)
{
    g_laser_tracker.tracking_active = 0;
    
    // 舵机回到中心位置
    ServoBoard_MoveHV(SERVO_POS_CENTER, SERVO_POS_CENTER, 1000);
    Delay_ms(1000);
}

/**
 * @brief 激光追踪主处理函数
 */
void LaserTracker_Process(void)
{
    uint32_t current_time = Timer_GetSystemTick();
    
    if (!g_laser_tracker.tracking_active) {
        return;
    }
    
    // 检查是否有新的位置数据
    if (g_laser_tracker.target_pos.valid && g_laser_tracker.laser_pos.valid) {
        // 更新最后更新时间
        g_laser_tracker.last_update_time = System_GetTick();
        // 计算位置误差（目标位置 - 激光位置）
        float error_x = (float)g_laser_tracker.target_pos.x - (float)g_laser_tracker.laser_pos.x;
        float error_y = (float)g_laser_tracker.target_pos.y - (float)g_laser_tracker.laser_pos.y;

        // 添加死区处理，避免小误差引起抖动
        if (fabs(error_x) < DEADZONE_PIXELS) error_x = 0.0f;
        if (fabs(error_y) < DEADZONE_PIXELS) error_y = 0.0f;

#if ENABLE_SAFETY_CHECK
        // 安全检查：限制最大误差，防止异常数据
        if (fabs(error_x) > ERROR_LIMIT_PIXELS) error_x = (error_x > 0) ? ERROR_LIMIT_PIXELS : -ERROR_LIMIT_PIXELS;
        if (fabs(error_y) > ERROR_LIMIT_PIXELS) error_y = (error_y > 0) ? ERROR_LIMIT_PIXELS : -ERROR_LIMIT_PIXELS;
#endif

        // 使用PID控制算法 - 直接传入预处理后的误差
        // 注意：这里使用PID_CalculateWithError函数，避免重复计算误差
        float pid_output_h = PID_CalculateWithError(&g_laser_tracker.pid_h, error_x);
        float pid_output_v = PID_CalculateWithError(&g_laser_tracker.pid_v, error_y);

        // 将PID输出转换为舵机位置增量
        float h_increment = pid_output_h * SERVO_RESPONSE_GAIN;
        float v_increment = pid_output_v * SERVO_RESPONSE_GAIN;

        // 限制单次增量，防止过大跳跃
        if (h_increment > MAX_SERVO_INCREMENT) h_increment = MAX_SERVO_INCREMENT;
        if (h_increment < -MAX_SERVO_INCREMENT) h_increment = -MAX_SERVO_INCREMENT;
        if (v_increment > MAX_SERVO_INCREMENT) v_increment = MAX_SERVO_INCREMENT;
        if (v_increment < -MAX_SERVO_INCREMENT) v_increment = -MAX_SERVO_INCREMENT;

        // 更新舵机位置（增量控制）
        int16_t new_h_pos = (int16_t)g_laser_tracker.servo_h_pos + (int16_t)h_increment;
        int16_t new_v_pos = (int16_t)g_laser_tracker.servo_v_pos + (int16_t)v_increment;

        // 安全位置限幅 - 使用宏定义的安全范围
#if ENABLE_SAFETY_CHECK
        if (new_h_pos < SERVO_SAFE_MIN) new_h_pos = SERVO_SAFE_MIN;
        if (new_h_pos > SERVO_SAFE_MAX) new_h_pos = SERVO_SAFE_MAX;
        if (new_v_pos < SERVO_SAFE_MIN) new_v_pos = SERVO_SAFE_MIN;
        if (new_v_pos > SERVO_SAFE_MAX) new_v_pos = SERVO_SAFE_MAX;
#else
        // 基本位置限幅
        if (new_h_pos < SERVO_POS_MIN) new_h_pos = SERVO_POS_MIN;
        if (new_h_pos > SERVO_POS_MAX) new_h_pos = SERVO_POS_MAX;
        if (new_v_pos < SERVO_POS_MIN) new_v_pos = SERVO_POS_MIN;
        if (new_v_pos > SERVO_POS_MAX) new_v_pos = SERVO_POS_MAX;
#endif

        g_laser_tracker.servo_h_pos = -(uint16_t)new_h_pos;
        g_laser_tracker.servo_v_pos = -(uint16_t)new_v_pos;

        // 发送舵机控制命令 - 使用宏定义的移动时间
        ServoBoard_MoveHV(g_laser_tracker.servo_h_pos, g_laser_tracker.servo_v_pos, SERVO_MOVE_TIME);

#if ENABLE_OLED_DEBUG
        // OLED实时调试显示 - 使用宏定义的更新分频
        static uint32_t debug_counter = 0;
        if (++debug_counter % DEBUG_UPDATE_DIV == 0) {
            // 第2行：显示目标和激光位置
            OLED_ShowString(2, 1, "T:");
            OLED_ShowNum(2, 3, g_laser_tracker.target_pos.x, 3);
            OLED_ShowString(2, 6, ",");
            OLED_ShowNum(2, 7, g_laser_tracker.target_pos.y, 3);

            OLED_ShowString(2, 11, "L:");
            OLED_ShowNum(2, 13, g_laser_tracker.laser_pos.x, 3);
            OLED_ShowString(2, 16, ",");
            OLED_ShowNum(2, 17, g_laser_tracker.laser_pos.y, 3);

            // 第3行：显示误差和PID输出
            OLED_ShowString(3, 1, "E:");
            OLED_ShowSignedNum(3, 3, (int32_t)error_x, 3);
            OLED_ShowString(3, 6, ",");
            OLED_ShowSignedNum(3, 7, (int32_t)error_y, 3);
            OLED_ShowString(3, 11, "P:");
            OLED_ShowSignedNum(3, 13, (int32_t)pid_output_h, 2);
            OLED_ShowString(3, 15, ",");
            OLED_ShowSignedNum(3, 16, (int32_t)pid_output_v, 2);

            // 第4行：显示舵机位置
            OLED_ShowString(4, 1, "Servo:");
            OLED_ShowNum(4, 7, g_laser_tracker.servo_h_pos, 3);
            OLED_ShowString(4, 10, ",");
            OLED_ShowNum(4, 11, g_laser_tracker.servo_v_pos, 3);
        }
#endif // ENABLE_OLED_DEBUG

        // 保持数据有效标志，避免数据丢失导致回中
        // g_laser_tracker.target_pos.valid = 0;
        // g_laser_tracker.laser_pos.valid = 0;
    }
    
    // 超时检测（5秒无数据则显示超时时间）
    if (g_laser_tracker.last_update_time > 0 &&
        (current_time - g_laser_tracker.last_update_time) > 5000) {
        static uint32_t warning_counter = 0;
        if (++warning_counter % 10 == 0) {  // 每10次显示一次超时时间
            uint32_t timeout_sec = (current_time - g_laser_tracker.last_update_time) / 1000;
            OLED_ShowString(1, 1, "TIMEOUT:");
            OLED_ShowNum(1, 9, timeout_sec, 3);
            OLED_ShowString(1, 12, "s");
        }
    }
}

/**
 * @brief 获取追踪状态
 */
bool LaserTracker_IsActive(void)
{
    return g_laser_tracker.tracking_active;
}

/**
 * @brief 设置追踪状态
 */
void LaserTracker_SetActive(bool active)
{
    g_laser_tracker.tracking_active = active ? 1 : 0;
    
    if (!active) {
        // 停止追踪时回到中心位置
        ServoBoard_MoveHV(SERVO_POS_CENTER, SERVO_POS_CENTER, 500);
        g_laser_tracker.servo_h_pos = SERVO_POS_CENTER;
        g_laser_tracker.servo_v_pos = SERVO_POS_CENTER;
    }
}

/**
 * @brief 更新目标位置
 */
void LaserTracker_UpdateTargetPosition(int16_t x, int16_t y)
{
    g_laser_tracker.target_pos.x = x;
    g_laser_tracker.target_pos.y = y;
    g_laser_tracker.target_pos.valid = 1;
}

/**
 * @brief 更新激光位置
 */
void LaserTracker_UpdateLaserPosition(int16_t x, int16_t y)
{
    g_laser_tracker.laser_pos.x = x;
    g_laser_tracker.laser_pos.y = y;
    g_laser_tracker.laser_pos.valid = 1;
}

/**
 * @brief 更新PID参数
 */
void LaserTracker_UpdatePIDParams(float kp_h, float ki_h, float kd_h, 
                                  float kp_v, float ki_v, float kd_v)
{
    g_laser_tracker.pid_h.kp = kp_h;
    g_laser_tracker.pid_h.ki = ki_h;
    g_laser_tracker.pid_h.kd = kd_h;
    g_laser_tracker.pid_v.kp = kp_v;
    g_laser_tracker.pid_v.ki = ki_v;
    g_laser_tracker.pid_v.kd = kd_v;
}

/**
 * @brief 获取舵机位置
 */
void LaserTracker_GetServoPosition(uint16_t* h_pos, uint16_t* v_pos)
{
    if (h_pos) *h_pos = g_laser_tracker.servo_h_pos;
    if (v_pos) *v_pos = g_laser_tracker.servo_v_pos;
}

/**
 * @brief PID控制器初始化 - 使用宏定义参数
 */
static void PID_Init(PID_Controller_t* pid, float kp, float ki, float kd, float max_output)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->error = 0.0f;
    pid->last_error = 0.0f;
    pid->integral = 0.0f;
    pid->output = 0.0f;
    pid->max_output = max_output;
    pid->max_integral = PID_MAX_INTEGRAL;  // 使用宏定义的积分限幅
}

/**
 * @brief PID控制计算
 */
static float PID_Calculate(PID_Controller_t* pid, float setpoint, float measured)
{
    // 计算误差
    pid->error = setpoint - measured;
    
    // 积分项计算（带限幅）
    pid->integral += pid->error;
    if (pid->integral > pid->max_integral) {
        pid->integral = pid->max_integral;
    } else if (pid->integral < -pid->max_integral) {
        pid->integral = -pid->max_integral;
    }
    
    // 微分项计算
    float derivative = pid->error - pid->last_error;
    
    // PID输出计算
    pid->output = pid->kp * pid->error + pid->ki * pid->integral + pid->kd * derivative;
    
    // 输出限幅
    if (pid->output > pid->max_output) {
        pid->output = pid->max_output;
    } else if (pid->output < -pid->max_output) {
        pid->output = -pid->max_output;
    }
    
    // 保存当前误差为下次的上次误差
    pid->last_error = pid->error;
    
    return pid->output;
}

/**
 * @brief PID控制计算 - 直接使用预处理后的误差
 * @param pid PID控制器指针
 * @param error 预处理后的误差值（已经过死区处理和安全检查）
 * @return PID输出值
 */
static float PID_CalculateWithError(PID_Controller_t* pid, float error)
{
    // 直接使用传入的误差，避免重复计算
    pid->error = error;

    // 积分项计算（带限幅）
    pid->integral += pid->error;
    if (pid->integral > pid->max_integral) {
        pid->integral = pid->max_integral;
    } else if (pid->integral < -pid->max_integral) {
        pid->integral = -pid->max_integral;
    }

    // 微分项计算
    float derivative = pid->error - pid->last_error;

    // PID输出计算
    pid->output = pid->kp * pid->error + pid->ki * pid->integral + pid->kd * derivative;

    // 输出限幅
    if (pid->output > pid->max_output) {
        pid->output = pid->max_output;
    } else if (pid->output < -pid->max_output) {
        pid->output = -pid->max_output;
    }

    // 保存当前误差为下次的上次误差
    pid->last_error = pid->error;

    return pid->output;
}

/**
 * @brief 图像坐标转换为舵机位置
 */
static uint16_t Position_ToServoPos(int16_t image_pos, uint8_t is_horizontal)
{
    uint16_t servo_pos;
    
    if (is_horizontal) {
        // 水平方向：图像X坐标转换为舵机位置
        servo_pos = (uint16_t)((float)image_pos * (SERVO_POS_MAX - SERVO_POS_MIN) / IMAGE_WIDTH + SERVO_POS_MIN);
    } else {
        // 垂直方向：图像Y坐标转换为舵机位置（注意Y轴可能需要反向）
        servo_pos = (uint16_t)(SERVO_POS_MAX - (float)image_pos * (SERVO_POS_MAX - SERVO_POS_MIN) / IMAGE_HEIGHT);
    }
    
    // 限幅
    if (servo_pos < SERVO_POS_MIN) servo_pos = SERVO_POS_MIN;
    if (servo_pos > SERVO_POS_MAX) servo_pos = SERVO_POS_MAX;
    
    return servo_pos;
}
