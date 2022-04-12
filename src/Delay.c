#include "Delay.h"

extern bit READ;				//串口中断接收标志位（全局使用，动画中加快接收响应）

void DelayMs(uchar m)
{
	unsigned char i,j,k;
	if(READ)return;					//接收标志位，加快接收响应
	for(k=0;k<m;k++)
	{
		for(i=0;i<60;i++)
		{
			for(j=0;j<78;j++)
			{
				;
			}
		}
	}
}