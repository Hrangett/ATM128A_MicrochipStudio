/*
 * fnd02.c
 *
 * Created: 2022-06-17 오후 4:54:48
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

/*
int main()
{
	int i = 0;
	
	int fnd_arr[] = {0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X27};
	int btn_arr[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

	int num = 0;

	DDRD = 0x00;
	DDRA = 0xFF;
	while (1)
	{
		num = PIND;
		
		for (i = 0; i<8 ; i++)
		{
			if(btn_arr[i] == num)	
			{
				PORTA = fnd_arr[i];
				_delay_ms(10);
				PORTA = 0x00;
				break;
				
			}
		}
		

		
		
	}
	
	
	return 0;
}
*/

