/*
 * LCD.c
 *
 * Created: 2022-06-20 오후 2:54:41
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Lcd.h"

bool signal = false;

SIGNAL(INT5_vect)
{
	signal = !signal;
	
}


int main(void)
{

	DDRA = 0xFF;	//출력용
	DDRG = 0xFF;
	
	DDRE = 0x00;	//입력
	
	EIMSK = 1<<INT5;
	
	EICRB = 1<<ISC51;
	
	sei();
	
	Lcd_Init();
	_delay_ms(500);
	
	Lcd_Clear();
	_delay_ms(15);
	
	Byte str2[] = "GuguDan";

	Byte *mul[16] ;

	int i = 8;
	int j = 1;
	
	while (1)
	{

		while (i<=9)
		{
			while(j<=9)
			{
				
				sprintf((char*)mul,"%d * %d = %d",i,j,i*j);
				if(signal)
				{
					//구구단을 해당시점에서 멈춤, lcd창에 interrupt 발생 문구 출력
					Lcd_Clear();
					_delay_ms(15);
					
					Lcd_Pos(0,0);
					Lcd_STR((unsigned char*)"INTERRUPT");
					
					_delay_ms(2000);
				}
				else
				{
					Lcd_Pos(0,0);
					Lcd_STR(str2);
					Lcd_Pos(1,0);
					Lcd_STR((unsigned char* )mul);
						
					_delay_ms(3000);
					Lcd_Clear();
					_delay_ms(5);
						
					j++;
				}

			}
			i++; j = 1;
		}
		i = j = 1;
		
    }
}

