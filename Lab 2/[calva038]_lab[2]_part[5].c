/*
[calva038]_lab[2]_part[5].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #2  Exercise #5
*Exercise Description: Activates or deactivates a car airbag
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include <avr/io.h>
int main(void)
{
	DDRB = 0x06; // Configure port B's 8 pins as inputs, except PB1 and PB2
	DDRD = 0x00; // Configure port D's 8 pins as inputs
	PORTB = 0x00; // Initialize PORTB output to 0’s
	unsigned int cntavail = 0x00; // Temporary variable to hold the value of PORTB
	while(1)
	{
		cntavail = ((PIND << 1) + (PINB & 0x01)); // Set the temp value as a 9bit PD7-PD0PB0
		if (cntavail <= 0x05){ // Less than or equal to 5 lbs: no signals
			PORTB = (PORTB & 0x01) | 0x00;
		}
		else if ((cntavail > 0x05) && (cntavail < 0x46)){ // Between 5 and 70 lbs: Airbag disabled signal
			PORTB = (PORTB & 0x01) | 0x04;
		}
		else if (cntavail >= 0x46){ // Over 70 lbs: Airbag enabled signal
			PORTB = (PORTB & 0x01) | 0x02;
		}
	}
	return 0;
}