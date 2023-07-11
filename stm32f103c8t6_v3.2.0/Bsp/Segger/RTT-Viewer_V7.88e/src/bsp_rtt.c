/*
 * **********************************************************************************
 * @copyright Copyright (c) 2023 Shaanxi Tianji Communication Technologies Co., Ltd.
 *
 * @file        bsp_rtt.c
 * @author      WangJun
 * @version     None
 * @date        2023-06-16
 * @brief       RTT Viewer Printf
 *
 * **********************************************************************************
 */

#include "bsp_rtt.h"


/*---------------------- 端口定义 ----------------------*/


/*---------------------- 宏 定 义 ----------------------*/


/*---------------------- 结 构 体 ----------------------*/


/*---------------------- 常    量 ----------------------*/


/*---------------------- 全局变量 ----------------------*/


/*---------------------- 局部变量 ----------------------*/


/*---------------------- 函    数 ----------------------*/


/*****************************************************************************
* @brief  : RTT Viewer打印
* @param  : Terminalx: 端口号
*		    sFormat: 参数
*			...:
* @retval : int
* @date   : 2023-06-16
* @note   : None
*****************************************************************************/
int rtt_printf(char Terminalx, const char * sFormat, ...)
{
    int r;

#if _RTT_VIEWER_EN_
    va_list ParamList;

    SEGGER_RTT_SetTerminal(Terminalx);
    va_start(ParamList, sFormat);

    r = SEGGER_RTT_vprintf(0, sFormat, &ParamList);

    SEGGER_RTT_printf(0, RTT_CTRL_TEXT_BRIGHT_WHITE"");

    va_end(ParamList);
#endif

    return r;
}



/*****************************************************************************
* @brief  : RTT Viewer初始化
* @param  : None
* @retval : None
* @date   : 2023-06-16
* @note   : None
*****************************************************************************/
void rtt_init(void)
{
	SEGGER_RTT_Init();
	
    /* 配置通道 0，上行配置*/
    SEGGER_RTT_ConfigUpBuffer(0, "RTT_UP", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);

    /* 配置通道 0，下行配置*/
    SEGGER_RTT_ConfigDownBuffer(0, "RTT_DW", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
}
