/*
[calva038]_lab[2]_part[1].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #2  Exercise #1
*Exercise Description: Counts the number of bits with the value 1 on pins A and B
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include<avr/io.h>
// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) { 
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k){
	return((x & (0x01 << k))!= 0);
	}

int main(void)
{
	DDRA = 0x00; // Configure port A's 8 pins as inputs
	DDRB = 0x00; // Configure port B's 8 pins as inputs
	PORTA = 0x00;
	PORTB = 0x00; // Initialize PORTB input to 0’s
	DDRC = 0xFF; // Configure port C's 8 pins as outputs
	PORTC = 0x00;
	unsigned char tmpC = 0x00; // Temporary variable to hold the value of C
	while(1)
	{
			tmpC = 0x00;
			if (GetBit(PINA, 0)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINA, 1)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINA, 2)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINA, 3)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINA, 4)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINA, 5)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINA, 6)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINA, 7)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINB, 0)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINB, 1)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINB, 2)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINB, 3)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINB, 4)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINB, 5)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINB, 6)){
				tmpC = tmpC + 1;
			}
			if (GetBit(PINB, 7)){
				tmpC = tmpC + 1;
			}
		PORTC = tmpC;
	}
	return 0;
}