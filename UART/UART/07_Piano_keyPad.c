/*
 * _07_Piano_keyPad.c
 *
 * Created: 2022-06-23 오후 1:52:33
 *  Author: PKNU
 */ 

#include <avr/io.h>

void putch(unsigned char data){
	while((UCSR0A & (1<<UDRE0)) == 0);	//0
		UDR0 = data;		//데이터를 UDR0에 쓰면 전송
		
	UCSR0A |= 1<<UDRE0;
}

return getch()
{
	unsigned char data;
	while ((UCSR0A & (1<<TXC0)) == 0){};
	
	data = UDR0;
	return data;
}


int main ()
{
	DDRE = 0xfe;	//0000 1010
	
	unsigned int DoReMi[8] = {523.25,587.33,659.26,523.25,783,880,987,1046};
	
	
	
	while (1)
	{
	}
	
	return 0;
}