#include "head.h"

uchar ledD[]={0,0,0,0,0,0,0,0}; //湿度4位+温度4位，由高到低
uchar ledC[]={0x10,0x20,0x40,0x80,0x01,0x02,0x04,0x08};	//段选，对应ledD各位数字

void getLedCode()
{
	uchar i;
	uint tmp100 = dhtData[2]*100 + dhtData[3];
	uint hum100 = dhtData[0]*100 + dhtData[1];
	uchar ledCode[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	for(i=0;i<4;i++)
	{	
		ledD[3-i]=ledCode[hum100%10];
		ledD[7-i]=ledCode[tmp100%10];
		hum100/=10;
		tmp100/=10;
	}	
	ledD[1]|=0x80;
	ledD[5]|=0x80;
}

void sendTo595(uchar c)//把温度或湿度的某一位值、对应序列号放入2个595中
{
	uchar i,dat;
	dat=ledC[c];
	for(i=0;i<8;i++)
	{
		CLK=0;
		LED=dat&0x80;
		dat=dat<<1;
		CLK=1;
	}
	dat=ledD[c];
	for(i=0;i<8;i++)
	{
		CLK=0;
		LED=dat&0x80;
		dat=dat<<1;
		CLK=1;
	}
	sCLK=0;
	nop();
	nop();
	sCLK=1;
}


void ledShow()
{
	uchar i;
	getLedCode();
	for(i=0;i<8;i++)
	{
		sendTo595(i);
	}
}