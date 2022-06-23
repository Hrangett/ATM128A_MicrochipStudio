/*
 * _03_PWM_PIEZO.c
 *
 * Created: 2022-06-23 오전 9:38:21
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523.25,587.33,659.26,523.25,783,880,987,1046};
	
int main()
{
	unsigned char piano = 0;
	
	DDRB = 0x80;
	
	//TCCR1A = 1<<COM1C1 | 1<<WGM31;
	//TCCR1B = 1<<WGM13 | 1<<WGM12 | 1<<CS10; 
	TCCR1A |= 0x0A;
	TCCR1B |= 0x19;
	TCCR1C = 0x00;
	TCNT1 = 0x0000;
	
	while(1)
	{
		
		ICR1 = F_CPU / ((DoReMi[piano]));
		OCR1C = ICR1/2;
		
		piano++;
		
		if(8<piano) piano = 0;
		
		_delay_ms(1100);
		_delay_ms(1100);
		_delay_ms(1100);
		_delay_ms(1100);
		_delay_ms(1100);

		
	}
	
	return 0;
}