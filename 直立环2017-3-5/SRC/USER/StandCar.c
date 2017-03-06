#include "StandCar.h"

int32_t Stand_PWM ;



//直立环变量
uint32_t Stand_ZeroDot = 14900;
float Stand_P = 0;
float Stand_D = 0;
//直立环控制函数
int32_t Stand_Control(void)
{
	int32_t PWM = 0;
	PWM = (int32_t) (Stand_P*( Angle - Stand_ZeroDot)  + Stand_D * ADC_Gy );
	if(PWM > 9990 )
	{
		PWM = 9990;
	}
	else if(PWM < -9990 )
	{
		PWM = -9990;
	}
	
	return PWM;
}

