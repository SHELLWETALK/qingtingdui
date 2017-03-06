#include "mykey.h"

void Key_Init(void)
{
	GPIO_QuickInit(Key_Down_Port,Key_Down_Pin,GPIO_Mode_IPU,GPIO_IT_DISABLE,Bit_SET);
	GPIO_QuickInit(Key_MenuConfirm_Port, Key_MenuConfirm_Pin ,GPIO_Mode_IPU,GPIO_IT_DISABLE,Bit_SET);
	GPIO_QuickInit(Key_Up_Port, Key_Up_Pin ,GPIO_Mode_IPU,GPIO_IT_DISABLE,Bit_SET);
	GPIO_QuickInit(Key_Back_Port, Key_Back_Pin ,GPIO_Mode_IPU,GPIO_IT_DISABLE,Bit_SET);
}


//
//使用例程
// uint16_t Key_Value = Key_EOR_Value;
//  Key_Value = Key_Scan(); 
//  if(Key_Value != Key_EOR_Value)
//  {
//      UART_printf(HW_UART4,"fun Key ! 0x%x\n" , Key_Value);
//  }
//
uint16_t Key_Scan(void)
{
    if(Key_Down == 0)
    { 
        while(Key_Down == 0)//等待放开按键
        {
            if(Key_Up == 0)//同时按下多个按键，直接返回Key_EOR_Value
            {
                return Key_EOR_Value;
            }
            if(Key_MenuConfirm == 0)
            {
                return Key_EOR_Value;
            }
            if(Key_Back == 0)
            {
                return Key_EOR_Value;
            }           
        }
        return Key_Down_Value;
    }
    else if(Key_Up == 0)
    { 
        while(Key_Up == 0)//等待放开按键
        {
            if(Key_Down == 0)//同时按下多个按键，直接返回Key_EOR_Value
            {
                return Key_EOR_Value;
            }
            if(Key_MenuConfirm == 0)
            {
                return Key_EOR_Value;
            }
            if(Key_Back == 0)
            {
                return Key_EOR_Value;
            }           
        }
        return Key_Up_Value;
    }
    else if(Key_MenuConfirm == 0)
    { 
        while(Key_MenuConfirm == 0)//等待放开按键
        {
            if(Key_Up == 0)//同时按下多个按键，直接返回Key_EOR_Value
            {
                return Key_EOR_Value;
            }
            if(Key_Down == 0)
            {
                return Key_EOR_Value;
            }
            if(Key_Back == 0)
            {
                return Key_EOR_Value;
            }           
        }
        return Key_MenuConfirm_Value;
    }
    else if(Key_Back == 0)
    { 
        while(Key_Back == 0)//等待放开按键
        {
            if(Key_Up == 0)//同时按下多个按键，直接返回Key_EOR_Value
            {
                return Key_EOR_Value;
            }
            if(Key_MenuConfirm == 0)
            {
                return Key_EOR_Value;
            }
            if(Key_Down == 0)
            {
                return Key_EOR_Value;
            }           
        }
        return Key_Back_Value;
    }    
    else 
    {
        return Key_EOR_Value;
    }
    
}




