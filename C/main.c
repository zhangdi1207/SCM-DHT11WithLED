#include "head.h"

uchar dhtData[]={0,0,0,0,1};

void Timer0Init(void)		//20����@11.0592MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0xB8;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	EA=1;			//�ж�����
	ET0=1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void tm0Isr() interrupt 1 using 1
{
	DQ = 1;
	dhtGetdat();	 //��ʼ����
}

void main()
{
	int i;
	WDT_CONTR = WDT;
	LED=0;
	DQ = 1;

	Delay1s(); //DHT11Խ�����ȶ��׶�
	while(1)
	{	
		DQ=0;			//DHT11�͵�ƽ��ʱ18ms
		Timer0Init();
		for(i=0;i<500;i++)
		{
			WDT_CONTR = WDT;//ι��
			ledShow();
		}
	}
}

