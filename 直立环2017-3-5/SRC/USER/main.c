#include "sys.h"
#include "delay.h"
#include "ftm.h"
#include "pit.h"
#include "adc.h"
#include "uart.h"
#include "gpio.h"
#include "chshell.h"
#include "beep.h"
#include "Quick_Init.h"
#include "led.h"
#include "key.h"
#include "mykey.h"
#include "monter.h"
#include "kalman.h"
#include "Serial_oscilloscope.h"

int main(void)
{	
	SystemClockSetup(ClockSource_EX50M,CoreClock_100M); //CoreClock_200M    CoreClock_100M
	DelayInit();
	LED_Init();	
	
	UART_DebugPortInit(UART4_RX_E24_TX_E25,115200);
	UART_ITConfig(UART4,UART_IT_RDRF,ENABLE);
	NVIC_EnableIRQ(UART4_RX_TX_IRQn);

	ADC_QuickInit(ADC1_SE1_DP1,ADC_PRECISION_16BIT,ADC_TRIGGER_SW);//初始化ADC
	ADC_QuickInit(ADC1_SE3_DP3,ADC_PRECISION_16BIT,ADC_TRIGGER_SW);

	FTM_QuickInit(Left_Pin1,5000,0);//初始化PWM  对其模式都是FTM_Mode_EdgeAligned
	FTM_QuickInit(Left_Pin2,5000,0);
	FTM_QuickInit(Right_Pin1,5000,0);//右轮的PWM  
	FTM_QuickInit(Right_Pin2,5000,0);	

	DisplayCPUInfo();
	
	PIT_QuickInit(PIT0,5);//初始化PIT0
	PIT_ITConfig(PIT0,PIT_IT_TIF,ENABLE);
	NVIC_EnableIRQ(PIT0_IRQn);
	
	PID_Init();
	
		CHS_Init();//超核SHELL
		
	while(1)
	{	  
		LED1 = !LED1;
		DelayMs(100);
	}
	
}


void assert_failed(uint8_t* file, uint32_t line)
{
	//断言失败检测
	UART_printf("assert_failed:line:%d %s\r\n",line,file);
	while(1);
}

