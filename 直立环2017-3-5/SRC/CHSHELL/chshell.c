#include "chshell.h"
#include "uart.h"
/*==================================================================================
	CH SHELL ��һ�����Ĵ�������������������ô��ڵ��ó������κεĲ��� V1.0
===================================================================================*/
//�Ա��ַ���
uint8_t CHS_StrCmp(uint8_t*str1,uint8_t *str2)
{
	while(1)
	{
		if(*str1!=*str2)return 0;//�����
		if(*str1=='\0')break;//�Ա������.
		str1++;
		str2++;
	}
	return 1;//�����ַ������
}
//��str1������copy��str2  
void CHS_StrCopy(uint8_t*SercStr,uint8_t *DestStr)
{
	while(1)
	{										   
		*DestStr=*SercStr;	//����
		if(*SercStr=='\0')break;//���������.
		SercStr++;
		DestStr++;
	}
}

void CHS_MemCopy(uint8_t*Serc,uint8_t *Dest,uint16_t Num)
{
	while(Num--)
	{										   
		*Dest=*Serc;	//����
		Serc++;
		Dest++;
	}
}
//�õ��ַ����ĳ���(�ֽ�) 
uint8_t CHS_StrLen(uint8_t*str)
{
	uint8_t len=0;
	uint8_t *p= str;
	p=p;
	while(1)
	{							 
		if(*str=='\0')break;//���������.
		len++;
		str++;
	}
	return len;
}
//����ֵ:m^n�η�
u32 CHS_Pow(uint8_t m,uint8_t n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	   
//����ַ���
uint8_t CHS_ClearStr(uint8_t* str,uint8_t Num)
{
	while(Num--)
	{
		*str=' ';
		str++;
	}
	return 0;
}
//���ַ���תΪ����
//֧��16����ת��,����16������ĸ�����Ǵ�д��,�Ҹ�ʽΪ��0X��ͷ��.
//��֧�ָ��� 
//*str:�����ַ���ָ��
//*res:ת����Ľ����ŵ�ַ.
//����ֵ:0���ɹ�ת�����.����,�������.
//1,���ݸ�ʽ����.2,16����λ��Ϊ0.3,��ʼ��ʽ����.4,ʮ����λ��Ϊ0.
uint8_t CHS_Str2Num(uint8_t*str,u32 *res)
{
	u32 t;
	uint8_t bnum=0;	 //���ֵ�λ��
	uint8_t *p;		  
	uint8_t hexdec=10;//Ĭ��Ϊʮ��������
	p=str;
	*res=0;//����.
	while(1)
	{
		if((*p<='9'&&*p>='0')||(*p<='F'&&*p>='A')||(*p=='X'&&bnum==1))//�����Ϸ�
		{
			if(*p>='A')hexdec=16;	//�ַ����д�����ĸ,Ϊ16���Ƹ�ʽ.
			bnum++;					//λ������.
		}else if(*p=='\0')break;	//����������,�˳�.
		else return 1;				//��ȫ��ʮ���ƻ���16��������.
		p++; 
	} 
	p=str;			    //���¶�λ���ַ�����ʼ�ĵ�ַ.
	if(hexdec==16)		//16��������
	{
		if(bnum<3)return 2;			//λ��С��3��ֱ���˳�.��Ϊ0X��ռ��2��,���0X���治������,������ݷǷ�.
		if(*p=='0' && (*(p+1)=='X'))//������'0X'��ͷ.
		{
			p+=2;	//ƫ�Ƶ�������ʼ��ַ.
			bnum-=2;//��ȥƫ����	 
		}else return 3;//��ʼͷ�ĸ�ʽ����
	}else if(bnum==0)return 4;//λ��Ϊ0��ֱ���˳�.	  
	while(1)
	{
		if(bnum)bnum--;
		if(*p<='9'&&*p>='0')t=*p-'0';	//�õ����ֵ�ֵ
		else t=*p-'A'+10;				//�õ�A~F��Ӧ��ֵ	    
		*res+=t*CHS_Pow(hexdec,bnum);		   
		p++;
		if(*p=='\0')break;//���ݶ�������.	
	}
	return 0;//�ɹ�ת��
}

//���Һ����Ĳ��� ���뺯���Ĳ����ַ���
//���� �����ĸ���
uint8_t CHS_GetParmNum(uint8_t* str)
{
	uint8_t ParmNum=1;
	uint8_t IfStr=0;
	uint8_t ZeroParmTable1[]="()";
	uint8_t ZeroParmTable2[]="(void)";
	uint8_t ZeroParmTable3[]="(void);";
    uint8_t ZeroParmTable4[]="();";
    // 0�����ж�
	if(CHS_StrCmp(str,ZeroParmTable1) || CHS_StrCmp(str,ZeroParmTable2) || CHS_StrCmp(str,ZeroParmTable3) || CHS_StrCmp(str,ZeroParmTable4)) return 0;
	while(1)
	{
		if((*str==')'||*str=='\0')) break;
		if(*str==',' && IfStr==0) ParmNum++;
		if(*str=='"' && IfStr==1)
		{
			IfStr=0;
		}
		else if(*str=='"') IfStr=1;
		str++;
	}
	return ParmNum;
}

//����������Ϣ
//ֻ�����ڷ������ܵ�����������Ϣ ���ܷ�������
//���������Ϣ
uint8_t CHS_ParmProcess(uint8_t* str,struct T_CHS_DEV* CHS_Dev)
{
	uint8_t i;
	uint8_t ParmPos[MAX_PARM];
	uint8_t Pos=0;
	uint8_t Temp[PARM_LEN];
	u32 NumParm;
	uint8_t Results;

	//��һ�� ��������������Buffer�е�λ��
	for(i=1;i<CHS_Dev->pnum+1;i++)
	{
		if(CHS_Dev->PInfo.Type[i]==2)
		{
			ParmPos[i]=Pos;
			Pos+=CHS_Dev->PInfo.Long[i]+2;//ֻ�洢�ַ���
		}
	}
  //��������
	for(i=1;i<CHS_Dev->pnum+1;i++)
	{
		if(CHS_Dev->PInfo.Type[i]==1) //����
		{
			CHS_StrCopy(str+CHS_Dev->PInfo.OffSet[i],Temp);
			Temp[CHS_Dev->PInfo.Long[i]]='\0';
			Results=CHS_Str2Num(Temp,&NumParm);
			if(Results!=0) return 1;
			CHS_Dev->PInfo.ParmData[i]=NumParm;
		}
		else //�ַ���
		{
			CHS_StrCopy(str+CHS_Dev->PInfo.OffSet[i],Temp);
			Temp[CHS_Dev->PInfo.Long[i]]='\0';
			CHS_StrCopy(Temp,CHS_Dev->PInfo.ParmBuf+ParmPos[i]);
			CHS_Dev->PInfo.ParmData[i]=(u32)&(CHS_Dev->PInfo.ParmBuf)+ParmPos[i];
		}
	}
	return 0;
}
//��ú��������ڲ����ַ����е�ƫ�ƺͳ���
uint8_t CHS_GetParmInfo(uint8_t* str,struct T_CHS_DEV* CHS_Dev)
{
	uint8_t i=0;
	uint8_t j=0;
	uint8_t ParmNum=1;
	uint8_t IfStr=0;
	uint8_t len;
	uint8_t* OrgStrPtr=str;
	//��ò�������
	CHS_Dev->PInfo.OffSet[1]=1;
	while(1)
	{
		if((*str==')'||*str=='\0')) break;
		if(*str==',' && IfStr==0)
		{
			ParmNum++;
			CHS_Dev->PInfo.OffSet[ParmNum]=i+1;
		}
		if((*str>='0' && *str<='9') && IfStr==0)
		{
			CHS_Dev->PInfo.Type[ParmNum]=1;
		}
		if(*str=='"' && IfStr==1)
		{
				IfStr=0;
		}
		else if(*str=='"')//����" ��ʼ����string
		{
			IfStr=1;
			CHS_Dev->PInfo.Type[ParmNum]=2; //ȷ�����ַ�������
		}
		str++;
		i++;
		
	}
	//�жϲ����Ŀ�ʼλ��
	for(i=1;i<ParmNum+1;i++)
	{
		if(CHS_Dev->PInfo.Type[i]==2)CHS_Dev->PInfo.OffSet[i]++;
	}
	//��ʼλ��Ѱ�ҽ���
	i=0;
	str=OrgStrPtr;       //��ԭ�ַ���
	len=CHS_StrLen(str); //����ַ�������
	//���ÿ�������ĳ���
	for(i=1;i<ParmNum+1;i++)
	{
		str=OrgStrPtr+CHS_Dev->PInfo.OffSet[i];
		for(j=CHS_Dev->PInfo.OffSet[i];j<len;j++)
		{
			if(CHS_Dev->PInfo.Type[i]==1)
			{
				if(*str==',' || *str=='"' || *str==')') //Ѱ�ҽ�����־
				{
					CHS_Dev->PInfo.Long[i]=j-CHS_Dev->PInfo.OffSet[i];
					break;	
				}
			}
			else
			{
				if(*str=='"')
				{
					CHS_Dev->PInfo.Long[i]=j-CHS_Dev->PInfo.OffSet[i]; //��¼������Ϣ
					break;	
				}
			}
			str++;
		}
	}
	return 0;
	//���������Σ�����Buffer�����
}
//����ַ����Ƿ�Ϸ� ���ҷ��뺯�����ַ����Ͳ����ַ���
//str     Դ�ַ���
//FunName ���������ַ���
//FunParm ���������ַ���
uint8_t CHS_StrCheck(uint8_t* str,uint8_t* FunName,uint8_t* FunParm)
{
	uint8_t len;
	uint8_t* StrStartPtr=str; //Դ�ַ���ָ��
	uint8_t* p;
	uint8_t i=0;
	uint8_t FoverLeft=0;   //���ŵĸ���
	uint8_t FoverRight=0;  //���ŵĸ���
	uint8_t SpaceOffset=0; //��һ���ո�ǰ��ƫ��
	
    //�����ж�
	len=CHS_StrLen(str);
	if(len>(PARM_LEN+MAX_FNAME_LEN)) return 1;
	
    //man �����ж�
    if(*str == 'm')
    {
        str ++;
        if(*str == 'a')
        {
            str ++;
            if(*str == 'n')
            {
                str++;
                if(*str == ' ')
                {
                    CHS_MemCopy(str,FunName,4);
                    str ++;
                    CHS_StrCopy(str,FunParm);
                    return 2;
                }
            }
        }
    }
    str = StrStartPtr;//��ԭ�ַ���ָ��
    
    //�����ж�
	for(i=0;i<len;i++)
	{
		if(*str=='(')  FoverLeft++;
		if(*str==')')  FoverRight++;
		str++;
	}
	if(FoverLeft==0 || FoverRight==0 || FoverLeft!=FoverRight)  return 4;
	str=StrStartPtr; //��ԭ�ַ���ָ��
	
	for(i=0;i<len;i++)
	{
		if(*str=='(') break;
		str++;
	}
	FoverLeft=i;
	//������һ���ո񣬼���һ����ĸ�Ƿ�Ϊ�Ϸ���ĸ
	str=StrStartPtr;
	for(i=0;i<len;i++)
	{
		if(*str==' ' && (i<FoverLeft)) SpaceOffset=i+1;
		str++;
	}
	str=StrStartPtr;
	str=(str+SpaceOffset);
	p=str;
	if(!((*str>='a' && *str<='z')||(*str>='A' && *str<='Z')|| (*str=='_'))) return 5;
	//Ѱ�ҵ�һ��(
	str=StrStartPtr;
	for(i=0;i<len;i++)
	{
		if(*str=='(') break;
		str++;
	}
	str=p;
	CHS_MemCopy(str,FunName,i); //����FunName�ַ���
	CHS_StrCopy(str+i-SpaceOffset,FunParm);
	*(FunName+i-SpaceOffset)='\0';
	if(CHS_StrLen(FunName)>MAX_FNAME_LEN) return 6; //��ⳤ���Ƿ񳬳����
	if(CHS_StrLen(FunParm)>PARM_LEN)      return 6;
	return 0;
}
//�����
uint8_t *CHS_CMD_TABLE[]=
{
	"?",
	"help",
	"list",
};	
//��ִ�к���
uint8_t  CHS_Scan()
{
	uint8_t i=0;
	uint8_t Result=0;
	uint8_t len=0;
	uint8_t LocalFunName[MAX_FNAME_LEN];   //���غ��������ַ���
	uint8_t LocalFunParm[PARM_LEN];        //���ز��������ַ���
	uint8_t RecFunName[MAX_FNAME_LEN];     //���յ��ĺ��������ַ���
	uint8_t RecFunParm[PARM_LEN];          //���յ��ĺ��������ַ���
	if((CHS_Dev.USART_STAT&0x8000)==0) return 1;
	len=CHS_Dev.USART_STAT&0x3fff;	 //�õ��˴ν��յ������ݳ���
	CHS_Dev.USART_BUF[len]='\0';	   //��ĩβ���������. 
	Result=CHS_StrCheck(CHS_Dev.USART_BUF,RecFunName,RecFunParm); //��������ַ����Ƿ�Ϊ������ʽ������ǣ��������ƺͲ����ַ���
//Result�� 0��C���Ը�ʽ������
//         1���ȳ���
//         2 man ����    
//         3
//         4�����������������
//         5''���Ⱥ��治�Ǻ��������Ƿ�
//         6�ڿ������󳤶ȳ���

    if(Result == 2)
    {
        for(i=0;i<CHS_Dev.fnum ;i++)
        {
            CHS_StrCheck((uint8_t*) CHS_Dev.funs[i].name ,LocalFunName,LocalFunParm );
            if(CHS_StrCmp(LocalFunName,RecFunParm ))
            {
                UART_printf("man ");
                UART_printf("%s",RecFunParm);
                UART_printf("\r\n");
                UART_printf("%s",(uint8_t*)CHS_Dev.funs[i].man );
                UART_printf("\r\n");
                return 0;
            }
                
        }
    }
    if(Result!=0) //����C���Ժ�����ʽ������
	{
		for(i=0;i<3;i++)//֧��3��ϵͳָ��
		{
			if(CHS_StrCmp(CHS_Dev.USART_BUF,CHS_CMD_TABLE[i]))break;
		}
		switch(i)
		{					   
			case 0:
			case 1://����ָ��
				UART_printf("--------------------------CH SHELL V1.0------------------------ \r\n");
				UART_printf("    CHSHELL����YANDLD������һ�����ɵĴ��ڵ��Ի������,ͨ����,�� \r\n");
				UART_printf("����ͨ���������ֵ��ó���������κκ���,��ִ��.���,������������\r\n");
				UART_printf("�������������.�����������֧��6���������.���������ֻ����ַ���  \r\n");	  
				UART_printf("�Ա���:http://upcmcu.taobao.com\r\n");
				UART_printf("CH SHELL��3��ϵͳ����:\r\n"); 
				UART_printf("?:    ��ȡ������Ϣ\r\n");
				UART_printf("help: ��ȡ������Ϣ\r\n");
				UART_printf("list: ���õĺ����б�\r\n\n");
				UART_printf("�밴�ճ����д��ʽ���뺯�������������Իس�������.\r\n");    
				UART_printf("--------------------------YANDLD ------------------------- \r\n");
			case 2:
				UART_printf("\r\n");
				UART_printf("-------------------------�����嵥--------------------------- \r\n");
				for(i=0;i<CHS_Dev.fnum;i++)UART_printf("%s\r\n",CHS_Dev.funs[i].name);
				UART_printf("\r\n");
				return 0;
			default: 
				UART_printf("�޷�ʶ���ָ��\r\n");
				return 1;
		}
	}
	  //��鱾���Ƿ��д˺���
		for(i=0;i<CHS_Dev.fnum;i++) 
		{
			Result=CHS_StrCheck((uint8_t*)CHS_Dev.funs[i].name,LocalFunName,LocalFunParm);//�õ����غ���������������
			if(Result!=0)
			{
				UART_printf("���غ����������� %d\r\n",Result);
				return 2;//���ؽ�������
			}
			if(CHS_StrCmp(LocalFunName,RecFunName))//���뺯�����ͱ��غ�����ƥ��
			{
				CHS_Dev.id=i;//��¼����ID.
				break;//����.
			}	
		}
		if(i==CHS_Dev.fnum) //���뺯�����ͱ��غ������޷�ƥ��
		{
			UART_printf("�޷�ƥ�亯��\r\n");
			return 5;
		}
		//�����������Ƿ���ȷ
		if(CHS_GetParmNum(RecFunParm)!=CHS_GetParmNum(LocalFunParm))
		{
			UART_printf("�������벻��ȷ ����%d ����%d\r\n",CHS_GetParmNum(LocalFunParm),CHS_GetParmNum(RecFunParm));
			return 6;
		}
		
		CHS_Dev.pnum=CHS_GetParmNum(RecFunParm); //��ȡ�˴�Ҫִ�к����Ĳ�������
		CHS_GetParmInfo(RecFunParm,&CHS_Dev);    //��ò�����Ϣƫ�ƺʹ�С
		CHS_ParmProcess(RecFunParm,&CHS_Dev);   //��������Ϣ
		//�����ȷ ��ʼ��������
		UART_printf("\r\n%s(",RecFunName);//�����Ҫִ�еĺ�����
		for(i=1;i<CHS_Dev.pnum+1;i++) //����Ҫִ�еĲ���
		{
			if(CHS_Dev.PInfo.Type[i]==1) //����
			{
				UART_printf("%d",CHS_Dev.PInfo.ParmData[i]);
			}
			else  //�ַ���
			{
				UART_printf("%c",'"');			 
				UART_printf("%s",(uint8_t*)CHS_Dev.PInfo.ParmData[i]);
				UART_printf("%c",'"');
			}
			if(i!=CHS_Dev.pnum)UART_printf(",");
		}
		UART_printf(")\r\n");	
		//��ʼִ��
		switch(CHS_Dev.pnum)
		{
			case 0://�޲���(void����)											  
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)();
				UART_printf("FunRet: %d",Result);
				break;
	    case 1://��1������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1]);
				UART_printf("FunRet: %d",Result);
				break;
			case 2: //��2������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1],CHS_Dev.PInfo.ParmData[2]);
				UART_printf("FunRet: %d",Result);
				break;
			case 3: //��3������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1],CHS_Dev.PInfo.ParmData[2],CHS_Dev.PInfo.ParmData[3]);
				UART_printf("FunRet: %d",Result);
				break;
			case 4: //��4������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1],CHS_Dev.PInfo.ParmData[2],CHS_Dev.PInfo.ParmData[3],CHS_Dev.PInfo.ParmData[4]);
				UART_printf("FunRet: %d",Result);
				break;		
			case 5: //��5������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1],CHS_Dev.PInfo.ParmData[2],CHS_Dev.PInfo.ParmData[3],CHS_Dev.PInfo.ParmData[4],\
				CHS_Dev.PInfo.ParmData[5]);
				UART_printf("FunRet: %d",Result);
				break;		
			case 6: //��6������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1],CHS_Dev.PInfo.ParmData[2],CHS_Dev.PInfo.ParmData[3],CHS_Dev.PInfo.ParmData[4],\
				CHS_Dev.PInfo.ParmData[5],CHS_Dev.PInfo.ParmData[6]);
				UART_printf("FunRet: %d",Result);
				break;	
			default :
				UART_printf("�������\r\n");
				break;
		}
		return 0;
}

//����1���ַ��� ������ճɹ�������scan() ����һ��
void CHS_Rev1(uint8_t ch)
{
	if((CHS_Dev.USART_STAT&0x8000)==0)
	{
		if(CHS_Dev.USART_STAT&0x4000) //���յ���0x0D
		{
			if(ch!=0x0A)  CHS_Dev.USART_STAT=0; //���մ���
			else  
			{
				CHS_Dev.USART_STAT|=0x8000;    //�������
				CHS_Scan();                    //ִ��������
				CHS_ClearStr(CHS_Dev.USART_BUF,sizeof(CHS_Dev.USART_BUF));
				CHS_Dev.USART_STAT=0;
			}
		}
		else 
		{
			if(ch==0x0d) CHS_Dev.USART_STAT|=0x4000;//���յ��˻س���
			else
			{
				CHS_Dev.USART_BUF[CHS_Dev.USART_STAT&0x3FFF]=ch;
				CHS_Dev.USART_STAT++;
				if((CHS_Dev.USART_STAT&0x3FFF)>(MAX_FNAME_LEN+PARM_LEN-1)) CHS_Dev.USART_STAT=0; //�������ݴ���,���¿�ʼ����	  
			}		
		}
	}
}

