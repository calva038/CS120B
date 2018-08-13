/*[calva038]_lab[3]_part[1].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #3  Exercise #1
*Exercise Description: LED flip flop
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include <avr/io.h>
enum States {Start, PB0on, PB1on} state;
char count = 0;

void Tick(){

	switch(state){ // Transitions
		case Start:
			state = PB0on;
			break;
		
		case PB0on:
			if (count == 0){
				if (PINA && 0x01){
                    count = 1;
					state = PB1on;
				}
				else if (!(PINA && 0x01)){
					state = PB0on;
				}
			}
			else if (count == 1){
				if (!(PINA && 0x01)){
					count = 0;
					state = PB0on;
				}
				else if (PINA && 0x01){
					state = PB0on;
				}
			}
			break;
		
		case PB1on:
			if (count == 0){
				if (!(PINA && 0x01)){
                    count = 1;
					state = PB0on;
				}
				else if ((PINA && 0x01)){
					state = PB1on;
				}
			}
			else if (count == 1){
				if ((PINA && 0x01)){
					count = 0;
					state = PB1on;
				}
				else if (!(PINA && 0x01)){
					state = PB1on;
				}
			}
			break;
		
		default:
			state = Start;
			break;
	} // Transitions

	switch(state) { //State actions
		case PB0on:
			PORTB = 0x01;
		break;
		
		case PB1on:
            PORTB = 0x02;
		break;
		
		default:
		break;
	} // State actions
}

int main(){
	PORTB = 0x00; //Initializes outputs
	state = Start; // Indicates initial call
	while(1) { Tick();}
	return 0;
}
