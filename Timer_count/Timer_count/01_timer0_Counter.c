/*
 * Timer_count.c
 * 0번 인터럽트 - 오버플로우 인터럽트를 이용해서 1초마다 LED 점등
 * Created: 2022-06-21 오후 3:32:12
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>


volatile unsigned char LED_Data = 0x00;
unsigned char timer0Cnt = 0;	//

SIGNAL(TIMER0_OVF_vect)	//오버플로우 인터럽트 발생
{
	cli();
	TCNT0 = 256 - ((F_CPU / 1024)*0.01);
	timer0Cnt++;
	if(timer0Cnt == 100)	//1초
	{
		LED_Data++;
		if(LED_Data > 0x0F) LED_Data = 0x00;
		timer0Cnt = 0;
	}
	sei();
	
}



int main(void)
{
	
	DDRC = 0x0F;
	TCCR0 = 0X07;
    //TIMSK |= 1<<TOIE0;	//오버플로우 인터럽트 허용
	TIMSK = 0x01;
	TIFR |= 1 << TOV0;
	TCNT0 = 256 - ((F_CPU / 1024)*0.01);	//초?? 
	// 256 - 144 = 112 -> 0.01초마다 한번씩 인터럽트 발생
	/*
	0.01초 계산
	256 - (F_CPU / 1024)*0.01
	*/
	//0.01초 0~255
	
	
	sei();
	
    while (1) 
    {
		PORTC = LED_Data;
    }
}

