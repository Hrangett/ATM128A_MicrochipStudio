/*
 *	Interrupt04.c
 *
 *	Created: 2022-06-20 오후 2:06:08
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

volatile unsigned char signal = 0;
SIGNAL(INT5_vect)
{
	signal = ~signal;
}

int main()
{
	/*
		일정시간마다
		클럭에 의해
		
		1. 초기화
		2. stop/start
	*/
	
	DDRE = 0x00;
	DDRA = 0XFF;
	EIMSK = 1 << INT5;
	EICRB = 1<<ISC51;
	
	sei();
	
	//int fnd_zs[] = 0	 1	2	3	 4	  5	   6	7	 8	  9 	A	 B	 C	  D	   E	F
	int fnd_zs[] = {0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X27,0X7F,0X6F,0X77,0X7C,0X39,0X5E,0X79,0X71};
	int i = 0;
	
	while (1)
	{
		if(signal)
		{
			PORTA = fnd_zs[i];
		}
		else
		{
			PORTA = fnd_zs[i];
			_delay_ms(1000);
			if (fnd_zs[i] == 0x71)
			{
				i = -1;
			}
			i++;
							
		}
	}
	
	return 0;
	
}