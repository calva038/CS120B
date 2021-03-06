#include <avr/io.h>

// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-top most one
// Keypad must be connected to port C
/* Keypad arrangement
		PC4 PC5 PC6 PC7
	col  1   2   3   4
row
PC0 1   1 | 2 | 3 | A
PC1 2   4 | 5 | 6 | B
PC2 3   7 | 8 | 9 | C
PC3 4   * | 0 | # | D
*/

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k){
	return((x & (0x01 << k))!= 0);
}

unsigned char GetKeypadKey(){
	PORTD = 0xEF;
	// Enable col 4 with 0, disable others with 1�s
	asm("nop");
	// add a delay to allow PORTC to stabilize before checking
	if (GetBit(PIND,0)==0){
		return ('1');
	}
	if (GetBit(PIND,1)==0){
		return ('4');
	}
	if (GetBit(PIND,2)==0){
		return ('7');
	}
	if (GetBit(PIND,3)==0){
		return ('*');
	}
	// Check keys in col 2
	PORTD = 0xDF;
	// Enable col 5 with 0, disable others with 1�s
	asm("nop");
	// add a delay to allow PORTC to stabilize before checking
	if (GetBit(PIND,0)==0){
		return ('2');
	}
	if (GetBit(PIND,1)==0){
		return ('5');
	}
	if (GetBit(PIND,2)==0){
		return ('8');
	}
	if (GetBit(PIND,3)==0){
		return ('0');
	}
	PORTD = 0xBF;
	// Enable col 6 with 0, disable others with 1�s
	asm("nop");
	// add a delay to allow PORTC to stabilize before checking
	if (GetBit(PIND,0)==0){
		return ('3');
	}
	if (GetBit(PIND,1)==0){
		return ('6');
	}
	if (GetBit(PIND,2)==0){
		return ('9');
	}
	if (GetBit(PIND,3)==0){
		return ('#');
	}
	PORTD = 0x7F;
	// Enable col 7 with 0, disable others with 1�s
	asm("nop");
	// add a delay to allow PORTC to stabilize before checking
	if (GetBit(PIND,0)==0){
		return ('A');
	}
	if (GetBit(PIND,1)==0){
		return ('B');
	}
	if (GetBit(PIND,2)==0){
		return ('C');
	}
	if (GetBit(PIND,3)==0){
		return ('D');
	}
	// ... *****FINISH*****
	// Check keys in col 3
	PORTD = 0xBF;
	// Enable col 6 with 0, disable others with 1�s
	asm("nop");
	// add a delay to allow PORTC to stabilize before checking
	// ...*****FINISH*****
	// Check keys in col 4
	// ...*****FINISH*****
	return ('\0');
	// default value
}

int main(void){
	unsigned char x;
	DDRB = 0xFF;
	PORTB = 0x00;
	// PORTB set to output, outputs init 0s
	DDRD = 0xF0;
	PORTD = 0x0F;
	// PC7..4 outputs init 0s, PC3..0 inputs init 1s
	while (1){
		x = GetKeypadKey();
		switch (x){
			case '\0':
			PORTB = 0x1F;
			break;
			// All 5 LEDs on
			
			case '1':
			PORTB = 0x01;
			break;
			// hex equivalent
			
			case '2':
			PORTB = 0x02;
			break;
			// . . .***** FINISH *****
			
			case '3':
			PORTB = 0x03;
			break;
			// . . .***** FINISH *****
			
			case '4':
			PORTB = 0x04;
			break;
			// . . .***** FINISH *****
			
			case '5':
			PORTB = 0x05;
			break;
			// . . .***** FINISH *****
			
			case '6':
			PORTB = 0x06;
			break;
			// . . .***** FINISH *****
			
			case '7':
			PORTB = 0x07;
			break;
			// . . .***** FINISH *****
			
			case '8':
			PORTB = 0x08;
			break;
			// . . .***** FINISH *****
			
			case '9':
			PORTB = 0x09;
			break;
			// . . .***** FINISH *****
			
			case 'A':
			PORTB = 0x0A;
			break;
			// . . .***** FINISH *****
			
			case 'B':
			PORTB = 0x0B;
			break;
			// . . .***** FINISH *****
			
			case 'C':
			PORTB = 0x0C;
			break;
			// . . .***** FINISH *****
			
			case 'D':
			PORTB = 0x0D;
			break;
			
			case '*':
			PORTB = 0x0E;
			break;
			
			case '0':
			PORTB = 0x00;
			break;
			
			case '#':
			PORTB = 0x0F;
			break;
			
			default:
			PORTB = 0x1B;
			break;
			//  Should  never  occur.  Middle  LED off.
		}
	}
}