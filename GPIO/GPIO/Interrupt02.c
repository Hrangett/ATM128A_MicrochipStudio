/*
 * Intettupt02.c
 *
 * Created: 2022-06-20 오전 10:40:21
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
//하강에지 1 -> 0
//INT4 -> PINE4

//volatile unsigned char signal = 0;
volatile  bool signal = true;


SIGNAL(INT4_vect)
{
	//대충 누르면 켜지고 누르면 꺼지고
	//하강에지 : Height -> Low;
	
	switch (signal)
	{
		case true:
		/* Your code here */
		{
			
			signal = false;
		}
		
		break;
		
		case false:
		/* Your code here */
		{
			
			signal = true;
			
		}
		break;
		
	}
	

	
}

int main()
{
	//대충 누르면 켜지고 누르면 꺼지고
	DDRE = 0x00;
	DDRA = 0XFF;
	
	EIMSK = 1 << INT4;
	//EICRA = 1 << ISC01 | 0 << ISC00;
	EICRB = 1 << ISC41;	//기본설정값이 0이다 => 0은 굳이 설정하지않아도 된다.
	

	sei();
	
	while (1)
	{
		if(signal) PORTA = 0xff;
		else PORTA = 0x00;
	}
	
	return 0;
}