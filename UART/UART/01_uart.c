/*
 * UART.c
 * HyperTerminal에 메세지 출력
 * Created: 2022-06-21 오전 9:35:55
 * Author : PKNU
 */ 

#define F_CPU 14745600
#include <avr/io.h>

void putch(unsigned char data)
{
	
	while ((UCSR0A & 0x20) == 0);	//전송주니가 될 때 까지 대기
	UDR0 = data;					//데이터를 UDR0에 쓰면 전송
	UCSR0A |=0x20;
}

int main(void)
{
	//rx : 송신, tx : 수신
	
    unsigned char text[] = "Hello! World!! \r\n";
	unsigned char i = 0;
	
	DDRE = 0x02;			// Rx입력, tx 출력으로 설정 :: 데이터 시트 참고  0000 0110
	
	
	
	
	UCSR0A = 0x00;
	UCSR0B = 1<<RXEN0|1<<TXEN0;			//Rx, Tx enable 0001 1000
	UCSR0C = 0x06;			//비동기식 방식
	
	UBRR0H = 0x00;	
	UBRR0L = 3;			//115200 bps로 사용하겠다.
	
    while (text[i]!='\0') 
    {
		putch(text[i++]);
    }
	
	
}

