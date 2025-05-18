#include <reg51.h>

sbit control = P3^0;
sbit output = P2^2;

void delay_ms(unsigned int ms)
{
	unsigned int i, j;
	for(i = 0; i < ms; i++)
	{
		for(j = 0; j < 1275; j++);
	}
}

void main()
{
	P2 = 0x00;
	P3 = 0x00;
	while(1)
	{
		output = control;
		delay_ms(200);
	}
}
