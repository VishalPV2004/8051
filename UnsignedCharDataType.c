#include<reg52.h>
int main()
{
	unsigned char z;
	
	for(z = 0 ; z <= 255 ; z++)
	{
		P1 = z;
		//*(unsigned char* (0x90)) = z;  Accessing with direct address ;
	}
}
