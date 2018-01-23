#include "head.h"

uchar dhtData[]={0,0,0,0,1};

void Timer0Init(void)		//20毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0xB8;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	EA=1;			//中断允许
	ET0=1;
	TR0 = 1;		//定时器0开始计时
}

void tm0Isr() interrupt 1 using 1
{
	DQ = 1;
	dhtGetdat();	 //开始读数
}

void main()
{
	int i;
	WDT_CONTR = WDT;
	LED=0;
	DQ = 1;

	Delay1s(); //DHT11越过不稳定阶段
	while(1)
	{	
		DQ=0;			//DHT11低电平延时18ms
		Timer0Init();
		for(i=0;i<500;i++)
		{
			WDT_CONTR = WDT;//喂狗
			ledShow();
		}
	}
}

