#include "chshell.h"

/*==================================================================================
	CH SHELL 是一个灵活的串口组件，利用它可以用串口调用程序中任何的参数 V1.0
    CH SHELL 使用注意： 1   函数及参数中间不允许随意加空格，否则，，，
                        2   函数名最多只能有 30 个字符,多余放不进缓冲区,缓冲区定义在chshell.h
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

//KalmanFilter 参数调试函数
//使用SHELL的形式调参方便快速
void CHS_KalmanFilter(float  QA, float QG, float D)
{
    Q_angle = QA;
    Q_gyro = QG;
    dt = D;
    LED2 = !LED2;//参数一旦改变就翻转小灯作为明显的现象
}

//电机遥控运行控制函数
//CtrFlag： 0取消遥控，此时后面两个参数无意义   1进入遥控状态
//OutLeft： 0-10000 表示电机的输出 PWM占空比从0%-100%
//OutRight： 0-10000 表示电机的输出 PWM占空比从0%-100%
void CHS_MotTeleControl(uint16_t CtrFlag ,float OutLeft ,float OutRight)
{
    Mot_TeleControl_Flag = CtrFlag;
    Mot_TeleControl_Out_Left = OutLeft;
    Mot_TeleControl_Out_Right = OutRight;
}

//复位停车
void CHS_RESET(uint32_t pswd)
{
    if( pswd == 123)
        NVIC_SystemReset();
    else 
        UART_printf("pswd不正确！\r\n");
    
}


//函数管理列表
//添加希望管理的函数
//在chshell.c的CHS_MAN_TABLE中添加帮助信息、说明信息
struct T_CHS_FunTab CHS_FunTab[]=
{
	(u32*) CHS_TestFun,         "uint8_t CHS_TestFun(uint8_t* str1,uint8_t num1,uint8_t* str2,uint8_t num2,uint8_t* str3)", "测试函数,无实际意义\r\n",
	(u32*) CHS_LEDControl,      "void CHS_LEDControl(uint8_t led,uint8_t state)",   "LED控制函数\r\n第一个参数:代表第几个LED灯\r\n第二个参数:0亮,1灭\r\n",
    (u32*) CHS_KalmanFilter,    "void CHS_KalmanFilter(float  QA, float QG, float D)",  "卡尔曼滤波参数修改函数,在内存中修改的,复位还原\r\n第一个参数:Q_angle,对angle的协方差，代表了对angle的信任度\r\n第二个参数:Q_gyro,对gyro的协方差，代表了对gyro的信任度\r\n第三个参数:dt,dt越大\r\n",
    (u32*) CHS_MotTeleControl,  "void CHS_MotTeleControl(uint16_t CtrFlag ,float OutLeft ,float OutRight)", "遥控电机运行状态\r\n第一个参数:是否控制模式,0关,1开\r\n第二个参数:左电机输出\r\n第三个参数:右电机输出\r\n",
    (u32*) CHS_RESET,           "void CHS_RESET(uint32_t pswd)",    "为了防止意外发生,在紧急情况下通过软件复位\r\n第一个参数:PSWD即密码,验证通过才复位\r\n",
};	

//Shell系统初始化
//实现 初始化系统系统
void CHS_Init(void)
{
	//在这里包含你的串口初始化函数
	UART_DebugPortInit(UART4_RX_E24_TX_E25,460800); //初始化调试串口 //默认 UART3 115200 在UART.H中定义
	UART_ITConfig(UART4,UART_IT_TDRE,ENABLE);
	NVIC_EnableIRQ(UART4_RX_TX_IRQn);
}

//CHSHELL控制管理器 无需修改
struct T_CHS_DEV CHS_Dev=
{
	  CHS_FunTab,
		CHS_Init,
		0,
		sizeof(CHS_FunTab)/sizeof(struct T_CHS_FunTab),//函数数量
};


