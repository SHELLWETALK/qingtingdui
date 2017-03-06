#include "Kalman.h"

//int16_t    Angle=0;               //未修改过的原程序
//float  Gyro_x=0;	
//float  Q_angle=1;//0.0001;  
//float  Q_gyro=0.3;//0.00003;
//float  R_angle=0.01;
//float  dt=0.001;//0.005;	                  
//float  C_0 = 1.0;
//float  Q_bias=0, Angle_err=0;
//float  PCt_0=0.0, PCt_1=0, E=0.0;
//float  K_0=0.0, K_1=0.0, t_0=0.0, t_1=0.0;
//float  Pdot[4] ={0,0,0,0};
//float  PP[2][2] = { { 1.0, 0 },{ 0, 1.0 } };          //未修改过的原程序

int16_t  Angle=0;//最终融合得到的角度
float  Gyro_x=0;	
float  Q_angle=0.068;
float  Q_gyro=0.0045;
float  R_angle=0.01;
float  dt=0.00047; 
float  C_0 = 1.0;
float  Q_bias=0, Angle_err=0;
float  PCt_0=0.0, PCt_1=0, E=0.0;
float  K_0=0.0, K_1=0.0, t_0=0.0, t_1=0.0;
float  Pdot[4] ={0,0,0,0};
float  PP[2][2] = { { 1.0, 0 },{ 0, 1.0 } };

void Kalman_Filter(int Gyro,int Accel)	
{
	Angle+=(Gyro - Q_bias) * dt;          
	
	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; 

	Pdot[1]= -PP[1][1];
	Pdot[2]= -PP[1][1];
	Pdot[3]= Q_gyro;
	
	PP[0][0] += Pdot[0] * dt;   
	PP[0][1] += Pdot[1] * dt;  
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err =Accel-Angle;
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	Angle	+= K_0 * Angle_err;	 
	Q_bias	+= K_1 * Angle_err;	 
	Gyro_x   = Gyro - Q_bias;
 
}

