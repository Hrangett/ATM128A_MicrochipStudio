/*
 * Interrupt03.c
 *
 * Created: 2022-06-20 오전 11:34:53
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char signal = 0;
//ISR(INT4_vect)	//Interrupt Service Routine :: 인터럽트 서비스(신호) 루틴 
SIGNAL(INT4_vect)
{
	signal = ~signal;
}

int main()
{
	DDRE = 0x00;
	DDRA = 0XFF;
		
	EIMSK = 1 << INT4;
	//EICRA = 1 << ISC01 | 0 << ISC00;
	EICRB = 1 << ISC41 | 1 << ISC40;	//기본설정값이 0이다 => 0은 굳이 설정하지않아도 된다.
	//하강 엣지 :: Height -> Low LEVEL :: 버튼을 땔 때 동작
	//상승 엣지 :: Low -> Height LEVEL :: 버튼을 누를 때 동작
		
	sei();
	
	int led = 0x01;
	int move = 1;
	while (1)
	{
		if(signal)
		{
			PORTA =	led;

			_delay_ms(1000);
			led = led >> move;
			
			if (led == 0x00)
			{
				led=0x80;
			}

	
		}
		else
		{
			PORTA = led;

			_delay_ms(1000);
			led = led << move;

			if (led>>1 == 0x80)
			{
				led=0x01;
			}							
		}
	}
	
	
	
	return 0;
}