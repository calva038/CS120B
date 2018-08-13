/*
[calva038]_lab[1]_part[2].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #1  Exercise #2
*Exercise Description: Sets PC0-PC3 to display the number of cars based on PA0-PA3 inputs
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include <avr/io.h>
int main(void)
{
	DDRA = 0x00; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; // Configure port C's 8 pins as outputs
	PORTA = 0xFF;
	PORTC = 0x00; // Initialize PORTC output to 0’s
	unsigned char cntavail = 0x00; // Temporary variable to hold the value of C
	while(1)
	{
		// Sets PC0-PC3 to display the number of cars based on PA0-PA3 inputs
		if (PINA == 0x00){
			cntavail = (cntavail & 0xF8); // Sets tmpC to ccccccc0 (clear rightmost bit)
		}
		else if ((PINA == 0x01) || (PINA == 0x02) || (PINA == 0x04) || (PINA == 0x08)){
			cntavail = (cntavail & 0xF8) | 0x01; // Sets tmpC to 00000001 (sets PC0 to 1)
		}
		else if ((PINA == 0x03) || (PINA == 0x05) || (PINA == 0x06) || (PINA == 0x09) || (PINA == 0x0A) || (PINA == 0x0C)){
			cntavail = (cntavail & 0xF8) | 0x02; // Sets tmpC to 00000010 (sets PC1 to 1)
		}
		else if ((PINA == 0x07) || (PINA == 0x0B) || (PINA == 0x0D) || (PINA == 0x0E)){
			cntavail = (cntavail & 0xF8) | 0x03; // Sets tmpC to 00000011 (sets PC0 and PC1 to 1)
		}
		else if (PINA == 0x0F){
			cntavail = (cntavail & 0xF8) | 0x04; // Sets tmpC to 00000100 (sets PC2 to 1)
		}
		PORTC = cntavail;
	}
	return 0;
}