#include "reg51.h"
#include <intrins.h>

#define SNUM 50				//�Ƶĸ��������73����
sbit DI = P3^2;				//WS2812���ݶ˿ڣ�ֻ�������û���գ�
sbit KEY = P3^3;			//��������


#define uchar unsigned char
#define uint  unsigned int

/*--------------------------------��������------------------------------------*/
void SendOnePix(uchar *ptr);	//����һ��LED��24bit����
void SendOneFrame(char i, uchar *ptr);//�ӵ�i�����ؿ�ʼ����

//-------------------------THE END------------------------*/   

