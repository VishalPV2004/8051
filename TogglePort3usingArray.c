#include<reg52.h>


void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 123; j++);  
}

sbit P3_0 = P3 ^ 0;  // Bit-addressable pin P3.0


int main()
{
	 char myChar[] = {-1, 1};
	 char i = 0;
	 
	 while (1) {
    P3 = myChar[i];
    i = 1 - i;
    delay_ms(300);
}

}
