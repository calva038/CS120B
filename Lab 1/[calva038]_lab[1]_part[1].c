/*
[calva038]_lab[1]_part[1].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #1  Exercise #1
*Exercise Description: If PA0 is 1 and PA1 is 0, set PB0=1, else = 0
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include <avr/io.h>
int main(void)
{
DDRA = 0x00; // Configure port A's 8 pins as inputs
DDRB = 0xFF; // Configure port B's 8 pins as outputs
PORTA = 0xFF;
PORTB = 0x00; // Initialize PORTB output to 0’s
unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
while(1)
{
	// if PA0 is 1 and PA1 is 0, set PB0=1, else = 0
	if ((PINA & 0x00) | (PINA & 0x02)){
		tmpB = (tmpB & 0xFE); // Sets tmpB to bbbbbbb0 (clear rightmost bit)
	}
	else if (PINA == 0x01){
		tmpB = (tmpB & 0xFE) | 0x01; // Sets tmpB to bbbbbbb1 (clear rightmost bit, then set to 1)
	}
	PORTB = tmpB;
}
return 0;
}