#include<reg52.h>

/*

  Digit | h g f e d c b a | Hex
  -----------------------------
    0   | 0 0 1 1 1 1 1 1 | 0x3F
    1   | 0 0 0 0 0 1 1 0 | 0x06
    2   | 0 1 0 1 1 0 1 1 | 0x5B
    3   | 0 1 0 0 1 1 1 1 | 0x4F
    4   | 0 1 1 0 0 1 1 0 | 0x66
    5   | 0 1 1 0 1 1 0 1 | 0x6D
    6   | 0 1 1 1 1 1 0 1 | 0x7D
    7   | 0 0 0 0 0 1 1 1 | 0x07
    8   | 0 1 1 1 1 1 1 1 | 0x7F
    9   | 0 1 1 0 1 1 1 1 | 0x6F

*/

// Function prototype for delay
void delay(unsigned int);

void main()
{

    unsigned char seven_seg_digits[10] = {
        0x3F,  // 0
        0x06,  // 1
        0x5B,  // 2
        0x4F,  // 3
        0x66,  // 4
        0x6D,  // 5
        0x7D,  // 6
        0x07,  // 7
        0x7F,  // 8
        0x6F   // 9
    };
    
    unsigned char i;
    
    while(1)  // Infinite loop
    {
        for(i = 0; i < 10; i++)
        {
            P3 = seven_seg_digits[i];  // Output digit pattern to Port 1
					  P2 = ~seven_seg_digits[i]; // Output digit pattern to Port 2
            delay(50);              // Delay to keep the digit visible
        }
    }
}

// Simple delay function
void delay(unsigned int count)
{
    unsigned int i, j;
    for(i = 0; i < count; i++)
    {
        for(j = 0; j < 1275; j++);
    }
}
