#ifndef __Serial_oscilloscope_H__
#define __Serial_oscilloscope_H__

#include "sys.h"
#include "uart.h"
#include "adc.h"
#include "kalman.h"
#include "delay.h"



extern unsigned char gdata_to_send[16];
   



void Data_Send(uint16_t ADC_value_Ay,uint16_t ADC_value_Gy);







#endif

