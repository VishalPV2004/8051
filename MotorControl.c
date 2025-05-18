#include <reg52.h>

void delay(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1275; j++);
}

void main()
{
    while (1)
    {
        // Both motors forward
        // EN1 = 1 (P1.0), EN2 = 1 (P1.1)
        // IN1 = 1 (P1.2), IN2 = 0 (P1.3)
        // IN3 = 1 (P1.4), IN4 = 0 (P1.5)
        P1 = 0x37;  // 0011 0111
        delay(2000);

        // Both motors backward
        // EN1 = 1 (P1.0), EN2 = 1 (P1.1)
        // IN1 = 0 (P1.2), IN2 = 1 (P1.3)
        // IN3 = 0 (P1.4), IN4 = 1 (P1.5)
        P1 = 0x2B;  // 0010 1011
        delay(2000);
    }
}
