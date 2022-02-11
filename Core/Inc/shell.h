#ifndef __SHELL_H
#define __SHELL_H

#define UART huart1
#define Back_Display(UART, context)  HAL_UART_Transmit(&UART, (uint8_t *)&context, 1, 0xff) 
#define Recv_int_enable()            HAL_UART_Receive_IT(&UART, (uint8_t *)&charbuffer, 1)
/*
 * **************************************************************************
 * @param none none         
 * @brief shell工作状态枚举   
 * **************************************************************************
*/
typedef enum
{
    SHELL_OK = 0,
    SHELL_ERROR
}SHELL_STATUS;

/*
 * **************************************************************************
 * @brief 命令结构体
 * @param command 命令
 * @param description 该命令作用的描述
 * @param FunToExe 命令指向的将要执行的函数
 * @param next 单向链表中下一个命令的地址 
 * ***************************************************************************
*/
typedef struct _command
{
    //struct _command *prev;
    char* command;
    char* description;
    void (*FunToExe)(int argc, char **argv);
    struct _command *next;
    /* data */
}Command;

/*
 * ***************************************************************************
 * @name  shellexe
 * @brief 用于放入串口中断中用于处理外部输入的函数
 * ***************************************************************************
*/
void shellexe(void);

/*
 * ***************************************************************************
 * @name  commandExe
 * @brief 命令执行函数
 * @param &command 指向命令字符串的指针
 * ***************************************************************************
*/
SHELL_STATUS commandExe(char * command);

/*
 * ***************************************************************************
 * @name  DebugSend
 * @brief Debug格式信息发送函数
 * @param &msg 消息指针
 * ***************************************************************************
*/
SHELL_STATUS DebugSend(char *msg);

/*
 * ***************************************************************************
 * @name  MsgSend
 * @brief 通用信息发送函数
 * @param &msg 消息指针
 * ***************************************************************************
*/
int MsgSend(char * msg);


#endif

