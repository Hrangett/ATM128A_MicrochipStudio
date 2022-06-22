/*
 * _03_uart.c
 * HyperTerminal 을 이용한 Echo Server
 * Created: 2022-06-21 오전 11:22:16
 *  Author: PKNU
 */ 

#include <avr/io.h>

//문자열 출력
void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);	//전송준비가 될 때까지 대기
	UDR0 = data;					//데이터를 UDR0에 쓰면 전송
	UCSR0A |= 0x20;					
	
}

unsigned char getch()
{
	unsigned char data;
	while ((UCSR0A & 0x80)==0);		//데이터 받을 떄 까지 대기
	data = UDR0;					// 수신된 데이터는 UDR0에 저ㅏㅇ
	UCSR0A|=0x80;					// UCSR0A or 0100 0000						
	return data;					//읽어온 문자 바ㄴ환
}


int main()
{

	DDRE = 0xfe;	//1111 1110 Rx ( 입력 0), Tx(출력,1)
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;	//Rx,Tx enable
	UCSR0C = 0x06;	//비동기 방식, no Parity bit, 1 Stop bit
	
	UBRR0H = 0x00;
	UBRR0L = 3;
	
		
	unsigned char text[] =
	"\r\nWelcom! edgeiLAB\r\n USART 0 Test Program.\r\n";
	
	unsigned char echo[] = "ECHO >> ";
	unsigned char i = 0;
		
	
	while(text[i]!='\0')
	{putch(text[i++]);}	//text문자열 출력
	
	i=0;
	while (echo[i]!='\0')
	{
		putch(echo[i++]);	//저장된 echo 문자열을 출력
	}
	
	while (1)
	{
		putch(getch());
		//getch()로 입력받은 문자를 다시 putch()로 문자열 출력
	}
	
	return 0;
}
