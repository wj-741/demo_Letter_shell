/**
 * **********************************************************************************
 * @copyright Copyright (c) 2023 Shaanxi Tianji Communication Technologies Co., Ltd.
 *                         
 * @file        bsp_shell.h   
 * @author      WangJun
 * @version     None
 * @date        2023-05-23     
 * @brief       None   
 * 
 * **********************************************************************************
 */

#ifndef __BSP_SHELL_H_
#define __BSP_SHELL_H_

#include <stdint.h>
#include "usart.h"

#define SHELL_USART     USART1
#define SHELL_SERIAL    huart1


extern char recv_buf;

void vShell_Init(void);


void vShellProcess(void);

#endif

