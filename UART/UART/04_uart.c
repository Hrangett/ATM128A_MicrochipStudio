/*
 * _04_uart.c
 * HyperTerminal을 이용한 숫자 키보드 입력시 FND에 숫자 출력
 * Created: 2022-06-21 오전 11:59:09
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TX_flag = 0;
volatile char TX_data = 0;
unsigned char FND_DATA_TBL[] = {0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X27,0X7F,0X6F,0X77,0X7C,0X39,0X5E,0X79,0X71,0x08,0x80};

void putch(unsigned char data)
{
	while((UCSR0A&0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch(void)
{
	unsigned char data;
	while ((UCSR0A & 0x80) == 0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

int main()
{
	
	unsigned char RX_data = 0;
	DDRE = 0x0E;	//0000 1110 Rx(입력 0), Tx(출력 1)
	DDRA = 0xFF;	//출력포트
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	while(1)
	{
		RX_data = getch();	//Rx로 부터 입력받은 데이터를 변수 Rx_data에 저장
		
		if ((RX_data >= 0x30) && (RX_data <=0x39))	//0~9
		{
			PORTA = FND_DATA_TBL[RX_data - 0x30];	//0x03 == 0
		}
	}
}

