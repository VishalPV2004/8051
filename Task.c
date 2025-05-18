/*Write a 8051 C program to toggle port 1 continiously
*/

#include<reg52.h>

sfr port1 = 0x90;
void delay_ms(unsigned int ms);

void main()
{
	port1 = 0x00;
	delay_ms(250);
	port1 = 0xff;
	delay_ms(250);
}

void delay_ms(unsigned int ms)
{
	unsigned int i = 0, j = 0;
	for(i = 0 ; i < ms ; i++)
	{
		for(j = 0 ; j < 1275 ; j++)  //1 ms
		{
		}
	}
}
