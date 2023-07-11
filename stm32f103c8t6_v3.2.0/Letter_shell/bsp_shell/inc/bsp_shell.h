/**
 * **********************************************************************************
 * @copyright Copyright (c) 2023 Shaanxi Tianji Communication Technologies Co., Ltd.
 *                         
 * @file        bsp_shell.h   
 * @author      WangJun
 * @version     None
 * @date        2023-07-05     
 * @brief       None   
 * 
 * **********************************************************************************
 */

#ifndef __BSP_SHELL_H_
#define __BSP_SHELL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "shell.h"

#define SHELL_USART     USART1
#define SHELL_SERIAL    huart1

extern char recv_buf;
/*---------------------- 宏 定 义 ----------------------*/
#define SHELL_BUFF_LEN  512

extern Shell shell;

/*---------------------- 函    数 ----------------------*/
void vShellInit(void);      /* shell init */
void vShellProcess(void);   
     
#ifdef __cplusplus
}
#endif

#endif
