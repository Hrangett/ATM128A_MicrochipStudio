/*
 * led02.c
 *
 * Created: 2022-06-17 오후 1:54:49
 *  Author: PKNU
 */ 
#define F_CPU 7473800
#include <avr/io.h>
#include <util/delay.h>
/*
int main()
{
	DDRB = 0xFF;
	
	int num = 0x01;
	int i = 0;
	
	//PORTA = ~(num<<i);
	
	while (1)
	{
		//0 1 2 3 4 5 6 7
		
		PORTB = ~(num<<i);
		_delay_ms(500);
		
		i++;
		
		if (i == 7)
		{
			while(i != 0)
			{//7 6 5 4 3 2 1 0
				
				PORTB = ~(num<<i);
				_delay_ms(500);
				
				i--;	
			}	
			
		}
		
	}
	return 0;
}
*/