/*
 * TimerCount_PWM.c
 *	pc pwm :: overflow, 비교매치 둘 다 인터럽트 발생
 * Created: 2022-06-22 오후 4:24:54
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char Light = 0;
    
	DDRB = 0x10;
	
	TCCR0 = (1<<COM01|1<<COM00|1<< WGM00 | 1<<CS02 | 1<<CS01);	//pc pwm 모드, 256 분주 ==> 14.4KHz
	TCNT0 = 0x00;	//타이머 0 카운터를 초기화
	
	//pwm -> 인터럽트 발생 시 특정 핀으로 전압공급
	while (1) 
    {
		for(Light = 0;Light<255;Light++)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
		
		for(Light = 255;Light>0;Light--)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
		
		
    }
}

