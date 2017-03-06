#include "StandCar.h"

int32_t Stand_PWM ;



//ֱ��������
uint32_t Stand_ZeroDot = 14900;
float Stand_P = 0;
float Stand_D = 0;
//ֱ�������ƺ���
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

