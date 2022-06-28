/*
 * Digital Doorlock.c
 *
 * Created: 2022-06-24 오전 9:38:29
 * Author : PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "Lcd.h"

unsigned char keyscan();
unsigned char btn_check(unsigned char pw[]);
void Open_Door();
void Buzzer(unsigned char mode);
void check(unsigned char pw);
void Door_lock();

unsigned char PW[5] = "1111";
unsigned int DoReMi[8] = {523,587, 659, 698, 783,880, 987, 1046};

unsigned char signal = 0;
SIGNAL(INT7_vect)
{
	signal = ~signal;
}

int main(void)
{

    /*
	1.
	4개의 비밀번호를 설정, 키패드를 통해 4개의 패스워드 입력
	맞으면 스탭모터 구동, LCD에 open, 부저음 발생. 
	틀리면 LCD창에 ERROR NUMBER , 부저음 발생.
	
	2.
	INTERRUPT BUTTON을 누르면 통신을 통해 비밀번호 입력, 이후 동작은 동일

	*/
	
	
	
	DDRF = 0xF8;	//button
	PORTF = 0x07;	//0b 0000 0111
		
	DDRC = 0xFF;	//Motor
		
	DDRA = 0xFF;	//LCD
	DDRG = 0xFF;	//LCD 친구
		
	DDRB = 0x80;	//PIEZO
		
	//TCCR1A = 0x00; // WGM1(1:0) = “00”
	TCCR1B |= (1 << WGM13) | (1 << WGM12);// WGM1(3:2) = “11”
	TCCR1B |= (1 << CS10); // CS1(2:0) = “001” 1분주 사용
	TCCR1C = 0x00; // WGM1(3:0) = “1100”, CTC, 모드 12
		
	TCNT1 = 0x0000;
	
	EIMSK = 1 << INT7;
	//EICRA = 1 << ISC01 | 0 << ISC00;
	EICRB = 1 << ISC71;	//기본설정값이 0이다 => 0은 굳이 설정하지않아도 된다.
	//하강 엣지 :: Height -> Low LEVEL :: 버튼을 땔 때 동작
	//상승 엣지 :: Low -> Height LEVEL :: 버튼을 누를 때 동작
	
	sei();
	
	Lcd_Init();
	_delay_ms(500);
	Lcd_Clear();
	_delay_ms(15);
	while(1)
	{

		
		if(signal)
		{
			Door_lock();
		}
		else
		{	
			Lcd_Clear();
			_delay_ms(15);
			Lcd_Pos(0,0);
			Lcd_STR((unsigned char*)"***Locked***");
			
		}
		_delay_ms(1010);
		
	}
	
	return 0;
}

void Door_lock()
{
		
	unsigned char pw[5];
	unsigned char temp = 0;
	unsigned char temp02[15] = {0};
	int btn_cnt = 0;
	
	
	//while (1) 
	//{	
		Lcd_STR((unsigned char*)signal);
			
		//초기화
		for (int i =0 ; i <5 ; i++)
		{
			temp02[i] = 0;
			pw[i] = 0;
		}

		while (btn_cnt<4)
		{
			//버튼을 누르시오 :: 4개의 비밀번호를 설정, 키패드를 통해 4개의 패스워드 입력
			Lcd_Pos(0,0);
			Lcd_STR((unsigned char*)"Press Button");	//출력한다
			
			temp = keyscan();	//담는다
			
			
			
			if(temp != 0)
			{
				pw[btn_cnt] = temp;
			
				temp02[btn_cnt] = '*';
				Lcd_Pos(1,1);
				Lcd_STR(temp02);
				
				_delay_ms(1000);
				btn_cnt++;				
			}
		
		}
		

		
		if(btn_cnt == 4)
		{

			
			if(btn_check(pw) == 1)
			{
				//맞으면 스탭모터 구동, LCD에 OPEN 출력, 부저음 발생.
				Lcd_Clear();
				_delay_ms(15);
				
				Lcd_Pos(1,0);				
				Lcd_STR((unsigned char*)"OPEN");
				_delay_ms(1010);
								
				Buzzer(1);

				Open_Door();
			
			}
			else
			{
				//LCD창에 ERROR NUMBER , 부저음 발생.
				Lcd_Clear();
				_delay_ms(15);
				Lcd_Pos(1,0);
				Lcd_STR((unsigned char*)"WORNG");
				_delay_ms(1000);
				Buzzer(0);
				


			}	
			
			Lcd_Clear();
			_delay_ms(10);
			
			btn_cnt = 0;

		}
	//}
	

}


unsigned char keyscan()
{
	PORTF = 0x08; //0b 0000 1000
	_delay_ms(1);
	if((PINF & 0x07) == 0x01) return '1';	//0000 0111 & 0000 0001 = 000 0001 '1'
	else if((PINF & 0x07) == 0x02) return '2';
	else if((PINF & 0x07) == 0x04) return '3';
	_delay_ms(10);

	PORTF = 0x10;		// 0b 0001 0000
	_delay_ms(1);
	if((PINF & 0x07) == 0x01) return '4';
	else if((PINF & 0x07) == 0x02) return '5';
	else if((PINF & 0x07) == 0x04) return '6';
	_delay_ms(10);

	PORTF = 0x20;		// 0b 0010 0000
	_delay_ms(1);
	if((PINF & 0x07) == 0x01) return '7';
	else if((PINF & 0x07) == 0x02) return '8';
	else if((PINF & 0x07) == 0x04) return '9';
	_delay_ms(10);

	PORTF = 0x40;		// 0b 0100 0000
	_delay_ms(1);
	if((PINF & 0x07) == 0x01) return '*';
	else if((PINF & 0x07) == 0x02) return '0';
	else if((PINF & 0x07) == 0x04) return '#';
	_delay_ms(10);

	return 0;
	
	
	
}

unsigned char btn_check(unsigned char pw[])
{
	if(strcmp(pw,PW) == 0)
		return 1;
	else
		return 0;
	
	
}

void Open_Door()
{
	PORTC = 0x10;	// 0001 0000 => 1 step
	_delay_ms(1000) ;
			
	PORTC = 0x20;	//0010 0000 => 2 step
	_delay_ms(1000);
			
	PORTC = 0x40;	//0100 0000 => 3 step
	_delay_ms(1000);
			
	PORTC = 0x80;	//1000 0000 => 4 step
	_delay_ms(2000);
	
}

void Buzzer( unsigned char mode)
{
	
	if (mode == 1)
	{
		for (int i = 0;i<3;i++)
		{
			for(int i = 0 ; i < 3 ; i++ )
			{
				ICR1 = F_CPU / DoReMi[i];	//입력캡쳐시 TCNTx의 카운터 값을 지정 CTC MODE => TCNTx == TOP
				OCR1C = ICR1/2;		//듀티비(한 주기에서 High 비율 결정)
				TCCR1A |= 1<<COM1C0;
				_delay_ms(100);
				
			}
		}

			
	}
	else
	{
		ICR1 = F_CPU / DoReMi[7];	//입력캡쳐시 TCNTx의 카운터 값을 지정 CTC MODE => TCNTx == TOP
		OCR1C = ICR1/2;
		TCCR1A |= 1<<COM1C0;
		_delay_ms(3000);
		
	}
	
	TCCR1A = 0;
	
}

void check(unsigned char pw)
{
			Lcd_Clear();
			_delay_ms(10);
			Lcd_Pos(0,1);
			Lcd_STR(PW);
			_delay_ms(1000);
			Lcd_Pos(1,1);
			Lcd_STR(pw);
			_delay_ms(1000);
	
}