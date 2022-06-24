/*
 * keyT.c
 *
 * Created: 2022-06-23 오후 5:23:44
 *  Author: Cking
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
//#include "Keypad.h"

void init_keypad()
{
	DDRA = 0xF8; //0b 1111 1000
	PORTA = 0x07; //0b 0000 0111
}

unsigned char keyscan()
{
	PORTA = 0x08; //0b 0000 1000
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '1';
	else if((PINA & 0x07) == 0x02) return '2';
	else if((PINA & 0x07) == 0x04) return '3';
	_delay_ms(10);
	
	PORTA = 0x10;		// 0b 0001 0000
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '4';
	else if((PINA & 0x07) == 0x02) return '5';
	else if((PINA & 0x07) == 0x04) return '6';
	_delay_ms(10);
	
	PORTA = 0x20;		// 0b 0010 0000
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '7';
	else if((PINA & 0x07) == 0x02) return '8';
	else if((PINA & 0x07) == 0x04) return '9';
	_delay_ms(10);
	
	PORTA = 0x40;		// 0b 0100 0000
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '*';
	else if((PINA & 0x07) == 0x02) return '0';
	else if((PINA & 0x07) == 0x04) return '#';
	_delay_ms(10);
	
	return 0;
}
int main()
{
	DDRC = 0xFf;
	init_keypad();
	
	while(1){
		unsigned char key = keyscan();
		if(key == '1') PORTC = 0x01;
		else if(key == '2') PORTC = 0x02;
		
	}
	return 0;
}