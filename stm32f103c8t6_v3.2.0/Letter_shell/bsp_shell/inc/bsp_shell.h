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
/*
 * 申请内存大小取决于命令行输入的最大长度和历史命令记录的数量
 * 具体计算方式为(历史命令最大数量 + 1) * 命令行输入最大长度
 */
#define SHELL_BUFF_LEN  256

extern Shell shell;

/*---------------------- 函    数 ----------------------*/
void vShellInit(void);      /* shell init */
void vShellProcess(void);   
     
#ifdef __cplusplus
}
#endif

#endif
