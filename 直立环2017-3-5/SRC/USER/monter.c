#include "monter.h"

uint32_t Left_Pin1 = FTM0_CH6_PD6;
uint32_t Left_Pin2 = FTM0_CH7_PD7;

uint32_t Right_Pin1 = FTM0_CH1_PA4;
uint32_t Right_Pin2 = FTM0_CH2_PA5;
	
MotPID Left_PID;
MotPID Right_PID;

MotPID *LeftMotP = &Left_PID;
MotPID *RightMotP = &Right_PID;

uint16_t Mot_Mod_Flag=0;
uint16_t Mot_TeleControl_Flag = 1;

float Mot_TeleControl_Out_Left = 0;
float Mot_TeleControl_Out_Right = 0;

//电机占空比设置
//*P :电机PID结构体
void MOT_CTRL(MotPID *P){
	
	if(P->Out > 0){
		
		FTM_PWM_ChangeDuty(P->PWM_Pin1, P->Out );
		FTM_PWM_ChangeDuty(P->PWM_Pin2, 0 );
	}
	else if(P->Out < 0){
		
		FTM_PWM_ChangeDuty(P->PWM_Pin1, 0 );
		FTM_PWM_ChangeDuty(P->PWM_Pin2, -P->Out );
	}
}

//电机PID结构体初始化
void PID_Init(void){
	
	//电机PID参数
	Left_PID.Kp = 80;Left_PID.Ki = 0.3;Left_PID.Kd = 0;	Left_PID.SetSpeed = 0; 
	
	Left_PID.MaxOut = 7000;
	Left_PID.MinOut = -7000;	
	Left_PID.PWM_Pin1 = Left_Pin1;
	Left_PID.PWM_Pin2 = Left_Pin2;
	
	Left_PID.Out = 3000;
	
	//电机PID参数
	Right_PID.Kp = 80;Right_PID.Ki = 0.3;Right_PID.Kd = 0;	Right_PID.SetSpeed = 0;
	
	Right_PID.MaxOut = 7000;
	Right_PID.MinOut = -7000;	
	Right_PID.PWM_Pin1 = Right_Pin1;
	Right_PID.PWM_Pin2 = Right_Pin2;

	Right_PID.Out = 3000;
}

//电机位置式PID函数

//电机前后翻转，速度递增递减
void MotToggle(void)
{
        if(Mot_Mod_Flag == 0 )
        {
            LeftMotP->Out += 100;
            RightMotP->Out += 100;
            
            if(LeftMotP->Out == 6000)
            {
                 Mot_Mod_Flag = 1;
            }
        }
        else if(Mot_Mod_Flag == 1)
        {
                LeftMotP->Out -= 100;
                RightMotP->Out -= 100;
            
                if(LeftMotP->Out == -6000)
                {
                        Mot_Mod_Flag = 0;
                }
        }
        MOT_CTRL(LeftMotP);
        MOT_CTRL(RightMotP);
}

//电机串口遥控运行
void MotTeleControl(uint16_t CtrFlag , float TeleControlLeftOut , float TeleControlRightOut)
{   
    if(Mot_TeleControl_Flag == 0)
    {
        MotToggle();
    }
    else if(Mot_TeleControl_Flag == 1)
    {
            LeftMotP->Out = TeleControlLeftOut;
            RightMotP->Out = TeleControlRightOut;
    }
}
