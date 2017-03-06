/**
  ******************************************************************************
  * @file    led.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核原子核核心板 BSP构件 LED驱动
  ******************************************************************************
  */
#ifndef __LED_H__
#define __LED_H__

#include "gpio.h"

#ifdef __cplusplus
 extern "C" {
#endif

//LED头文件
//IO 口
#define LED1_PORT PTC
#define LED2_PORT PTD
#define LED3_PORT PTE
#define LED4_PORT PTA
//引脚
#define LED1_PIN  (0)
#define LED2_PIN  (15)
#define LED3_PIN  (26)
#define LED4_PIN  (17)
//位宏
#define LED1      PCout(LED1_PIN) 
#define LED2      PDout(LED2_PIN) 
#define LED3      PEout(LED3_PIN) 
#define LED4      PAout(LED4_PIN) 

//本构件所实现的函数接口列表
void LED_Init(void);

#ifdef __cplusplus
}
#endif

#endif
