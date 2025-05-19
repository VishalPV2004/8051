#include<reg51.h>

sbit b = P2^1;
void main(void)
{
	
	while(1) 
	{
	  TMOD = 0x00;  // 0000 0000 - Timer 0 mode
	  TH0 = 0xEE;
	  TL0 = 0x00;
	
	  TR0 = 1;      // starting timer 0
	  b = ~b;
	  while(TF0 == 0); // when it becomes 1, stop the timer
	  TR0 = 0;
	  TF0 = 0;
	}
}
