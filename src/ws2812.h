#include "reg51.h"
#include <intrins.h>

#define SNUM 50				//灯的个数（最大73个）
sbit DI = P3^2;				//WS2812数据端口（只有这个口没风险）
sbit KEY = P3^3;			//按键引脚


#define uchar unsigned char
#define uint  unsigned int

/*--------------------------------函数声明------------------------------------*/
void SendOnePix(uchar *ptr);	//发送一个LED的24bit数据
void SendOneFrame(char i, uchar *ptr);//从第i个像素开始发送

//-------------------------THE END------------------------*/   

