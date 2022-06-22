/*
 * _03_timer0_Cnt.c
 *
 * Created: 2022-06-21 오후 5:10:32
 *  Author: PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char FND_DATA[] =
{
	0x3f,   0x06,   0x5b,   0x4f,
	0x66,   0x6d,   0x7d,   0x27,
	0x7f,   0x6f,   0x77,   0x7c,
	0x39,   0x5e,   0x79,   0x71
};
volatile unsigned char time_s = 0;
unsigned char timer0Cnt = 0;

SIGNAL(TIMER0_OVF_vect);

int main(void)
{
	DDRA = 0xff;
	
	TCCR0 = 0x07;	//0000 0111
	OCR0 = ((F_CPU / 1024)*0.01);		//0.01초마다 한번씩 인터럽트 발생
	TIMSK = 0X02;	//출력비교 인터럽트 활성화
	TIFR |= 1<< OCF0;
	
	sei();
	while(1)
	{
		PORTA = FND_DATA[time_s];
	}
	 
	
	
	return 0;
}

SIGNAL(TIMER0_COMP_vect)
{
	cli();
	OCR0 += ((F_CPU / 1024)*0.01);
	timer0Cnt++;
	
	if(timer0Cnt == 100)
	{
		
		if (time_s>=15)
		{
			time_s = 0;
		}
		else time_s++;
		timer0Cnt = 0;
	}
	
	sei();
}