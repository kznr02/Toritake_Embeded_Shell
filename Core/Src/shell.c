#include "shell.h"
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
char commandbuffer[100];//用于存储串口中输入的内容
char msgbuffer[500];
char *Chariter;//字符迭代器
char charbuffer;
int g_nIndex;
int esc_flag;
int isEnable;
Command *CMDiter;

extern UART_HandleTypeDef huart1;

extern Command CMDList;


void shellexe(void)
{
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    switch(charbuffer)
    {
        case 0x0D :{  //回车检测
            if(g_nIndex == 0)
            {
                DebugSend("\r\nHyc ->");
                break;
            }
            g_nIndex=0;
            commandExe(commandbuffer);
            memset(commandbuffer,0x00,strlen(commandbuffer));
            DebugSend("\r\nHyc ->");
            break;
        }
        case 0x08 :{  //退格检测
            if(g_nIndex == 0)
            {
                DebugSend("\x07");
                break;
            }
            else
            {
                commandbuffer[--g_nIndex] = 0x00;
                DebugSend("\x7F");
                break;
            }       
        }
        case 0x1B :{ //ESC键检测，实现ANSI额外字符指令
            esc_flag = 1;
        }
        default :{
            if(charbuffer >= 0x20 && charbuffer <= 0x7E)  //一般字符检测
            {
                if(g_nIndex < 100)
                {
                    commandbuffer[g_nIndex++] = charbuffer;
                    Back_Display(UART, charbuffer);
                    break;
                }
                else if(g_nIndex == 0)
                {
                    DebugSend("\r\nHyc ->");
                    break;
                } 
            }
        }
    };
    Recv_int_enable();
}

SHELL_STATUS commandExe(char * command)
{
    SHELL_STATUS ret;
    CMDiter = &CMDList;
    while(memcmp(CMDiter->command, command, strlen(CMDiter->command)) != 0)
    {
        CMDiter = CMDiter->next;
        if(CMDiter == NULL)
        {
            ret = DebugSend("\r\nCommand Not Found!");
            if(ret == SHELL_ERROR)
                Error_Handler();
            return SHELL_ERROR;
        }
    }
		
		int argc = 0;
		Chariter = command;
		while(strstr(Chariter, " -") != NULL)
		{
			argc++;
			Chariter = strstr(Chariter, " -") + 1;
		}
		Chariter = command;
		char *param[argc];
		char *cmd_begin;
		char *cmd_end;
		for(int i=0;i<argc;i++)
		{	
			cmd_begin = strstr(Chariter, " -");
			cmd_end = strstr(strstr(Chariter, " -")+1," -"); 
			if(cmd_end == NULL)
			{
				param[i] = (char *)malloc(strlen(cmd_begin));
				strncpy(param[i], strstr(Chariter, " -")+1, strlen(cmd_begin));
			}
			else
			{
				param[i] = (char *)malloc(cmd_end - cmd_begin);
				strncpy(param[i], strstr(Chariter, " -")+1, cmd_end - cmd_begin);
				Chariter = strstr(Chariter, " -")+1;
			}
		}
    (CMDiter->FunToExe)(argc, param);
		
    return SHELL_OK;
}

SHELL_STATUS DebugSend(char *msg)
{
    HAL_StatusTypeDef ret;
    char msg2send[100];
    sprintf(msg2send, "%s",msg);
    ret = HAL_UART_Transmit(&UART, (uint8_t *)msg2send, strlen(msg2send), 0xff);
    if(ret != HAL_OK)
        return SHELL_ERROR;
    else 
        return SHELL_OK;
}

int MsgSend(char * msg)
{
    HAL_StatusTypeDef ret;
    char msg2send[100];
    sprintf(msg2send, "\r\n%s",msg);
    ret = HAL_UART_Transmit(&UART, (uint8_t *)msg2send, strlen(msg2send), 0xff);
    if(ret != HAL_OK)
        return 0;
    else 
        return 1;
}

