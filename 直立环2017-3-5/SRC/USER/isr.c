#include "isr.h"


void UART4_RX_TX_IRQHandler(void)
{
	uint8_t ch;
    NVIC_DisableIRQ(PIT0_IRQn);	
	//中断发送处理过程
	//UART_SendDataIntProcess(UART4);
	
	//如果成功接收到了数据
	if(UART_ReceiveData(UART4,&ch))
	{
		//把接收到的信息发送回去
		//UART_SendData(UART4,ch);
        CHS_Rev1(ch);
	}
	NVIC_EnableIRQ(PIT0_IRQn);
}



void PIT0_IRQHandler(void)
{
	NVIC_DisableIRQ(UART4_RX_TX_IRQn);

	ADC_Gy = ADC_GetConversionValue(ADC1_SE3_DP3) - 26810;// 1.35v / 3.3v * 65536
	ADC_Ay = ADC_GetConversionValue(ADC1_SE1_DP1);

	Kalman_Filter(ADC_Gy,ADC_Ay);
	Data_Send(ADC_Ay,ADC_Gy);
	LED2 = !LED2;

	Stand_PWM = Stand_Control();

	Left_PID.Out  =  Stand_PWM ;
	Right_PID.Out  =  Stand_PWM ;

	MOT_CTRL(LeftMotP);
	MOT_CTRL(RightMotP);
    
	PIT_ClearITPendingBit(PIT0,PIT_IT_TIF);
		NVIC_EnableIRQ(UART4_RX_TX_IRQn);
}

