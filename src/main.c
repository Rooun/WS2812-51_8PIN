#include "reg51.h"
#include "intrins.h"
#include "flash.h"			//���������ļ�
#define FOSC 22118400L		//ϵͳƵ��
#define BAUD 250000			//���ڲ�����
#define uchar unsigned char //��������
#define uint unsigned int	//��������

sfr AUXR = 0x8e; //�����Ĵ���
sfr T2H = 0xd6;	 //��ʱ��2��8λ
sfr T2L = 0xd7;	 //��ʱ��2��8λ

bit busy;								//���ͱ�־λ
bit READ;								//�����жϽ��ձ�־λ��ȫ��ʹ�ã������мӿ������Ӧ��
uchar Rdata;	  						//���յ��ַ�
uchar mode = '2'; 						//�ƹ���ʾģʽ
extern uchar idata s[SNUM][3];			//�������飬LEDĿǰ��ʾ���飬һ�����ص�{G,R,B}
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
	/* ��ʼ�� */
	UART_INIT();
	/* ��ʼ���� */
	while (1)
	{
		if (1 == READ)
		{
			READ = 0;			 //������Ϣ������
			mode = Rdata;		 //��Ϣ����ģʽ
			SendString("Mode:"); //��Ϣ���պ��������ֵ
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
		/* ����ģʽ */
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
		UART �жϷ������
-----------------------------*/
void Uart() interrupt 4 using 1
{
	if (RI)
	{
		RI = 0;		  //���RIλ
		if(SBUF > 31)   // ���β��ɼ��ַ����س������У�
		{
			READ = 1;	  //���ձ�־λ��1
			Rdata = SBUF; //���ռĴ���ȡֵ
		}
	}
	if (TI)
	{
		TI = 0;	  //���TIλ
		busy = 0; //��æ��־
	}
}
/*----------------------------
		���ڳ�ʼ��
----------------------------*/
void UART_INIT()
{
	SCON = 0x50;
	T2L = (65536 - (FOSC / 4 / BAUD)); //���ò�������װֵ
	T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
	AUXR = 0x14;				// T2Ϊ1Tģʽ, ��������ʱ��2
	AUXR |= 0x01;				//ѡ��ʱ��2Ϊ����1�Ĳ����ʷ�����
	ES = 1;						//ʹ�ܴ���1�ж�
	EA = 1;						//�����ܿ��ش�
	SendString("Init Sec\r\n"); //��ʼ���ɹ����
}
/*----------------------------
		���ʹ�������
----------------------------*/
void SendData(uchar dat)
{
	while (busy);		//�ȴ�ǰ������ݷ������
	busy = 1;			//���͵ȴ���־λ
	SBUF = dat; 		//д���ݵ�UART���ݼĴ���
}
/*----------------------------
        �����ַ���
----------------------------*/
void SendString(char *s)
{
	while (*s) //����ַ���������־
	{
		SendData(*s++); //���͵�ǰ�ַ�
	}
}
