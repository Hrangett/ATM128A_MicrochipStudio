/*
 * _02_PWM_TC.c
 *
 * Created: 2022-06-22 오후 5:04:35
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int Light = 0;
volatile unsigned char Light_flag = 1;

int main()
{
	DDRB = 0x80;
	
	DDRE = 0x00;
	
	//TCCR2 = (1<<WGM01 | 1<<COM01 | 1<<CS01);//	0110 0010  0111 0111
	TCCR2 = 0x62;
	// WGM : 010 =>	PC PWM 모드
	//		 PWM 주기 : F_CPU/256/2/8 = 3.6 KHz
	// CS01 : 010 => 분주비 8
	//COM01 : 업카운트시 Clear, 다운카운트시 Set 으로 설정
	
	TCNT2 = 0x00;	//
	
	EICRB = 0xFF;	//4567 interrupt hight edge
	EIMSK = 0xf0;	//4567 interrupt 
	EIFR = 0xF0;	//4567 interrupt clear
	
	sei();
	
	while(1)
	{
		if(Light_flag)
		{			
			OCR2 = Light;
			Light_flag = 0;
		}
		
	}
	
	return 0;
}

SIGNAL(INT5_vect)
{
	cli();
	Light -= 51;	//LED 밝기 감소
	if(Light <0 )
	Light = 0;
	Light_flag = 1;
	sei();
	
}

SIGNAL(INT6_vect)
{
	cli();
	Light += 51;	//LED 밝기 증가
	if(Light >255 )
	Light = 255;
	Light_flag = 1;
	sei();
	
}
SIGNAL(INT7_vect)
{
	
	cli();
	Light = 255;
	Light_flag = 1;
	sei();
}