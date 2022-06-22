/*
 * _05_uart.c
 * 구구단을 외자
 * Created: 2022-06-21 오후 12:20:01
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <stdio.h>

//문자열 출력
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

//출력할 구구단 입력
unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);
	data = UDR0;
	UCSR0A |= 0x80;	//
	return data;
}

int main()
{
	DDRE = 0xfe;	//1111 1110 Rx ( 입력 0), Tx(출력,1)
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;	//Rx,Tx enable
	UCSR0C = 0x06;	//비동기 방식, no Parity bit, 1 Stop bit
	
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	/*
	
	unsigned char text[] =
	"\r\nWelcom! edgeiLAB\r\n USART 0 Test Program.\r\n";
	
	unsigned char echo[] = "ECHO >> ";
	unsigned char i = 0;
	
	
	while(text[i]!='\0')
	{putch_Str(text[i++]);}	//text문자열 출력
	
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
*/
	
	unsigned char gugu[] = "NUM >> ";
	unsigned char gugu_i = 0;
	
	
	while (gugu[gugu_i]!='\0')
	{
		putch(gugu[gugu_i++]);
	}
	
	gugu_i = 0;
	

	unsigned char RX_data = 0;
	unsigned char *mul = 0;
	unsigned char *str = 0;
	unsigned char mul_i = 0;
	



	
	while (1)
	{

		RX_data = getch();
		putch(RX_data);
		 
		
		
	}
	
	return 0;
	
}
