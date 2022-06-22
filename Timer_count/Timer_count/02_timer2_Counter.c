/*
 * _02_timer0_Counter.c
 *
 * Created: 2022-06-21 오후 4:46:37
 *  Author: PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x01;
unsigned char timer2Cnt = 0, Shift_Flag = 0;

SIGNAL(TIMER2_OVF_vect);

int main()
{
	DDRC = 0xFF;
	TCCR2 = 0x05;
	
	TCNT2 = 256 - ((F_CPU / 1024)*0.01);
	
	TIMSK = 0x40; //0100 0000
	TIFR |= 1 << TOV2;
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	
	return 0;

}

SIGNAL(TIMER2_OVF_vect)
{
	
	cli();
	TCNT2 = 256 - ((F_CPU / 1024)*0.01);
	timer2Cnt++;
	
	if(timer2Cnt == 50)
	{
		if(Shift_Flag == 0)
		{
			LED_Data <<= 1;
			if(LED_Data == 0x80)Shift_Flag = 1;	//led3으로 이동하면 우측 쉬프트하도록 설정
			
		}
		else
		{
			// LED3 ~ LED0으로 이동
			LED_Data >>= 1; // LED_Data 변수를 우측으로 쉬프트
			if(LED_Data == 0x01) // LED0으로 이동하면
			Shift_Flag = 0; // 좌측으로 쉬프트하도록 설정
		}
		timer2Cnt = 0;
	}
	sei();
}
