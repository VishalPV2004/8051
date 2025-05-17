#include<reg52.h>

sbit inbit = P1 ^ 0;
sbit outbit = P2 ^ 7;
bit membit

/*

bit membit_at_0x05 => forces on 0x20.5

or 

bdata unsigned char myByte;
sbit mybit = myByte ^ 5;       => forces too

*/

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 123; j++);  
}


int main()
{
	while(1) {
	membit = inbit;
	delay_ms(300);
	outbit = ~membit;
	}
}
