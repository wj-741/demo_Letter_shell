/**
 * **********************************************************************************
 * @copyright Copyright (c) 2023 Shaanxi Tianji Communication Technologies Co., Ltd.
 *                         
 * @file        bsp_shell.c   
 * @author      WangJun
 * @version     None
 * @date        2023-05-23     
 * @brief       None   
 * 
 * **********************************************************************************
 */

#include "bsp_shell.h"

#include "shell.h"
#include <stdio.h>



/*---------------------- 端口定义 ----------------------*/


/*---------------------- 宏 定 义 ----------------------*/


/*---------------------- 结 构 体 ----------------------*/
Shell shell;

/*---------------------- 常    量 ----------------------*/


/*---------------------- 全局变量 ----------------------*/
char shellBuffer[512] = {0};

char recv_buf = 0;
/*---------------------- 局部变量 ----------------------*/


/*---------------------- 函    数 ----------------------*/

/*****************************************************************************
* @brief  : 用户shell写
* @param  : data: 数据
**			 len: 数据长度
* @retval : 实际写入的数据长度
* @author : 
* @date   : 2023-05-23
* @note   : 
*****************************************************************************/
short usShellWrite(char *data, unsigned short len)
{
    HAL_UART_Transmit(&SHELL_SERIAL, (uint8_t *)data, len, 0xFFFF);
    return len;
}


/*****************************************************************************
* @brief  : 用户shell读
* @param  : data: 数据
**			 len: 数据长度 
* @retval : 实际读取到
* @author : 
* @date   : 2023-05-23
* @note   : 
*****************************************************************************/
short usShellRead(char *data, unsigned short len)
{
    if(HAL_UART_Receive(&SHELL_SERIAL, (uint8_t *)data, 1, 0xFFFF) != HAL_OK)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*****************************************************************************
* @brief  : 串口回调函数
* @param  : huart: [输入/出] 
* @retval : 
* @author : 
* @date   : 2023-05-23
* @note   : 
*****************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == SHELL_USART)
    {
        shellHandler(&shell, recv_buf);
        HAL_UART_Receive_IT(&SHELL_SERIAL, (uint8_t*)&recv_buf, 1);
    }
}


/*****************************************************************************
* @brief  : shell初始化
* @param  : None
* @retval : 
* @author : 
* @date   : 2023-05-23
* @note   : 
*****************************************************************************/
void vShell_Init(void)
{
    HAL_UART_Receive_IT(&SHELL_SERIAL, (uint8_t*)&recv_buf, 1);
    
    shell.read = usShellRead;
    shell.write = usShellWrite;
    shellInit(&shell, shellBuffer, 512);
}


/*****************************************************************************
* @brief  : shell进程
* @param  : None
* @retval : 
* @author : 
* @date   : 2023-05-23
* @note   : 
*****************************************************************************/
void vShellProcess(void)
{
    
}



/* 系统重启 */
void vReboot(void)
{
	HAL_NVIC_SystemReset();
	HAL_Delay(1000);
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), reboot, vReboot, MCU reset);



/* 翻转led2 */
void vLed(void)
{
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)| SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), led, vLed, led2 toggles);







