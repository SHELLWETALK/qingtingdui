#ifndef __MONTER_H__
#define __MONTER_H__

#include "ftm.h"
#include "led.h"

typedef struct {
	
	int16_t SetSpeed; //设定速度
	int16_t NowSpeed; //当前速度
	
	//PID 参数
	float Kp;
	float Ki;
	float Kd;
	
	float Err;    //当前偏差
	float Err_1;  //上次偏差
	float Err_2;  //上上次偏差
	
	float DeltaOut; //输出的增量
	float Out;      //这次输出
	float Out_1;    //上次输出
	float MaxOut;   //最大占空比输出
	float MinOut;   //最小占空比输出
	
	uint32_t PWM_Pin1; //第一个PWM引脚
	uint32_t PWM_Pin2; //第二个PWM引脚
}MotPID;
extern MotPID Left_PID;
extern MotPID Right_PID;
extern MotPID *LeftMotP;
extern MotPID *RightMotP;

extern  uint32_t Left_Pin1;
extern  uint32_t Left_Pin2;

extern  uint32_t Right_Pin1;
extern  uint32_t Right_Pin2;

extern uint16_t Mot_Mod_Flag;
extern uint16_t Mot_TeleControl_Flag;

extern float Mot_TeleControl_Out_Left;
extern float Mot_TeleControl_Out_Right;

MotPID PID(MotPID *P);

void MOT_CTRL(MotPID *P);
void PID_Init(void);
MotPID PID(MotPID *P);
void MotToggle(void);
void MotTeleControl(uint16_t CtrFlag , float LeftOut , float RightOut);

#endif
