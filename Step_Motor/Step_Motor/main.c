/*
 * Step_Motor.c
 *
 * Created: 2022-06-23 오후 3:07:24
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 0xF0;
	
	
    while (1) 
    {
		PORTD = 0x10;	// 0001 0000 => 1 step
		_delay_ms(100) ;
		
		PORTD = 0x20;	//0010 0000 => 2 step
		_delay_ms(100);
		
		PORTD = 0x40;	//0100 0000 => 3 step
		_delay_ms(100);
		
		PORTD = 0x80;	//1000 0000 => 4 step
		_delay_ms(200);
		
		
    }
}

