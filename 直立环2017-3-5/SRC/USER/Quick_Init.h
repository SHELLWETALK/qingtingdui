/*
 * common.h
 *
 *  Created on: Nov 21, 2015
 *      Author: MJY
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "sys.h"
#include "gpio.h"
#include "pit.h"
#include "ftm.h"
#include "uart.h"
#include "adc.h"
#include "Serial_oscilloscope.h"

/********************** 函数声明 *****************************************************************/
void GPIO_QuickInit(GPIO_Type *GPIOx,uint16_t GPIO_Pin,GPIO_Mode_TypeDef GPIO_Mode,GPIO_IT_TypeDef GPIO_IRQMode,BitAction BitState);
void UART_QuickInit(uint32_t UARTxMAP,uint32_t UART_BaudRate);
void FTM_QuickInit(uint32_t FTMxMAP,uint32_t Frequency,uint32_t InitalDuty);
void PIT_QuickInit(uint8_t PITx,uint32_t PIT_Interval);
//void LPTMR_QuickInit(uint32_t LPTMxMap,LPTM_Mode_TpyeDef LPTM_Mode,uint32_t LPTM_InitCompareValue);
void I2C_QuickInit(uint32_t I2CxMAP,uint32_t I2C_ClockSpeed);
uint16_t ABS(int num);
void ADC_QuickInit(uint32_t ADCxMap, uint32_t ADC_Precision, uint16_t ADC_TriggerSelect);
void UART_DMAQuickInit(uint8_t  PeripheralDMAReq);
/***********************函数声明结束 **************************************************************/
#endif /* COMMON_H_ */
