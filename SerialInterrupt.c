#include<reg51.h>

sbit out = P2^0;
sbit in = P2^7;

void serial_int() interrupt 4
{
	P1 = SBUF;
	RI = 0;
}

void delay(unsigned int ms)
{
	unsigned int i,j;
	
	for(i = 0; i < ms ; i++)
	{
		for(j = 0 ; j < 1275 ; j++)
		{
		}
	}
}

void main()
{
	TMOD = 0x20;
	TH1 = 0xFD;
	SCON = 0x50;
	IE = 0x90;
	TR1 = 1;
	
	while(1)
	{
		out = in;
		delay(10);
	}
}
