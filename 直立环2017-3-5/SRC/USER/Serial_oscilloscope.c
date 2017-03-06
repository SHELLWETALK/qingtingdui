/******************** LQ_K60_函数库 v1.0 ********************
 * 文件名           ：UART.c
 * 功能             ：设置UART口工作模式
 * 备注             ：官方例程上修改
 * 日期             ：2015-10-16
 * 实验平台         ：龙丘 k60DN512Z核心板 
 * 作者             ：龙丘技术 006
 * 淘宝店           ：https://longqiu.taobao.com
 * 龙丘智能车讨论群 ：202949437
*************************************************************/

#include "Serial_oscilloscope.h"



unsigned char gdata_to_send[16]={0};
void Data_Send(uint16_t ADC_value_Ay,uint16_t ADC_value_Gy)
{
    uint8_t _cnt=0;	
    uint8_t sum = 0;      
    uint8_t i;
    
    uint8_t data[23]={0};  
	
  data[_cnt++]=0xAA;
	data[_cnt++]=0xAA;
	data[_cnt++]=0x02;
	data[_cnt++]=0x00;
	data[_cnt++]=0x00;//(uint8_t)(&data[0]>>8);    //Ax     //高8位                 
	data[_cnt++]=0x00;//(uint8_t)data[0];                  //低8位
	data[_cnt++]=(uint8_t)(ADC_value_Ay>>8);    //Ay
	data[_cnt++]=(uint8_t)ADC_value_Ay;
	data[_cnt++]=0x00;                        //Az
	data[_cnt++]=0x00;
	data[_cnt++]=0x00;//(uint8_t)(data[3]>>8);    //Gx
	data[_cnt++]=0x00;//(uint8_t)data[3];
	data[_cnt++]=(uint8_t)(ADC_value_Gy>>8);    //Gy
	data[_cnt++]=(uint8_t)ADC_value_Gy;
	data[_cnt++]=0x00;                        //Gz
	data[_cnt++]=0x00;
	data[_cnt++]=0x00;//Mx
	data[_cnt++]=0x00;
	data[_cnt++]=(uint8_t)(Angle>>8);//My 但这里方便起见直接用作卡尔曼滤波之后的结果
	data[_cnt++]=(uint8_t)Angle;
	data[_cnt++]=0x00;//Mz
	data[_cnt++]=0x00;
		
	data[3] = _cnt-4;
	
	sum = 0;
        
	for(i=0;i<_cnt;i++)
		sum += data[i];
        
	data[_cnt++] = sum;
//     UART_printf("%d",_cnt);


	for(i=0;i<_cnt;i++)
	{
		//UART_SendData(UART4,data[i]);
        UART_printf("%c",data[i]);
		//UART_printf("have send %d data\n\r",i);
	}


}	
	
