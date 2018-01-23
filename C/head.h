#ifndef _HEAD_H_
#define _HEAD_H_
#include <reg52.h>
#include <intrins.h>
#define nop() _nop_()
#define uchar unsigned char
#define uint unsigned int

#define WDT			0x35			//看门狗初始化@11.0592MHz，2.2755s

sfr AUXR        =   0x8e;
sfr CLK_DIV = 0x97;					//时钟命令寄存器
sfr WDT_CONTR = 0xc1;//看门狗


sbit LED = P3^0;
sbit CLK = P3^1;
sbit sCLK = P3^2;

sbit DQ=P3^5;

void Delay1s();

void DelayXus(uint n);
void Delay10us();
void Delay40us();


void ledShow();

void dhtGetdat();

extern uchar dhtData[];

#endif