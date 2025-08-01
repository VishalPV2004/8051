#include <reg51.h>

sbit ALE = P2^4;
sbit OE = P2^5;
sbit SC = P2^6;
sbit EOC = P2^7;
sbit ADDR_A = P2^0;
sbit ADDR_B = P2^1;
sbit ADDR_C = P2^2;
sbit LED = P2^3;


void MSDelay(unsigned int delay)
{
    unsigned int i, j;
    for(i = 0; i < delay; i++)
        for(j = 0; j < 1275; j++);
}

void main()
{
    unsigned char value;

    P1 = 0xFF;  
    EOC = 1;
    ALE = 0;
    OE = 0;
    SC = 0;
	  LED = 0;

    while(1)
    {
        ADDR_C = 0;
        ADDR_B = 0;
        ADDR_A = 0;

        MSDelay(1);
        ALE = 1;
        MSDelay(1);
        SC = 1;
        MSDelay(1);
        ALE = 0;
        SC = 0;

        while(EOC == 1);
        while(EOC == 0);

        OE = 1;
        MSDelay(1);
        value = P1;

        if (value > 50)
            LED = 1;
        else
            LED = 0;

        P3 = value;  // Send data out
        OE = 0;
    }
}

