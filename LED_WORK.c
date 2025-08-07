#include <reg51.h>

void delay_ms(unsigned int ms);
void DualLED();
void QuadLED();
void CompLED();

void DualLED()
{        
	int i;
	      for(i = 0; i <= 6; i += 2) {  
            P1 = 0x00;  
            P1 = (1 << i); 
					  P1 |= (1 << (i + 1));  
            delay_ms(100);
        }
        for(i = 7; i >= 1; i -= 2) {  
            P1 = 0x00;  
            P1 = (1 << i); 
					  P1 |= (1 << (i - 1));  
            delay_ms(100);
        }
}

void QuadLED()
{
	int i;
	for(i = 0 ; i <= 4 ; i=i+4)
	{
		P1 = 0x00;
		P1 = (1 << i);
		P1 |= (1 << (i+1));
		P1 |= (1 << (i+2));
		P1 |= (1 << (i+3));
		delay_ms(200);
	}
	for(i = 7 ; i >= 3 ; i=i-4)
	{
		P1 = 0x00;
		P1 = (1 << i);
		P1 |= (1 << (i-1));
		P1 |= (1 << (i-2));
		P1 |= (1 << (i-3));
		delay_ms(200);
	}
}

void CompLED()
{
	int i;
	
	for(i = 0 ; i < 4 ; i++)
	{
		P1 = 0x00;
		P1 = (1 << i);
		P1 |= (1 << (8-i-1));
		delay_ms(200);
	}
}

void main() {
    while(1) {
			  QuadLED();
			  CompLED();
    }
}

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++) {
        for(j = 0; j < 1275; j++) {
        }
    }
}
