﻿#ifndef __CHSHELL_H_
#define __CHSHELL_H_	

#include "uart.h"
#include "led.h"
#include "kalman.h"
#include "monter.h"

//重定义常用数据变量类型
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;
typedef unsigned long  u32;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
#include "stdio.h"           //支持printf函数
#define MAX_FNAME_LEN 	30	 //函数名最大长度，应该设置为不小于最长函数名的长度。	
#define MAX_PARM 		    10	   //最大为10个参数 ,修改此参数,必须修改usmart_exe与之对应.
#define PARM_LEN 		    200	 //所有参数之和的长度不超过PARM_LEN个字节,注意串口接收部分要与之对应(不小于PARM_LEN)

//函数参数信息结构体
struct T_CHS_PInfo
{
	uint8_t Type[MAX_PARM];    //类型 1 数字 2 字符串
  u32 ParmData[MAX_PARM];    //参数信息:如果是数字型参数则存放参数的值，如果是字符串型参数则存放参数起始地址(指向ParmBuf)
	uint8_t OffSet[MAX_PARM];  //参数在字符串中偏移
	uint8_t Long[MAX_PARM];    //参数的长度
  uint8_t ParmBuf[PARM_LEN];     //字符串型参数存放内存区
};

//函数名列表	 
struct T_CHS_FunTab
{
	void* func;			//函数指针
	const uint8_t* name;    //函数名(查找串)
    const uint8_t* man;     //函数帮助信息   
};
//CHS_SHELL管理器
struct T_CHS_DEV
{
		struct T_CHS_FunTab *funs;	//函数名指针
		void (*init)(void);			//初始化
	  uint16_t USART_STAT;
	  uint8_t fnum; //函数数量
	  uint8_t pnum; //参数数量
	  uint8_t id;   //函数ID号
		uint8_t USART_BUF[MAX_FNAME_LEN+PARM_LEN];         //串口接收缓冲区
		struct T_CHS_PInfo PInfo;                          //参数信息结构体
};
extern struct T_CHS_DEV CHS_Dev;				//在usmart_config.c里面定义
void CHS_Rev1(uint8_t ch);                   //移植函数 在你的串口接收中断中调用
uint8_t  CHS_Scan(void);                         //CHS执行主函数
void CHS_Init(void);                    //CHS 初始化函数
#endif
