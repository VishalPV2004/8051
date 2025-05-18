/*Write a program to monitor p2.0 and control port 1*/

#include<reg52.h>

sbit inbit = P2^0;
sfr outport = 0x90;

void delay(unsigned int ms);

int main()
{
	P2 = 0x00;
	P1 = 0x00;
   while(1)
	 {
		 if (inbit == 0x01)
		 {
			 outport = 0xff;
			 delay(10);
		 }
		 else
		 {
			 outport = 0x00;
			 delay(10);
		 }
	 }		 
}

void delay(unsigned int ms)
{
	unsigned int i = 0, j = 0;
	for(i = 0 ; i < ms ; i++)
	{
		for(j = 0 ; j < 1275 ; j++)
		{
		}
	}
}
