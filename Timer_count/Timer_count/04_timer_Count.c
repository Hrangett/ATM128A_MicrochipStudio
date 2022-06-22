/*
 * _04_timer_Count.c
 * 타이머와 인터럽트로 FND 점멸
 * Created: 2022-06-21 오후 5:41:52
 *  Author: PKNU
 */ 

#include <avr/io.h> // AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h> // AVR 인터럽트에 대한 헤더파일

unsigned char FND_DATA =
{
	0x3f,   0x06,   0x5b,   0x4f,
	0x66,   0x6d,   0x7d,   0x27,
	0x7f,   0x6f,   0x77,   0x7c,
	0x39,   0x5e,   0x79,   0x71
};

volatile unsigned char time_s = 0;
volatile unsigned char Time_STOP = 0;

unsigned char timer0Cnt = 0;

int main(void)
{
	
	DDRA = 0xFF;
	DDRE = 0x00;
	
	TCCR2 = 0x05;
	OCR2 = ((F_CPU / 1024)*0.01);
	TIMSK = 0x80;
	TIFR |=1 << OCF2;
	
	EICRB = 0x03;
	EIMSK = 0x10;
	EIFR = 0x10;
	
	sei();
	
	while(1)
	{
		PORTA = FND_DATA[time_s];
		
	}
	return 0;
	
	
}

SIGNAL(TIMER2_COMP_vect)
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
		
	}
	timer0Cnt = 0;
	sei();
}

SIGNAL(INT4_vect)
{
	
	cli();
	
	if(Time_STOP == 0)Time_STOP = 1;
	else Time_STOP = 0;
	
	sei();
	
}