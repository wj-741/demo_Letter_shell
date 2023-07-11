/**
 * **********************************************************************************
 * @copyright Copyright (c) 2023 Shaanxi Tianji Communication Technologies Co., Ltd.
 *                         
 * @file        bsp_shell.c   
 * @author      WangJun
 * @version     None
 * @date        2023-07-05     
 * @brief       None   
 * 
 * **********************************************************************************
 */

#include "bsp_shell.h"

#include "usart.h"
#include "bsp_rtt.h"

/*---------------------- 端口定义 ----------------------*/


/*---------------------- 宏 定 义 ----------------------*/


/*---------------------- 结 构 体 ----------------------*/
Shell shell;

/*---------------------- 常    量 ----------------------*/


/*---------------------- 全局变量 ----------------------*/


/*---------------------- 局部变量 ----------------------*/
static char shellBuffer[SHELL_BUFF_LEN] = {0};

char recv_buf = 0;
/*---------------------- 函    数 ----------------------*/
/**
 * @brief  用户shell写
 * @param  data   数据
 * @param  len    数据长度
 * @return short  实际写入的数据长度
 */
short ShellWrite(char * data, unsigned short len)
{
    HAL_UART_Transmit(&SHELL_SERIAL, (uint8_t *)data, len, 0xFFFF);
    return len;
}


/**
 * @brief  用户shell读
 * @param  data   数据
 * @param  len    数据长度
 * @return short  实际读取的长度
 */
short ShellRead(char * data, unsigned short len)
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


/**
 * @brief  用户shell上锁
 * @param  shell  shell
 * @return int    0
 */
int ShellLock(Shell * shell)
{
    /* code */
    return 0;
}


/**
 * @brief  用户shell解锁
 * @param  shell  shell
 * @return int    0
 */
int ShellUnlock(Shell * shell)
{
    /* code */
    return 0;
}


/**
 * @brief  用户shell初始化
 */
void vShellInit(void)
{
    shell.write = ShellWrite;
    shell.read = ShellRead;
    shell.lock = ShellLock;
    shell.unlock = ShellUnlock;
    shellInit(&shell, shellBuffer, SHELL_BUFF_LEN);
}


/**
 * @brief     shell进程
 */
void vShellProcess(void)
{
    
}


/* 系统重启 */
void vReboot(void)
{
    rtt_printf(RTT_T_OS, "system restart\r\n");
    HAL_Delay(3000);
	HAL_NVIC_SystemReset();
	
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), reboot, vReboot, mcu reset);



/* 翻转led2 */
void vLed(void)
{
    rtt_printf(RTT_T_OS, "led2 toggle test\r\n");
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)| SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), led, vLed, led2 toggles);


/* 函数测试 */
void fun(int i, char ch, char *str)
{
    rtt_printf(RTT_T_OS, "input int: %d, char: %c, string: %s\r\n", i, ch, str);
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), fun, fun, test);
