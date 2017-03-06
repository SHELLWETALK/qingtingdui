#include "beep.h"


void Beep_Init(void)
{
	GPIO_QuickInit(BEEP_PORT,BEEP_PIN,GPIO_Mode_OPP,GPIO_IT_DISABLE,Bit_SET);
}

void Beep_dididi(void)
{
	BEEP = !BEEP;
	DelayMs(120);
	BEEP = !BEEP;
	DelayMs(120);
	BEEP = !BEEP;
	DelayMs(120);
	BEEP = !BEEP;
	DelayMs(120);
	BEEP = !BEEP;
	DelayMs(120);
	BEEP = !BEEP;
}

