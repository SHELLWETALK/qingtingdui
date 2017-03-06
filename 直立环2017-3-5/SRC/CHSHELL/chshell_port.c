#include "chshell.h"

/*==================================================================================
	CH SHELL 是一个灵活的串口组件，利用它可以用串口调用程序中任何的参数 V1.0
    注意：1、参数中间不准有空格，修改位置chshell.c添加相应和函数
          2、函数名最大30个字符，修改位置chshell.h改宏定义
===================================================================================*/
//这里包含你的串口驱动头文件
//1个demo 测试函数
uint8_t CHS_TestFun(uint8_t* str1,uint8_t num1,uint8_t* str2,uint8_t num2,uint8_t* str3)
{
	UART_printf("进入TestFun函数\r\n");
	UART_printf("参数1: %s\r\n",str1);
	UART_printf("参数2: %d\r\n",num1);
	UART_printf("参数3: %s\r\n",str2);
	UART_printf("参数4: %d\r\n",num2);
	UART_printf("参数5: %s\r\n",str3);
	return 100;
}

void CHS_LEDControl(uint8_t led,uint8_t state)
{
	switch(led)
	{
		case 1:
			LED1 = state;
			break;
		case 2:
			LED2 = state;
			break;
		case 3:
			LED3 = state;
			break;
		case 4:
			LED4 = state;
			break;
		default:break;
	}
	
}

void CHS_KalmanFilter(uint32_t QA, uint32_t QG, uint32_t D)
{
    Q_angle = 0.000001*QA;
    Q_gyro=0.000001*QG;
    dt=0.000001*D;
    LED2=!LED2;
}

void CHS_MotTeleControl(uint16_t CtrFlag, float OutLeft, float OutRight)
{
    Mot_TeleControl_Flag = CtrFlag;
    Mot_TeleControl_Out_Left =OutLeft;
    Mot_TeleControl_Out_Right =OutRight;
}

void CHS_RESET(uint32_t pswd)
{
    if(pswd == CHS_PSWD)
        NVIC_SystemReset();
    else 
        UART_printf("pswd不正确!\r\n");
}

void CHS_ShowKalman()//未写完无参数函数参数个数计算错误
{
    LED2 =!LED2;
}
//函数管理列表
//添加希望管理的函数
struct T_CHS_FunTab CHS_FunTab[]=
{
	(u32*) CHS_TestFun,         "uint8_t CHS_TestFun(uint8_t* str1,uint8_t num1,uint8_t* str2,uint8_t num2,uint8_t* str3)",     "测试函数",
	(u32*) CHS_LEDControl,      "void CHS_LEDControl(uint8_t led,uint8_t state)",                                               "LED控制函数",
    (u32*) CHS_MotTeleControl,  "void CHS_MotTeleControl(uint16_t CtrFlag, float OutLeft, float OutRight)",                     "电机遥控函数",
    (u32*) CHS_RESET,           "void CHS_RESET(uint32_t pswd)",                                                                "远程软件复位",
    (u32*) CHS_ShowKalman,      "void CHS_ShowKalman(void)",                                                                    "串口显示Kalman的参数值",
    (u32*) CHS_KalmanFilter,    "void CHS_KalmanFilter(uint32_t QA, uint32_t QG, uint32_t D)",                                  "在内存中修改kalman参数,,,参数输入后信息丢失CHS_Dev.PInfo.ParmData的类型不是float",
};	

//Shell系统初始化
//实现 初始化系统系统
void CHS_Init(void)
{
    //在这里包含你的串口初始化函数
	  UART_DebugPortInit(UART4_RX_E24_TX_E25,115200); //初始化调试串口 //默认 UART3 115200 在UART.H中定义
	  //UART_ITConfig(UART4,UART_IT_TDRE,ENABLE);
	  //NVIC_EnableIRQ(UART4_RX_TX_IRQn);
}

//CHSHELL控制管理器 无需修改
struct T_CHS_DEV CHS_Dev=
{
	  CHS_FunTab,
		CHS_Init,
		0,
		sizeof(CHS_FunTab)/sizeof(struct T_CHS_FunTab),//函数数量
};


