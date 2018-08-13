/*
[calva038]_lab[2]_part[3].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #2  Exercise #3
*Exercise Description: Displays the fuel level of a car and seatbelt warning
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
		// Sets PC0-PC5 to display the fuel level of a car
		if (PINA == 0x00){
			cntavail = (cntavail & 0x00) | 0x40; // Sets tmpC to 01000000 (clears bits and sets PC6 to 1) 
		}
		else if ((PINA == 0x01) || (PINA == 0x02)){
			cntavail = (cntavail & 0x00) | 0x60; // Sets tmpC to 01100000 (sets PC5 and PC6 to 1)
		}
		else if ((PINA == 0x03) || (PINA == 0x04)){
			cntavail = (cntavail & 0x00) | 0x70; // Sets tmpC to 01110010 (sets PC5PC4 and PC6 to 1)
		}
		else if ((PINA == 0x05) || (PINA == 0x06)){
			cntavail = (cntavail & 0x00) | 0x38; // Sets tmpC to 00111000 (sets PC5-PC3 to 1)
		}
		else if ((PINA == 0x07) || (PINA == 0x08) || (PINA == 0x09)){
			cntavail = (cntavail & 0x00) | 0x3C; // Sets tmpC to 00111100 (sets PC5-PC2 to 1)
		}
		else if ((PINA == 0x0A) || (PINA == 0x0B) || (PINA == 0x0C)){
			cntavail = (cntavail & 0x00) | 0x3E; // Sets tmpC to 00111110 (sets PC5-PC1 to 1)
		}
		else if ((PINA == 0x0D) || (PINA == 0x0E) || (PINA == 0x0F)){
			cntavail = (cntavail & 0x00) | 0x3F; // Sets tmpC to 00111111 (sets PC5-PC0 to 1)
		}
		// Displays a "Fasten seatbelt" signal if the key is in the ignition and the driver is seated
		if (!(PINA & 0x40)){
			if (PINA & 0x30){
				cntavail = (cntavail & 0x7F) | 0x80;
			}
			else{
				cntavail = (cntavail & 0x7F);
			}
		}
		else{
			cntavail = (cntavail & 0x7F);
		}
		PORTC = cntavail;
	}
	return 0;
}