/*
 * common.c
 *
 *  Created on: Nov 21, 2015
 *      Author: MJY
 */
#include "Quick_Init.h"

/***********************************************************************************************
 功能：GPIO初始化
 形参：GPIOx:
			 @arg PTA:A端口
			 @arg PTB:B端口
			 @arg PTC:C端口
			 @arg PTD:D端口
			 @arg PTE:E端口
	  
	  GPIO_Pin:
       	     GPIO 端口号 GPIO_Pin_0 - GPIO_Pin_31 ： 设置引脚
      
      GPIO_Mode: 设置引脚工作模式
				GPIO_Mode_IN_FLOATING = 0x04,     //浮空输入
				GPIO_Mode_IPD = 0x05,             //下拉输入
				GPIO_Mode_IPU = 0x06,             //上拉输入
				GPIO_Mode_OOD = 0x07,             //开漏输出
				GPIO_Mode_OPP = 0x08,             //推挽输出 	     
       
       GPIO_IRQMode: 设置中断模式
				GPIO_IT_DISABLE = 0x00,              //禁止外部中断
				GPIO_IT_DMA_RISING = 0x01,           //DMA上升沿触发
				GPIO_IT_DMA_FALLING = 0x02,          //DMA下降沿触发
				GPIO_IT_DMA_RASING_FALLING = 0x03,   //DMA上升或下降沿触发
				GPIO_IT_LOW = 0x08,                  //逻辑0状态触发
				GPIO_IT_RISING = 0x09,               //上升沿触发
				GPIO_IT_FALLING = 0x0A,              //下降沿触发
				GPIO_IT_RISING_FALLING = 0x0B,       //上升或下降沿触发
				GPIO_IT_HIGH = 0x0C,                 //逻辑1触发
       
       GPIO 初始化结构，引脚初始化默认为低电平
 返回：0
 详解：GPIO_QuickInit(PTA,GPIO_Pin_14,GPIO_Mode_OPP,GPIO_IT_DISABLE);  设置PTA 14引脚为输出模式（初始状态为低电平）
************************************************************************************************/
void GPIO_QuickInit(GPIO_Type *GPIOx,uint16_t GPIO_Pin,GPIO_Mode_TypeDef GPIO_Mode,GPIO_IT_TypeDef GPIO_IRQMode,BitAction BitState){
	
		GPIO_InitTypeDef GPIO_InitSturct1;
		GPIO_InitSturct1.GPIO_Pin = GPIO_Pin;
		GPIO_InitSturct1.GPIO_InitState = BitState;
		GPIO_InitSturct1.GPIO_IRQMode = GPIO_IRQMode;
		GPIO_InitSturct1.GPIO_Mode = GPIO_Mode;
		GPIO_InitSturct1.GPIOx = GPIOx;
		GPIO_Init(&GPIO_InitSturct1);
}

/***********************************************************************************************
 功能：UART初始化
 形参：UARTxMAP:UART0_RX_PA1_TX_PA2: UART0 PA1引脚作为TX  PA2引脚作为RX
			
	  UART_BaudRate:设置波特率
       	     

 返回：0
 详解：UART_QuickInit(UART0_RX_PD6_TX_PD7,115200)  设置设置UART0波特率为115200 RX为PD6 TX为PD7
************************************************************************************************/
void UART_QuickInit(uint32_t UARTxMAP,uint32_t UART_BaudRate){
	
	UART_InitTypeDef UART_InitStruct1;
	UART_InitStruct1.UARTxMAP = UARTxMAP;
	UART_InitStruct1.UART_BaudRate = UART_BaudRate;
	
	UART_Init(&UART_InitStruct1);
	
}


/***********************************************************************************************
 功能：FTM初始化
 形参：FTMxMAP:FTM2_CH0_PB18: FTM2模块 通道0 在PB18引脚
			
	  Frequency:设置频率
	  InitalDuty：设置占空比 ( 0-10000 )
       	     

 返回：0
 详解：FTM_QuickInit(FTM2_CH0_PB18,10000,0);  FTM2模块 通道0 在PB18引脚 频率10k 占空比0
************************************************************************************************/
void FTM_QuickInit(uint32_t FTMxMAP,uint32_t Frequency,uint32_t InitalDuty){
	
	FTM_InitTypeDef FTM_InitStruct1;
	FTM_InitStruct1.Frequency = Frequency;
	FTM_InitStruct1.FTMxMAP = FTMxMAP;
	FTM_InitStruct1.InitalDuty = InitalDuty;
	FTM_InitStruct1.FTM_Mode = FTM_Mode_EdgeAligned;//FTM_Mode_CenterAligned 边沿对齐
	
	FTM_Init(&FTM_InitStruct1);	
}

/***********************************************************************************************
 功能：PIT初始化
 形参：PITx: PIT模块 号
 	 	 arg：PIT0
			  PIT1
			  PIT2
			  PIT3
	  PIT_Interval:定时时间 单位MS
	  
 返回：0
 详解：PIT_QuickInit(PIT0,100); 初始化PIT0模块，定时100MS进一次中断
************************************************************************************************/
void PIT_QuickInit(uint8_t PITx,uint32_t PIT_Interval){
	
	PIT_InitTypeDef PIT_InitStruct1;
	PIT_InitStruct1.PITx = PITx;          //PIT0通道
	PIT_InitStruct1.PIT_Interval = PIT_Interval;   
	PIT_Init(&PIT_InitStruct1);
}

/***********************************************************************************************
 功能：LPTMR初始化
 形参：LPTMxMap: LPTMR模块 号
 	 	 arg：LPTM_CH1_PA19 和50M晶振靠的太近干扰大慎用
			  LPTM_CH2_PC5
			  
	 LPTM_Mode:使用模式
	 	 arg:LPTM_Mode_PC_RISING,   //脉冲计数模式 上升沿计数
	 	 	 LPTM_Mode_PC_FALLING,  //脉冲计数模式 下降沿计数
	 	 	 LPTM_Mode_TC,          //TimerCounter模式
	 	 	 
	 LPTM_InitCompareValue:定时器模式下的初值(定时时间)，在计数模式下没用。
	 	 计时单位：MS
	 
	  
 返回：0
 详解：LPTMR_QuickInit(LPTM_CH2_PC5 , LPTM_Mode_PC_RISING , 200);
 	 使用计数模式，PTC5引脚上升沿计数。如果为定时模式则定时200MS
************************************************************************************************//*
void LPTMR_QuickInit(uint32_t LPTMxMap,LPTM_Mode_TpyeDef LPTM_Mode,uint32_t LPTM_InitCompareValue){
	
	LPTM_InitTypeDef LPTM_InitStruct1;
	LPTM_InitStruct1.LPTMxMap = LPTMxMap;
	LPTM_InitStruct1.LPTM_InitCompareValue = LPTM_InitCompareValue;          //在脉冲计数模式下无意义
	LPTM_InitStruct1.LPTM_Mode = LPTM_Mode,   //脉冲计数模式 上升沿计数
	LPTM_Init(&LPTM_InitStruct1);
}
*/


/*取绝对值*/
uint16_t ABS(int num){
	
	if(num >= 0) num = num;
	else if(num < 0) num = (-num);
	
	return (uint16_t)(num);
}

/***********************************************************************************************
 功能：I2C 快速初始化
 形参： I2CxMAP ：I2C模块号
 	 	 arg：I2C1_SCL_PE1_SDA_PE0
 	 	 	  I2C0_SCL_PB0_SDA_PB1
 	 	 	  I2C0_SCL_PB2_SDA_PB3
 	 	 	  I2C1_SCL_PC10_SDA_PC11
 	 	 	  
 	  I2C_ClockSpeed ：I2C通信速度
 	  	 arg： I2C_CLOCK_SPEED_50KHZ
 	  	 	  I2C_CLOCK_SPEED_100KHZ
 	  	 	  I2C_CLOCK_SPEED_150KHZ
 	  	 	  I2C_CLOCK_SPEED_200KHZ
 	  	 	  I2C_CLOCK_SPEED_250KHZ
 	  	 	  I2C_CLOCK_SPEED_300KHZ
 	 	 	  
 返回：0
 详解：0
************************************************************************************************//*
void I2C_QuickInit(uint32_t I2CxMAP,uint32_t I2C_ClockSpeed){
	
	I2C_InitTypeDef I2C_InitStruct1;
	I2C_InitStruct1.I2CxMAP = I2CxMAP;
	I2C_InitStruct1.I2C_ClockSpeed = I2C_ClockSpeed;
	I2C_Init(&I2C_InitStruct1);	
}
*/
//ADC快速初始化，软触发方式，16位精度，A
void ADC_QuickInit(uint32_t ADCxMap, uint32_t ADC_Precision, uint16_t ADC_TriggerSelect)
{
	ADC_InitTypeDef ADC_InitStruct0;
	
	ADC_InitStruct0.ADCxMap = ADCxMap;
	ADC_InitStruct0.ADC_Precision = ADC_Precision;
	ADC_InitStruct0.ADC_TriggerSelect = ADC_TriggerSelect;  //软件触发(A 通道可使用软/硬件触发 B 通道只能使用硬件触发) ADC_TRIGGER_SW / ADC_TRIGGER_HW
	ADC_Init(&ADC_InitStruct0);
	//SIM->SOPT7 |= SIM_SOPT7_ADC0TRGSEL_MASK;					//选择ADC的触发源为PIT0触发	
	//SIM->SOPT7 &= 0xFFFFFFF4;													//选择ADC的触发源为PIT0触发	
}

//PeripheralDMAReq : 外设DMA请求号
//例：配置UART4的DMA
// UART_DMAQuickInit(UART4_TRAN_DMAREQ);
/*
void UART_DMAQuickInit(uint8_t  PeripheralDMAReq)
{
	DMA_InitTypeDef DMA_InitStruct1;

	DMA_InitStruct1.Channelx = DMA_CH0;                         
	DMA_InitStruct1.DMAAutoClose = ENABLE;                      
	DMA_InitStruct1.EnableState = ENABLE;                       
	DMA_InitStruct1.MinorLoopLength = sizeof(gdata_to_send);   
	DMA_InitStruct1.PeripheralDMAReq  = PeripheralDMAReq; 		//外设DMA请求号  PeripheralDMAReq   UART4_TRAN_DMAREQ   
	DMA_InitStruct1.TransferBytes = 1;                         

	DMA_InitStruct1.DestBaseAddr = (uint32_t)&(UART4->D);       
	DMA_InitStruct1.DestDataSize = DMA_DST_8BIT;                
	DMA_InitStruct1.DestMajorInc = 0;                           
	DMA_InitStruct1.DestMinorInc = 0;                           
 
	DMA_InitStruct1.SourceBaseAddr = (uint32_t)gdata_to_send;
	DMA_InitStruct1.SourceDataSize = DMA_SRC_8BIT;
	DMA_InitStruct1.SourceMajorInc = 0;
	DMA_InitStruct1.SourceMinorInc = 1;
	DMA_Init(&DMA_InitStruct1);
}
*/
