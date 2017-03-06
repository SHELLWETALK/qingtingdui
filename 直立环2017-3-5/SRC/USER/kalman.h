#ifndef __Kalman_H__
#define __Kalman_H__ 

#include "sys.h"


extern int16_t Angle;//卡尔曼滤波之后的角度

extern float  Q_angle;
extern float  Q_gyro;
extern float  dt;

void Kalman_Filter(int Gyro,int Accel);


#endif

