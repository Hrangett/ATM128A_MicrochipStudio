/*
 * _02_uart.c
 * button 누를 시 HyperTerminal에 해당 포트에 입력된 값 출력
 * Created: 2022-06-21 오전 10:36:43
 *  Author: PKNU
 */ 

#define F_CPU=14745600
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TX_flag = 0;
volatile char TX_data = 0;

void putch(unsigned char data)
{
	while ((UCSR0A & 0x20) == 0);
	
	UDR0 = data;
	UCSR0A |=0x20;
	
}

void putch_Str(char *str)
{
	unsigned char i = 0;
	while(str[i]!='\0')
	putch(str[i++]);
	
}

int main()
{
	DDRE = 0x02;	//0000 0010  Rx(입력 : 0), Tx(출력 : 1), SW0~3 입력
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;	//Rx, Tx enable
	UCSR0C = 0x06;	//비동ㅇ기 방식, 노 패리티비트, 1 스톱 비트
	UBRR0H = 0x00;
	UBRR0L = 3;		//115200 bps
	
	EICRB = 0xff;	//인터럽트 4,5,6,7을 상승엣지에서 동작하도록 설정
	EIMSK = 0xF0;	//인터럽트 4,5,6,7 허용
	EIFR = 0XF0;	//인터럽트 4,5,6,7 플래그를 클리어
	sei();
	
	while (1)
	{
		if(TX_flag == 1)
		{
			putch_Str("\n\r Input Switch : ");
			putch(TX_data);
			TX_flag = 0;
			
		}
	}

}

SIGNAL(INT4_vect)	//인터럽트 서비스 루틴
{
	
	cli();			//전체 인터럽트를 금지
	TX_data = '0';	//문자 0을 저장
	TX_flag = 1;	
	sei();			//전체 인터럽트 허용
}

SIGNAL(INT5_vect)
{
	cli();			//전체 인터럽트를 금지
	TX_data = '1';	//문자 1을 저장
	TX_flag = 1;
	sei();			//전체 인터럽트 허용
}

SIGNAL(INT6_vect)
{
	cli();			//전체 인터럽트를 금지
	TX_data = '2';	//문자 2을 저장
	TX_flag = 1;
	sei();			//전체 인터럽트 허용
}

SIGNAL(INT7_vect)
{
	cli();			//전체 인터럽트를 금지
	TX_data = '3';	//문자 3을 저장
	TX_flag = 1;
	sei();			//전체 인터럽트 허용
}