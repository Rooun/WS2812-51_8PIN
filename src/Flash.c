#include <stdlib.h>
#include "flash.h" 			//包含动画文件

extern bit READ;			//串口中断接收标志位（全局使用，动画中加快接收响应）
uchar i, j;				   	//计算使用
uchar r, g, b, d;		   	//灯光效果使用
uchar old_r, old_g, old_b; 	//呼吸灯使用
uchar idata s[SNUM][3];	   	//定义数组，一个像素点{G,R,B}

/****************************************************************/
/*                            纯色                              */
/****************************************************************/
void SetRGBD(r, g, b, d)
{
	for (i = 0; i < SNUM; i++)
	{
		s[i][1] = r;
		s[i][0] = g;
		s[i][2] = b;
	}
	SendOneFrame(d, &s[0][0]);
	DelayMs(20);
}

void _Black()
{
	SetRGBD(0, 0, 0, 0);
}
void _White()
{
	SetRGBD(255, 255, 255, 0);
}
void _Red()
{
	SetRGBD(255, 0, 0, 0);
}
void _Green()
{
	SetRGBD(0, 255, 0, 0);
}
void _Blue()
{
	SetRGBD(0, 0, 255, 0);
}
void _Yellow()
{
	SetRGBD(255, 255, 0, 0);
}
void _Cyan() //青色
{
	SetRGBD(0, 255, 255, 0);
}
void _Magenta() //紫色
{
	SetRGBD(255, 0, 255, 0);
}
void _Orange() //橘色
{
	SetRGBD(215, 70, 0, 0);
}

/****************************************************************/
/*                            动画								*/
/****************************************************************/
/* 模式1(默认) 单渐暗螺旋旋转 */
void _Single()
{
	for (i = 0; i < SNUM; i++)
	{
		r = 255 > (i)*40 + 5 ? (i)*40 + 5 : 0;
		s[i][1] = r;
		s[i][0] = r;
		s[i][2] = r;
		SendOneFrame(i, &s[0][0]);
		DelayMs(24);
	}
}

/* 模式2 双渐暗螺旋旋转 */
void _Double()
{
	for (i = 0; i < SNUM; i++)
	{
		if (i < SNUM / 2)
		{
			r = 255 > (i)*40 + 5 ? (i)*40 + 5 : 0;
		}
		else
		{
			r = 255 > (i - SNUM / 2) * 40 + 5 ? (i - SNUM / 2) * 40 + 5 : 0;
		}
		s[i][1] = r;
		s[i][0] = r;
		s[i][2] = r;
		SendOneFrame(i, &s[0][0]);
		DelayMs(20);
	}
}

/* 模式3 呼吸灯 */
void _Breath()
{
	if (old_r + old_g + old_b == 0)
	{
		r = rand() % 128;
		old_r = rand() % 256;
		srand(old_r);
		g = rand() % 128;
		old_g = rand() % 256;
		srand(old_g);
		b = rand() % 128;
		old_b = rand() % 256;
	}

	if (r >= old_r + 3)
		r -= 3;
	else if (r <= old_r - 3)
		r += 3;
	else
		old_r = rand() % 256;

	if (g >= old_g + 3)
		g -= 3;
	else if (g <= old_g - 3)
		g += 3;
	else
		old_g = rand() % 256;

	if (b >= old_b + 3)
		b -= 3;
	else if (b <= old_b - 3)
		b += 3;
	else
		old_b = rand() % 256;

	SetRGBD(r, g, b, 0);
	DelayMs(30);
}

/* 模式4 旋转花 */
void _Flower()
{
	for (i = 0; i < SNUM; i++)
	{
		if (i < SNUM / 8 * 1)
		{
			s[i][1] = 255;
			s[i][0] = 0;
			s[i][2] = 0;
		}
		else if (i < SNUM / 8 * 2)
		{
			s[i][1] = 255;
			s[i][0] = 255;
			s[i][2] = 0;
		}
		else if (i < SNUM / 8 * 3)
		{
			s[i][1] = 0;
			s[i][0] = 255;
			s[i][2] = 0;
		}
		else if (i < SNUM / 8 * 4)
		{
			s[i][1] = 0;
			s[i][0] = 255;
			s[i][2] = 255;
		}
		else if (i < SNUM / 8 * 5)
		{
			s[i][1] = 0;
			s[i][0] = 0;
			s[i][2] = 255;
		}
		else if (i < SNUM / 8 * 6)
		{
			s[i][1] = 255;
			s[i][0] = 0;
			s[i][2] = 255;
		}
		else if (i < SNUM / 8 * 7)
		{
			s[i][1] = 157;
			s[i][0] = 139;
			s[i][2] = 126;
		}
		else if (i < SNUM / 8 * 8)
		{
			s[i][1] = 215;
			s[i][0] = 70;
			s[i][2] = 0;
		}
		SendOneFrame(-i, &s[0][0]);
		DelayMs(30);
	}
}

/* 模式8 黑白闪光灯 */
void _Flash()
{
	_White();
	DelayMs(100);
	_Black();
	DelayMs(100);
}

/* 模式9 彩色闪光灯 */
void _Flash2()
{
	_White();
	DelayMs(100);
	_Black();
	DelayMs(100);
	_Red();
	DelayMs(100);
	_Black();
	DelayMs(100);
	_Green();
	DelayMs(100);
	_Black();
	DelayMs(100);
	_Blue();
	DelayMs(100);
	_Black();
	DelayMs(100);
	_Yellow();
	DelayMs(100);
	_Black();
	DelayMs(100);
	_Cyan();
	DelayMs(100);
	_Black();
	DelayMs(100);
	_Magenta();
	DelayMs(100);
	_Black();
	DelayMs(100);
	_Orange();
	DelayMs(100);
	_Black();
	DelayMs(100);
}
