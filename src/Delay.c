#include "Delay.h"

extern bit READ;				//�����жϽ��ձ�־λ��ȫ��ʹ�ã������мӿ������Ӧ��

void DelayMs(uchar m)
{
	unsigned char i,j,k;
	if(READ)return;					//���ձ�־λ���ӿ������Ӧ
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