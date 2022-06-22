/*
 * _02.c
 *	1초마다 FND의 숫자가 증가(‘0’ ~ ’_’ 까지)
 * Created: 2022-06-22 오전 11:16:24
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA[] = 
{0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,
0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,
0X79,0X71,0X08,0X80};
volatile unsigned char time_s = 0;

int main ()
{
	DDRA = 0xff;	//A Port 출력으로 설정
	
	TCCR1A = 0x00;	//0000 0000 normal 포트,TOP = MAX
	TCCR1B = 1<<CS12 | 1<<CS10 ;	//0000 0101 => 1024 분주비
	
	OCR1A = 7200;	
	TIMSK = 0x10;	//0001 0000 => 타이머1의 출력비교 인터럽트 A, B를 개별적으로 Enable
	
	
	
	TIFR |=1 << OCF1A;
	
	
	
	sei();
	
	while (1)
	{
		PORTA = FND_DATA[time_s];
	}
	
	return 0;
}

SIGNAL(TIMER1_COMPA_vect)
{
	cli();
	
	OCR1A += 7200;		//1초 후 인터럽트 발생
	if(time_s > 18)
	time_s = 0;
	else
	time_s++;
		
	sei();
	
}