#include "reg51.h"
#include "intrins.h"
#include "flash.h"			//包含动画文件
#define FOSC 22118400L		//系统频率
#define BAUD 250000			//串口波特率
#define uchar unsigned char //定义类型
#define uint unsigned int	//定义类型

sfr AUXR = 0x8e; //辅助寄存器
sfr T2H = 0xd6;	 //定时器2高8位
sfr T2L = 0xd7;	 //定时器2低8位

bit busy;								//发送标志位
bit READ;								//串口中断接收标志位（全局使用，动画中加快接收响应）
uchar Rdata;	  						//接收的字符
uchar mode = '2'; 						//灯光显示模式
extern uchar idata s[SNUM][3];			//定义数组，LED目前显示数组，一个像素点{G,R,B}
extern void _Black();
extern void _Single();
extern void _Double();
extern void _Breath();
extern void _Flower();
extern void _Flash();
extern void _Flash2();
extern void _White();
extern void _Red();
extern void _Green();
extern void _Blue();
extern void _Cyan();
extern void _Yellow();
extern void _Magenta();
extern void _Orange();

void SendData(uchar dat);
void SendString(char *s);
void UART_INIT();
void Work();


void main()
{
	/* 初始化 */
	UART_INIT();
	/* 开始工作 */
	while (1)
	{
		if (1 == READ)
		{
			READ = 0;			 //接受消息标记清空
			mode = Rdata;		 //消息传给模式
			SendString("Mode:"); //消息接收后给出返回值
			SendData(Rdata);
			SendString("\r\n");
		}
		if(!KEY)
		{
			DelayMs(5);
			while(!KEY)
			{
				_Flower();
			}
		}
		/* 工作模式 */
		switch (mode)
		{
			case '0':
				_Black();
				break;
			case '1':
				_Single();
				break;
			case '2':
				_Double();
				break;
			case '3':
				_Breath();
				break;
			case '4':
				_Flower();
				break;
			case '8':
				_Flash();
				break;
			case '9':
				_Flash2();
				break;
			case 'W':
				_White();
				break;
			case 'R':
				_Red();
				break;
			case 'G':
				_Green();
				break;
			case 'B':
				_Blue();
				break;
			case 'C':
				_Cyan();
				break;
			case 'Y':
				_Yellow();
				break;
			case 'M':
				_Magenta();
				break;
			case 'O':
				_Orange();
				break;
			default:
				SendData(Rdata);
				DelayMs(255);
				break;
		}
	}
}

/*----------------------------
		UART 中断服务程序
-----------------------------*/
void Uart() interrupt 4 using 1
{
	if (RI)
	{
		RI = 0;		  //清除RI位
		if(SBUF > 31)   // 屏蔽不可见字符（回车、换行）
		{
			READ = 1;	  //接收标志位置1
			Rdata = SBUF; //接收寄存器取值
		}
	}
	if (TI)
	{
		TI = 0;	  //清除TI位
		busy = 0; //清忙标志
	}
}
/*----------------------------
		窗口初始化
----------------------------*/
void UART_INIT()
{
	SCON = 0x50;
	T2L = (65536 - (FOSC / 4 / BAUD)); //设置波特率重装值
	T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
	AUXR = 0x14;				// T2为1T模式, 并启动定时器2
	AUXR |= 0x01;				//选择定时器2为串口1的波特率发生器
	ES = 1;						//使能串口1中断
	EA = 1;						//串口总开关打开
	SendString("Init Sec\r\n"); //初始化成功输出
}
/*----------------------------
		发送串口数据
----------------------------*/
void SendData(uchar dat)
{
	while (busy);		//等待前面的数据发送完成
	busy = 1;			//发送等待标志位
	SBUF = dat; 		//写数据到UART数据寄存器
}
/*----------------------------
        发送字符串
----------------------------*/
void SendString(char *s)
{
	while (*s) //检测字符串结束标志
	{
		SendData(*s++); //发送当前字符
	}
}
