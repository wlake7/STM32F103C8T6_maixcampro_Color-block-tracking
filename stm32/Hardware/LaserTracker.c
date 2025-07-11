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
 * - 重大更新：将控制目标从0-1000位置值改为0°-240°角度值
 *   像素误差 -> 角度误差 -> PID控制 -> 角度增量 -> 角度限幅 -> 转换为0-1000发送
 *   优势：更直观的角度控制，更精确的转换关系，更合理的PID参数
 * - 所有调试参数使用宏定义，便于调试和优化
 * - 增加安全检查和保护机制
 * - 优化OLED显示，显示角度误差、PID输出和舵机角度
 * - 支持调试开关，便于性能优化
 */

/* 全局激光追踪系统状态 */
static LaserTracker_t g_laser_tracker;



/* 内部函数声明 */
static void PID_Init(PID_Controller_t* pid, float kp, float ki, float kd, float max_output);
static float PID_Calculate(PID_Controller_t* pid, float setpoint, float measured);
static float PID_CalculateWithError(PID_Controller_t* pid, float error, float dt);
static uint16_t Angle_ToServoPos(float angle);

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

    // 设置舵机初始角度为中心
    g_laser_tracker.servo_h_angle = SERVO_ANGLE_CENTER;
    g_laser_tracker.servo_v_angle = SERVO_ANGLE_CENTER;

    // 等待系统稳定
    Delay_ms(1000);

    // 舵机回到中心角度
    OLED_ShowString(4, 1, "Centering servo");
    uint16_t center_pos_h = Angle_ToServoPos(g_laser_tracker.servo_h_angle);
    uint16_t center_pos_v = Angle_ToServoPos(g_laser_tracker.servo_v_angle);
    ServoBoard_MoveHV(center_pos_h, center_pos_v, 1000);
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
        uint32_t current_tick = System_GetTick();
        float dt = (float)(current_tick - g_laser_tracker.last_update_time) / 1000.0f;
        g_laser_tracker.last_update_time = current_tick;
        
        // 如果dt为0或过大，则跳过本次控制，防止异常
        if (dt <= 0.0f || dt > 0.5f) {
            return;
        }
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

        // 将像素误差转换为角度误差
        float angle_error_h = error_x * PIXEL_TO_ANGLE_GAIN_H;
        float angle_error_v = error_y * PIXEL_TO_ANGLE_GAIN_V;

        // 使用PID控制算法 - 直接传入角度误差
        float pid_output_h = PID_CalculateWithError(&g_laser_tracker.pid_h, angle_error_h, dt);
        float pid_output_v = PID_CalculateWithError(&g_laser_tracker.pid_v, angle_error_v, dt);

        // 将PID输出转换为舵机角度增量
        float h_angle_increment = -pid_output_h * SERVO_RESPONSE_GAIN;
        float v_angle_increment = -pid_output_v * SERVO_RESPONSE_GAIN;

        // 限制单次角度增量，防止过大跳跃
        if (h_angle_increment > MAX_SERVO_INCREMENT) h_angle_increment = MAX_SERVO_INCREMENT;
        if (h_angle_increment < -MAX_SERVO_INCREMENT) h_angle_increment = -MAX_SERVO_INCREMENT;
        if (v_angle_increment > MAX_SERVO_INCREMENT) v_angle_increment = MAX_SERVO_INCREMENT;
        if (v_angle_increment < -MAX_SERVO_INCREMENT) v_angle_increment = -MAX_SERVO_INCREMENT;

        // 更新舵机角度（增量控制）
        float new_h_angle = g_laser_tracker.servo_h_angle + h_angle_increment;
        float new_v_angle = g_laser_tracker.servo_v_angle + v_angle_increment;

        // 安全角度限幅 - 使用宏定义的安全范围
#if ENABLE_SAFETY_CHECK
        if (new_h_angle < SERVO_SAFE_MIN) new_h_angle = SERVO_SAFE_MIN;
        if (new_h_angle > SERVO_SAFE_MAX) new_h_angle = SERVO_SAFE_MAX;
        if (new_v_angle < SERVO_SAFE_MIN) new_v_angle = SERVO_SAFE_MIN;
        if (new_v_angle > SERVO_SAFE_MAX) new_v_angle = SERVO_SAFE_MAX;
/*
#else
        // 基本角度限幅
        if (new_h_angle < SERVO_ANGLE_MIN) new_h_angle = SERVO_ANGLE_MIN;
        if (new_h_angle > SERVO_ANGLE_MAX) new_h_angle = SERVO_ANGLE_MAX;
        if (new_v_angle < SERVO_ANGLE_MIN) new_v_angle = SERVO_ANGLE_MIN;
        if (new_v_angle > SERVO_ANGLE_MAX) new_v_angle = SERVO_ANGLE_MAX;
*/
#endif

        // 更新舵机角度
        g_laser_tracker.servo_h_angle = new_h_angle;
        g_laser_tracker.servo_v_angle = new_v_angle;

        // 将角度转换为控制板需要的位置值并发送舵机控制命令
        uint16_t servo_h_pos = Angle_ToServoPos(g_laser_tracker.servo_h_angle);
        uint16_t servo_v_pos = Angle_ToServoPos(g_laser_tracker.servo_v_angle);
        ServoBoard_MoveHV(servo_h_pos, servo_v_pos, SERVO_MOVE_TIME);

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

            // 第3行：显示角度误差和PID输出
            OLED_ShowString(3, 1, "AE:");
            OLED_ShowSignedNum(3, 4, (int32_t)angle_error_h, 2);
            OLED_ShowString(3, 6, ",");
            OLED_ShowSignedNum(3, 7, (int32_t)angle_error_v, 2);
            OLED_ShowString(3, 10, "P:");
            OLED_ShowSignedNum(3, 12, (int32_t)pid_output_h, 2);
            OLED_ShowString(3, 14, ",");
            OLED_ShowSignedNum(3, 15, (int32_t)pid_output_v, 2);

            // 第4行：显示舵机角度
            OLED_ShowString(4, 1, "Angle:");
            OLED_ShowNum(4, 7, (uint32_t)g_laser_tracker.servo_h_angle, 3);
            OLED_ShowString(4, 10, ",");
            OLED_ShowNum(4, 11, (uint32_t)g_laser_tracker.servo_v_angle, 3);
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
        // 停止追踪时回到中心角度
        g_laser_tracker.servo_h_angle = SERVO_ANGLE_CENTER;
        g_laser_tracker.servo_v_angle = SERVO_ANGLE_CENTER;
        uint16_t center_pos_h = Angle_ToServoPos(g_laser_tracker.servo_h_angle);
        uint16_t center_pos_v = Angle_ToServoPos(g_laser_tracker.servo_v_angle);
        ServoBoard_MoveHV(center_pos_h, center_pos_v, 500);
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
 * @brief 获取舵机角度
 */
void LaserTracker_GetServoAngle(float* h_angle, float* v_angle)
{
    if (h_angle) *h_angle = g_laser_tracker.servo_h_angle;
    if (v_angle) *v_angle = g_laser_tracker.servo_v_angle;
}

/**
 * @brief 获取舵机位置 (兼容性函数，将角度转换为位置)
 */
void LaserTracker_GetServoPosition(uint16_t* h_pos, uint16_t* v_pos)
{
    if (h_pos) *h_pos = Angle_ToServoPos(g_laser_tracker.servo_h_angle);
    if (v_pos) *v_pos = Angle_ToServoPos(g_laser_tracker.servo_v_angle);
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
static float PID_CalculateWithError(PID_Controller_t* pid, float error, float dt)
{
    // 直接使用传入的误差，避免重复计算
    pid->error = error;

    // 积分项计算（带限幅）
    pid->integral += pid->error * dt;
    if (pid->integral > pid->max_integral) {
        pid->integral = pid->max_integral;
    } else if (pid->integral < -pid->max_integral) {
        pid->integral = -pid->max_integral;
    }

    // 微分项计算
    float derivative = 0.0f;
    if (dt > 0.00001f) { // 避免除以零
        derivative = (pid->error - pid->last_error) / dt;
    }

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
 * @brief 角度转换为舵机控制板位置值
 * @param angle 舵机角度 (0°-240°)
 * @return 控制板位置值 (0-1000)
 *
 * 根据核心规则：控制角度范围0~1000对应0°~240°
 */
static uint16_t Angle_ToServoPos(float angle)
{
    // 角度限幅
    if (angle < SERVO_ANGLE_MIN) angle = SERVO_ANGLE_MIN;
    if (angle > SERVO_ANGLE_MAX) angle = SERVO_ANGLE_MAX;

    // 角度转换为0-1000位置值
    // 0° -> 0, 240° -> 1000
    uint16_t servo_pos = (uint16_t)((angle / SERVO_ANGLE_MAX) * 1000.0f);

    // 再次限幅确保安全
    if (servo_pos > 1000) servo_pos = 1000;

    return servo_pos;
}
