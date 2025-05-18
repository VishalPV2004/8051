#include <reg52.h>

sfr port2 = 0xA0;  // P2 SFR

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 123; j++);  // ~1ms at 11.0592 MHz
}

void main()
{
    unsigned long i;
    for(i = 0; i < 50000; i++)
    {
        port2 = 0xFF;  // Turn ON all P2 pins
        delay_ms(300);
        port2 = 0x00;  // Turn OFF all P2 pins
        delay_ms(300);
    }
}
