#include <reg51.h>

sbit b = P2^1;

void main(void)
{
    TMOD = 0x0C;     // Counter 0, Mode 0 (13-bit counter)
    TH0 = 0xFF;      // Upper 5 bits used
    TL0 = 0xE0;      // Total count = 0x1FE0 (8160 pulses)

    TR0 = 1;         // Start Counter 0

    while (1)
    {
        while (TF0 == 0);  // Wait for 8160 external pulses on P3.4
        TF0 = 0;           // Clear overflow flag
        b = ~b;            // Toggle P2.1
    }
}
