#include "gpio.h"
#include "delay.h"
#include "Quick_Init.h"

//beep头文件
//IO 口
#define BEEP_PORT PTC

//引脚
#define BEEP_PIN  (18)

//位宏
#define BEEP      PCout(BEEP_PIN) 


void Beep_Init(void);
void Beep_dididi(void);

