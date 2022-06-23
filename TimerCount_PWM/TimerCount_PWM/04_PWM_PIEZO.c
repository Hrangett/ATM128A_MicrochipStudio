/*
 * _04_PWM_PIEZO.c
 *
 * Created: 2022-06-23 오전 10:14:11
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523.25,587.33,659.26,523.25,783,880,987,1046};
volatile unsigned char sound_flag = 1;

int main()
{
	DDRE = 0x08; //Buzzer -> PE3
	
	TCCR3A = 0x00;
	TCCR3B = 1<<WGM33 |  1<<WGM32 | 1<<CS30;	//1분주
	TCCR3C = 0x00; // WGM3(3:0) = “1110”, Fast PWM, 모드 14
	TCNT3 = 0x0000; // 타이머3 카운터 초기화
	
	EICRB = 0xFF;
	EIMSK = 0xF0;
	EIFR = 0xF0;
	sei();
	
	while (1)
	{
		if(sound_flag)
		{
			_delay_ms(500);
			TCCR3A = 0x00;
			sound_flag = 0;
			
		}
	}
	
	return 0;
}

SIGNAL(INT4_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	
	ICR3 = F_CPU/DoReMi[0]/2; // 도의 음향을 연주한다
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	
	sei(); // 전체 인터럽트를 허용
}SIGNAL(INT5_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = F_CPU/DoReMi[1]/2; // 래의 음향을 연주한다
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}SIGNAL(INT6_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = F_CPU/659.26/2; // 미의 음향을 연주한다
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}
SIGNAL(INT7_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = F_CPU/698.46/2; // 파의 음향을 연주한다
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}