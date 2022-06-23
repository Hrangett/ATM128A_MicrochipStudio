/*
 * 01_keypad.c
 *
 * Created: 2022-06-23 오후 4:03:56
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char key;
	
	DDRA = 0xF8;	//0b 1111 1000 포트 A의 상위 4비트는 출력, 하위 4비트는 입력
	DDRC = 0xFF;
	
    while (1) 
    {
		key = keySn();
		if(key == '1')
		PORTC = 0x01;
    }
}

unsigned char keySn()
{
	
	PORTA = 0XFB;	//0b 1111 0111
	if(PINA == 0xF6) return '1';	//0b 1111 1110
	else if(PINA = 0xFD)return'2';	// 0b 1111 1101
	else if(PINA = 0xFB)return'3';
	_delay_ms(10);
		
	PORTA = 0xEF;	//0B 1110 1111
	if(PINA == 0xFE)return'4';	//0b 1111 1100
	else if(PINA == 0xFD)return'5';
	else if(PINA == 0xfb)return'6';
	_delay_ms(10);
	
	PORTA = 0xDF;
	if(PINA = 0xFE)return'7';
	else if(PINA ==0xFd)return'8';
	else if(PINA == 0xfb)return'9';
	_delay_ms(10);
	
	PORTA = 0xBf;	//1011 FFFF
	if(PINA = 0xFE)return'*';
	else if(PINA ==0xFd)return'0';
	else if(PINA == 0xfb)return'#';
	
}