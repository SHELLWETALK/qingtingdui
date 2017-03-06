#ifndef __CHSHELL_H_
#define __CHSHELL_H_	

#include "uart.h"
#include "led.h"
#include "kalman.h"
#include "monter.h"

#define CHS_PSWD 123    //CHSHELL����

//�ض��峣�����ݱ�������
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;
typedef unsigned long  u32;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
#include "stdio.h"           //֧��printf����
#define MAX_FNAME_LEN 	30	 //��������󳤶ȣ�Ӧ������Ϊ��С����������ĳ��ȡ�	
#define MAX_PARM 		    10	   //���Ϊ10������ ,�޸Ĵ˲���,�����޸�usmart_exe��֮��Ӧ.
#define PARM_LEN 		    200	 //���в���֮�͵ĳ��Ȳ�����PARM_LEN���ֽ�,ע�⴮�ڽ��ղ���Ҫ��֮��Ӧ(��С��PARM_LEN)

//����������Ϣ�ṹ��
struct T_CHS_PInfo
{
	uint8_t Type[MAX_PARM];    //���� 1 ���� 2 �ַ���
    u32 ParmData[MAX_PARM];    //������Ϣ:����������Ͳ������Ų�����ֵ��������ַ����Ͳ������Ų�����ʼ��ַ(ָ��ParmBuf)
	uint8_t OffSet[MAX_PARM];  //�������ַ�����ƫ��
	uint8_t Long[MAX_PARM];    //�����ĳ���
  uint8_t ParmBuf[PARM_LEN];     //�ַ����Ͳ�������ڴ���
};

//�������б�	 
struct T_CHS_FunTab
{
	void* func;			//����ָ��
	const uint8_t* name;	//������(���Ҵ�)
    const uint8_t* man;     //man ������Ϣ
};
//CHS_SHELL������
struct T_CHS_DEV
{
		struct T_CHS_FunTab *funs;	//������ָ��
		void (*init)(void);				//��ʼ��
	  uint16_t USART_STAT;
	  uint8_t fnum; //��������
	  uint8_t pnum; //��������
	  uint8_t id;   //����ID��
		uint8_t USART_BUF[MAX_FNAME_LEN+PARM_LEN];         //���ڽ��ջ�����
		struct T_CHS_PInfo PInfo;                          //������Ϣ�ṹ��
};
extern struct T_CHS_DEV CHS_Dev;				//��usmart_config.c���涨��
void CHS_Rev1(uint8_t ch);                   //��ֲ���� ����Ĵ��ڽ����ж��е���
uint8_t  CHS_Scan(void);                         //CHSִ��������
void CHS_Init(void);                    //CHS ��ʼ������
#endif
