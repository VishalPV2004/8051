#include <reg51.h>

void delay(unsigned int ms)
{
	unsigned int i,j;
	for( i = 0 ; i < ms ; i++)
	{
		for(j = 0 ; j < 1275 ; j++)
		{
		}
	}
}

void main() {
	TMOD = 0x20;     // Timer1, Mode2 (auto-reload)
	TH1 = 0xFD;      // 9600 baud (for 11.0592 MHz)
	SCON = 0x50;     // Mode1, 8-bit UART, REN enabled
	TR1 = 1;         // Start Timer1

	while (1) {
		TI = 0;           // Clear transmit interrupt flag
		SBUF = 65;       // Load data to send
    delay(20);
		while (TI == 0);  // Wait for transmit to complete
	}
}
