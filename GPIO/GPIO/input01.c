/*
 * input01.c
 *
 * Created: 2022-06-17 오후 3:20:14
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

/*
int main()
{
	DDRD = 0x00;	//portD input
	DDRA = 0xff;	//portA output
	int P_NUM;
	
	while (1)
	{
		P_NUM = PIND;
		PORTA = P_NUM;
		_delay_ms(300);
		PORTA = 0x00;

	}
	
	return 0;
}
*/


