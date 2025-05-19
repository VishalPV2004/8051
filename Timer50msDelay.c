#include<reg51.h>

sbit led = P1^5;

int main()
{
	while(1){
	TMOD = 0x01;
	TH0 = 0xB4;
	TL0 = 0x03;
	
	TR0 = 1;
	
  led = ~led;
	while(TF0 == 0);
	
	TF0 = 0;
	TR0 = 0;
	
	}
	
	
}
