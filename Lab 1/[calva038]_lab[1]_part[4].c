/*
[calva038]_lab[1]_part[4].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #1  Exercise #4
*Exercise Description: Notifies the ride operator if the car is overburdened or unbalanced
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include <avr/io.h>
int main(void)
{
	DDRA = 0x00; // Configure port A's 8 pins as inputs
	DDRB = 0x00; // Configure port B's 8 pins as inputs
	DDRC = 0x00; // Configure port C's 8 pins as inputs
	DDRD = 0xFF; // Configure port D's 8 pins as outputs
	PORTA = 0xFF;
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0x00; // Initialize PORTD output to 0’s
	unsigned char weightActual = 0x00;
	unsigned char weightDif = 0x00;
	unsigned char tmpD = 0x00; // Temporary variable to hold the value of D
	while(1)
	{
		weightActual = (PINA + PINB + PINC);
		if (PINA > PINC){
			weightDif = (PINA - PINC);
		}
		else if (PINA < PINC){
			weightDif = (PINC - PINA);
		}
		// Checks if there is too much weight
		if (weightActual <= 0x8C){
			tmpD = (tmpD & 0xFE);
		}
		else if (weightActual > 0x8C){
			tmpD = (tmpD & 0xFE) | 0x01;
		}
		// Checks if A and C are balanced
		if (weightDif <= 0x50){
			tmpD = (tmpD & 0xFD);
		}
		else if (weightDif > 0x50){
			tmpD = (tmpD & 0xFD) | 0x02;
		}
		PORTD = tmpD;
	}
	return 0;
}