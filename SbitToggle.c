#include<reg52.h>

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 123; j++);  // Roughly 1 ms delay
}

sbit myBit = P1^7;

void main()
{
    
    while(1)
    {
        myBit = ~myBit;
        delay_ms(300);  // 300 ms blink
    }
}
