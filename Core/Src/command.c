#include "command.h"
#include "stdio.h"
#include "main.h"
#include "string.h"
#include "stdlib.h"
extern UART_HandleTypeDef huart1;
extern char charbuffer;
extern Command *CMDiter;
extern char msgbuffer[500];
/*******************命令描述结构体*******************/
Command Clear =
{
	"clear",
	"Clear the screen",
	*clear,
	NULL
};

Command argDetect =
{
	"argtest",
	"test arg details.",
	*argtest,
	&Clear
};
Command KeyScan =
{
    "keyscan",
    "Display key value.",
    *keyscan,
    &argDetect
};

Command Command3 = 
{
    "hello3",
    "print \"Hello,world3\"",
    *hello3,
    &KeyScan
};

Command Command2 = 
{
    "hello2",
    "print \"Hello,world2\"",
    *hello2,
    &Command3
};

Command Version = 
{
    "version",
    "display the shell version information",
    *version,
    &Command2
};

Command CMDList =
{
    "cmdlist",
    "list the avaliable command and its description",
    *cmdlist,
    &Version
};

/*******************命令实现函数*******************/
void clear(int argc, char **argv)
{
    DebugSend("\x1B[2J\x1B[H");
}

void argtest(int argc, char **argv)
{
	sprintf(msgbuffer,"Arg count:%d",argc);
	MsgSend(msgbuffer);
	for(int i=0; i<argc; i++)
	{
		MsgSend(argv[i]);
		free(argv[i]);
	}
	memset(msgbuffer,0x00, strlen(msgbuffer));
	
}

void cmdlist(int argc, char **argv)
{
    char msgbuf[500];
    uint8_t i=1;
    uint8_t j=0;
    uint8_t k=0;
    CMDiter = &CMDList;
    while(CMDiter->next != NULL)
    {
        i++;
        CMDiter = CMDiter->next;
    }
    CMDiter = &CMDList;
    strcat(msgbuf, "Found Avaliable command:\r\nCommand:                description:");
    MsgSend(msgbuf);
    while(j!=i)
    {
        sprintf(msgbuf, "%d. %s",j+1,CMDiter->command);
        k=24-strlen(msgbuf);
        while(k--)
            strcat(msgbuf, " ");
        strcat(msgbuf, CMDiter->description);
        MsgSend(msgbuf);
        CMDiter = CMDiter->next;
        j++;
        memset(msgbuf, 0x00, strlen(msgbuf));
    };
    
}

void version(int argc, char **argv)
{
    MsgSend("\x1B[7mTaKeToRi Shell ver. 0.0.4");
    DebugSend("\x1B[0m");
}

void hello2(int argc, char **argv)
{
    MsgSend("Hello,world2");
}

void hello3(int argc, char **argv)
{
    MsgSend("Hello,world3");
}

void keyscan(int argc, char **argv)
{
    char value[5];
    MsgSend("键值检测:  ");
    while(1)
    {
        if(HAL_UART_Receive(&UART, (uint8_t *)&charbuffer, 1, 0xff) == HAL_OK)
        {
            if(charbuffer == 0x03)
            {
                MsgSend("退出...");
                break;
            }
            for(int i=0;i<strlen(value); i++)
                DebugSend("\x7F");

            sprintf(value,"%d",(int)charbuffer);
            
            DebugSend(value);
        }
    }
}

