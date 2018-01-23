#include "head.h"

uchar tempData[5]={0,0,0,0,0};

uchar dhtReadByte()
{
	uchar i=0,dat=0;
	for(i=0;i<8;i++)
	{
		while(!DQ);
		Delay40us();
		dat<<=1;
		if(DQ)
		{
			dat++;
			while(DQ);
		}		
	}
	return dat;
}


void dhtGetdat()
{
	uchar  i;
	Delay40us();
	if(!DQ)
	{
		while(!DQ);
		Delay40us();
		Delay40us();
		Delay10us();
		tempData[0]=	dhtReadByte();
		tempData[1]=	dhtReadByte();
		tempData[2]=	dhtReadByte();
		tempData[3]=	dhtReadByte();
		tempData[4]=	dhtReadByte();
	}
	DQ=1;
	if(tempData[4] == tempData[0]+tempData[1]+tempData[2]+tempData[3])
	{
		for(i=0;i<5;i++)
			dhtData[i]=tempData[i];
	}
}