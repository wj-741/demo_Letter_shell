/**
 * **********************************************************************************
 * @copyright Copyright (c) 2023 Shaanxi Tianji Communication Technologies Co., Ltd.
 *                         
 * @file        bsp_shell_cfg.h   
 * @author      WangJun
 * @version     None
 * @date        2023-07-05     
 * @brief       None   
 * 
 * **********************************************************************************
 */

#ifndef __BSP_SHELL_CFG_H_
#define __BSP_SHELL_CFG_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* ST */
#if defined(STM32F103xB)
#include "stm32f1xx_hal.h"

#define Get_Tick()  HAL_GetTick()   // 重映射
#endif

#if defined(STM32F407xx) || defined(STM32F412xx)
#include "stm32f4xx_hal.h"

#define Get_Tick()  HAL_GetTick()   // 重映射
#endif

/* GD */
#if defined(GD32F407xx) || defined(GD32F427xx)
#include "systick.h"

// #define Get_Tick()  GetTick()       // 重映射

/* 需要在systick.c和systick.h文件中自行封装函数GetTick()*/
/**********************************************************
    * systick.c文件中添加如下代码：

        volatile static uint32_t ulTick;

        void vIncTick(void)
        {
            ulTick += 1;
        }

        uint32_t GetTick(void)
        {
            return ulTick;
        }

    * systick.h文件中添加如下代码：
        void vIncTick(void);
        uint32_t GetTick(void);

    * 说明：
        函数vIncTick()需要添加到 SysTick_Handler() 函数中
**********************************************************/
#endif

/* 系统相关 */
#define _USE_RTOS       0       /* 是否使用系统（FreeRTOS）：0禁用；1使用*/


#if (1 == _USE_RTOS)
#include "FreeRTOS.h"
#include "portable.h"
#endif

/**
 * @brief 是否使用shell伴生对象
 *        一些扩展的组件(文件系统支持，日志工具等)需要使用伴生对象
 */
#define     SHELL_USING_COMPANION       0


/**
 * @brief 支持shell尾行模式
 */
#define     SHELL_SUPPORT_END_LINE      1


/**
 * @brief 使用LF作为命令行回车触发
 *        可以和SHELL_ENTER_CR同时开启
 */
#define     SHELL_ENTER_LF              1

/**
 * @brief 使用CR作为命令行回车触发
 *        可以和SHELL_ENTER_LF同时开启
 */
#define     SHELL_ENTER_CR              1

/**
 * @brief 使用CRLF作为命令行回车触发
 *        不可以和SHELL_ENTER_LF或SHELL_ENTER_CR同时开启
 */
#define     SHELL_ENTER_CRLF            0

/**
 * @brief shell格式化输入的缓冲大小
 *        为0时不使用shell格式化输入
 * @note shell格式化输入会阻塞shellTask, 仅适用于在有操作系统的情况下使用
 */
#define     SHELL_SCAN_BUFFER          128

/**
 * @brief 获取系统时间(ms)
 *        定义此宏为获取系统Tick，如`HAL_GetTick()`
 * @note 此宏不定义时无法使用双击tab补全命令help，无法使用shell超时锁定
 */
#define     SHELL_GET_TICK()            Get_Tick()

/**
 * @brief 使用锁
 * @note 使用shell锁时，需要对加锁和解锁进行实现
 */
#define     SHELL_USING_LOCK            1

/**
 * @brief shell内存分配
 *        shell本身不需要此接口，若使用shell伴生对象，需要进行定义
 */
#define     SHELL_MALLOC(size)          pvPortMalloc(size)

/**
 * @brief shell内存释放
 *        shell本身不需要此接口，若使用shell伴生对象，需要进行定义
 */
#define     SHELL_FREE(obj)             vPortFree(obj)

#ifdef __cplusplus
}
#endif

#endif
