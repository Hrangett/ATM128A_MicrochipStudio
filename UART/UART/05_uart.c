/*
 * _05_uart.c
 * 구구단을 외자
 * Created: 2022-06-21 오후 12:20:01
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <stdio.h>

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
	
}

void putch_Str(char *str){
	int i = 0;
	
	while(str[i] != '\0'){
		putch(str[i++]);
	}
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
	//DDRE = 0xfe;	//1111 1110 Rx ( 입력 0), Tx(출력,1)
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;	//Rx,Tx enable
	UCSR0C = 0x06;	//비동기 방식, no Parity bit, 1 Stop bit
	
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	unsigned char gugu[] = "NUM >> ";
	unsigned char gugu_i = 0;
	
	unsigned char RX_data = 0;
	int RX_data_to_int = 0;
	int j = 0;
	
	unsigned char mul[50];
	
	while (1)
	{

		putch_Str(gugu);
		RX_data = getch();
		putch((RX_data));
		
		RX_data_to_int = RX_data - 0x30;
	
		
		while (j != 10)
		{
			
			sprintf(mul,"\r%d * %d = %d\n", RX_data_to_int, j, RX_data_to_int * j);
			putch_Str(mul);
			j++;
			
		}
		j = 0;
		
	}
	return 0;
	
}
