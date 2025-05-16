#include <REG52.H>

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 123; j++);  
}

void main(void)
{
    while(1)
    {
        P2 = 0x00;            // Turn OFF all pins of Port 2
        delay_ms(1000);       // 1 second delay

        P2 = 0xFF;            // Turn ON all pins of Port 2
        delay_ms(1000);       // 1 second delay
    }
}
