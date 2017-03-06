﻿/**
  ******************************************************************************
  * @file    wdog.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   超核K60固件库 看门狗驱动
  ******************************************************************************
  */
#include "wdog.h"
#include "sys.h"
/***********************************************************************************************
 功能：看门狗初始化
 形参：FeedInterval: 看门狗复位间隔时间 单位为FeedInterval  
 返回：0
 详解：看门狗初始化
************************************************************************************************/
void WDOG_Init(uint16_t FeedInterval)
{
	uint32_t Value;
	//写入钥匙
	WDOG->UNLOCK = 0xC520u;
	WDOG->UNLOCK = 0xD928u;  
	//默认选择BusClock  设置分频器，设置值为8
	WDOG->PRESC = WDOG_PRESC_PRESCVAL(7);
	Value = CPUInfo.BusClock/8;
  Value = ((Value/1000)*FeedInterval);
	WDOG->TOVALH = (Value&0xFFFF0000)>>16;
	WDOG->TOVALL = (Value&0x0000FFFF)>>0;
	//开启看门狗
	WDOG->STCTRLH |= 0x0001u;
}
/***********************************************************************************************
 功能：关闭看门狗 
 形参：0
 返回：0
 详解：关闭看门狗 
************************************************************************************************/
void WDOG_Close(void)
{
	//写入钥匙
	WDOG->UNLOCK=0xC520u;
	WDOG->UNLOCK=0xD928u;
	//关闭看门狗
	WDOG->STCTRLH&=~0x0001u;
}
/***********************************************************************************************
 功能：开启看门狗
 形参：0
 返回：0
 详解：开启看门狗
************************************************************************************************/
void WDOG_Open(void)
{
	//写入钥匙
	WDOG->UNLOCK=0xC520u;
	WDOG->UNLOCK=0xD928u;  
	//打开看门狗
	WDOG->STCTRLH|=0x0001u;
}
/***********************************************************************************************
 功能：看门狗喂狗
 形参：0
 返回：0
 详解：看门狗喂狗
************************************************************************************************/
void WDOG_Feed(void)
{
	//喂狗
	WDOG->REFRESH=0xA602u; 
	WDOG->REFRESH=0xB480u; //喂看门狗，参考k10手册504页。
}
