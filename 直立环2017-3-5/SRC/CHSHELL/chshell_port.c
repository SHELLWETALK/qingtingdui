#include "chshell.h"

/*==================================================================================
	CH SHELL ��һ�����Ĵ�������������������ô��ڵ��ó������κεĲ��� V1.0
    ע�⣺1�������м䲻׼�пո��޸�λ��chshell.c�����Ӧ�ͺ���
          2�����������30���ַ����޸�λ��chshell.h�ĺ궨��
===================================================================================*/
//���������Ĵ�������ͷ�ļ�
//1��demo ���Ժ���
uint8_t CHS_TestFun(uint8_t* str1,uint8_t num1,uint8_t* str2,uint8_t num2,uint8_t* str3)
{
	UART_printf("����TestFun����\r\n");
	UART_printf("����1: %s\r\n",str1);
	UART_printf("����2: %d\r\n",num1);
	UART_printf("����3: %s\r\n",str2);
	UART_printf("����4: %d\r\n",num2);
	UART_printf("����5: %s\r\n",str3);
	return 100;
}

void CHS_LEDControl(uint8_t led,uint8_t state)
{
	switch(led)
	{
		case 1:
			LED1 = state;
			break;
		case 2:
			LED2 = state;
			break;
		case 3:
			LED3 = state;
			break;
		case 4:
			LED4 = state;
			break;
		default:break;
	}
	
}

void CHS_KalmanFilter(uint32_t QA, uint32_t QG, uint32_t D)
{
    Q_angle = 0.000001*QA;
    Q_gyro=0.000001*QG;
    dt=0.000001*D;
    LED2=!LED2;
}

void CHS_MotTeleControl(uint16_t CtrFlag, float OutLeft, float OutRight)
{
    Mot_TeleControl_Flag = CtrFlag;
    Mot_TeleControl_Out_Left =OutLeft;
    Mot_TeleControl_Out_Right =OutRight;
}

void CHS_RESET(uint32_t pswd)
{
    if(pswd == CHS_PSWD)
        NVIC_SystemReset();
    else 
        UART_printf("pswd����ȷ!\r\n");
}

void CHS_ShowKalman()//δд���޲����������������������
{
    LED2 =!LED2;
}
//���������б�
//���ϣ������ĺ���
struct T_CHS_FunTab CHS_FunTab[]=
{
	(u32*) CHS_TestFun,         "uint8_t CHS_TestFun(uint8_t* str1,uint8_t num1,uint8_t* str2,uint8_t num2,uint8_t* str3)",     "���Ժ���",
	(u32*) CHS_LEDControl,      "void CHS_LEDControl(uint8_t led,uint8_t state)",                                               "LED���ƺ���",
    (u32*) CHS_MotTeleControl,  "void CHS_MotTeleControl(uint16_t CtrFlag, float OutLeft, float OutRight)",                     "���ң�غ���",
    (u32*) CHS_RESET,           "void CHS_RESET(uint32_t pswd)",                                                                "Զ�������λ",
    (u32*) CHS_ShowKalman,      "void CHS_ShowKalman(void)",                                                                    "������ʾKalman�Ĳ���ֵ",
    (u32*) CHS_KalmanFilter,    "void CHS_KalmanFilter(uint32_t QA, uint32_t QG, uint32_t D)",                                  "���ڴ����޸�kalman����,,,�����������Ϣ��ʧCHS_Dev.PInfo.ParmData�����Ͳ���float",
};	

//Shellϵͳ��ʼ��
//ʵ�� ��ʼ��ϵͳϵͳ
void CHS_Init(void)
{
    //�����������Ĵ��ڳ�ʼ������
	  UART_DebugPortInit(UART4_RX_E24_TX_E25,115200); //��ʼ�����Դ��� //Ĭ�� UART3 115200 ��UART.H�ж���
	  //UART_ITConfig(UART4,UART_IT_TDRE,ENABLE);
	  //NVIC_EnableIRQ(UART4_RX_TX_IRQn);
}

//CHSHELL���ƹ����� �����޸�
struct T_CHS_DEV CHS_Dev=
{
	  CHS_FunTab,
		CHS_Init,
		0,
		sizeof(CHS_FunTab)/sizeof(struct T_CHS_FunTab),//��������
};


