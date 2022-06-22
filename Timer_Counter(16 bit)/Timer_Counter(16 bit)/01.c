/*
 * Timer_Counter(16 bit).c
 *	타이머로 LED 점멸
 * Created: 2022-06-22 오전 10:16:03
 * Author : PKNU
 */ 
//avr은 8bit
#define F_CPU 7372800UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer1Cnt = 0;

int main(void)
{
    DDRA = 0x0F;	//0000 1111
	
	TCCR1A = 0x00;		//OC핀 사용안함, PWM모드 설정 및 분주비 설정 OC핀 출력을 설정하는 레지스터
	TCCR1B = 1<<CS20;	//프리스케일러(1) => 분주비 256개로 설정

	TCNT1 = 66536-78800;
	TIMSK = 1<<TOIE1;
	TIFR = TIFR | 1<<TOV1;
	
	sei();
	
    while (1) 
    {
		PORTA = LED_Data;
    }
	return 0;
}

SIGNAL(TIMER1_OVF_vect)
{
	cli();
	
//	timer1Cnt++;
	
//	if(timer1Cnt == 255)
	//{
		
	LED_Data++;
	if(LED_Data > 0x0F)LED_Data = 0;
		
		//timer1Cnt = 0;
		
	//}
	
	sei();
	
}

