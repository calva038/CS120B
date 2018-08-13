/*
[calva038]_lab[2]_part[4].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #2  Exercise #4
*Exercise Description: Displays nibbles of PINA on pins B and C
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include <avr/io.h>
int main(void)
{
	DDRA = 0x00; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; // Configure port B's 8 pins as outputs
	DDRC = 0xFF; // Configure port C's 8 pins as outputs
	PORTB = 0x00; // Initialize PORTB output to 0’s
	PORTC = 0x00; // Initialize PORTB output to 0’s
	while(1)
	{
		PORTB = (PINA >> 4); // Upper nibble of A is lower nibble of B
		PORTC = (PINA << 4); // Lower nibble of A is upper nibble of C
	}
	return 0;
}