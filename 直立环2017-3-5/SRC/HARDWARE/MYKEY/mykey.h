#ifndef __key
#define __key

#include "sys.h"
#include "gpio.h"
#include "uart.h"
#include "Quick_Init.h"


    
//定义一下四个按键
#define Key_Down            PBin(0)
#define Key_MenuConfirm     PBin(2)
#define Key_Up              PBin(4)
#define Key_Back            PBin(6)

//key端口
#define Key_Down_Port					PTB
#define Key_MenuConfirm_Port	PTB
#define Key_Up_Port						PTB
#define Key_Back_Port					PTB

//key引脚
#define Key_Down_Pin					0
#define Key_MenuConfirm_Pin		2
#define Key_Up_Pin						4
#define Key_Back_Pin					6

//定义一些按键被扫描到之后函数返回值的意义
#define Key_Down_Value              0x2222
#define Key_MenuConfirm_Value       0x4444
#define Key_Up_Value                0x5555
#define Key_Back_Value              0x6666

//返回值错误定义
#define Key_EOR_Value               0xaaaa





void Key_Init(void);//按键初始化的引脚是固定的的，如需同时修改key.c中的Key_Init()函数
uint16_t Key_Scan(void);


#endif
