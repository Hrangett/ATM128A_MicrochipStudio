/*
 * _03.c
 *
 * Created: 2022-06-22 오후 3:13:36
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>


unsigned char FND_DATA[] ={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,
							0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,
							0X79,0X71,0X08,0X80};

volatile unsigned char time_s=0; // 초를 세는 변수
volatile unsigned char FND_flag=0, edge_flag = 0;

int main()
{
	DDRA = 0xFF;
	DDRE = 0x00;
	
	
	TCCR3A = 0x00;	//normal, OCn 분리
	//TCCR3B = 0x45;
	TCCR3B =  1<<ICES3 |1<<CS32 | 1<<CS30;		//0100 0101 :: 분주비(프리스케일러) 1024,  1로 설정시, 상승(양)에지에서 검출, 0은 하강엣지에서 검출
	ETIMSK = 0x20;
	ETIFR |= 1<< ICF3;
	
	sei();
	
	PORTA = FND_DATA[0];
	
	while (1) 
	{
		if(FND_flag) 
		{
			if(time_s > 15) // 최대 1.5초까지 표시(F)
			time_s = 15;
			PORTA = FND_DATA[time_s]; // 포트A에 FND Table 값 출력
			FND_flag = 0;
		}
	}
	return 0;
}

SIGNAL(TIMER3_CAPT_vect)
{
	
	cli();
	
	unsigned int count_check;
	
	if(edge_flag == 0)
	{
		
		TCCR3B = 0x05;
		TCNT3 = 0;
		ICR3 = 0;
		edge_flag = 1;
	}
	else
	{
		TCCR3B = 0x45;
		count_check = ICR3;
		
		time_s = count_check / 720;
		
		FND_flag = 1;
		edge_flag = 0;
		
	}
	sei();
}