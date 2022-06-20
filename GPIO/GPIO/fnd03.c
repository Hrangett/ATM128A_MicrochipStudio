/*
 * fnd03.c
 * 타이머를 만들자
 * Created: 2022-06-17 오후 5:58:34
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#define NUMBER 1000
#include <avr/io.h>
#include <util/delay.h>

int main ()
{
	//Andoe
	
	DDRA = 0xFF;	
	DDRD = 0xFF;
	
	int dlf,tlq,qor,cjs;

	int tmp, lef;
		
	int arr[] = {0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X27,0X7F,0X6F,0X77,0X7C,0X39,0X5E,0X79,0X71};
		
	tmp = NUMBER;
	
	while (1)
	{
		/*
		//1111 1110
		//PORTA = 0xFE;	//C0
		
		//1111 1101
		//PORTA = 0xFD;	//C1
		
		//1111 1011
		//PORTA = 0xFB;	//C2
		
		//1111 0111
		//PORTA = 0xF7;	//C0
	*/
		
		if(tmp == 0) tmp = NUMBER;
		
		cjs = tmp / 1000;
		
		qor =( tmp % 1000 ) / 100;
		
		tlq = ( tmp % 100) / 10 ;
		
		dlf = tmp % 10 ;

		
		for (int i = 0 ; i<(100/4) ;i++)
		{
			
			PORTA = 0xFE;	//C0
			PORTD = arr[cjs];
			_delay_ms(1);
		
		
			PORTA = 0xFD;	//C1
			PORTD = arr[qor];
			_delay_ms(1);
		
		
			PORTA = 0xFB;	//C2
			PORTD = arr[tlq];
			_delay_ms(1);
		
						
			PORTA = 0xF7;	//C3
			PORTD = arr[dlf];
			_delay_ms(1);
		
		}
		
		tmp--;

	}
	
	
	return 0;
}
