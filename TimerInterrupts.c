#include<reg51.h>

sbit wave = P2^1;
sbit in = P1^1;
sbit out = P0^1;


void timer0_int() interrupt 1
{
	wave = ~wave;
	TF0 = 0;
}

void main()
{
	TMOD = 0x02;
	TH0 = 0xA4;
	TL0 = 0xA4;
	IE = 0x82;
	TR0 = 1;
	
	while(1)
	{
		out = in;
	}
}
