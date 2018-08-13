/*[calva038]_lab[3]_part[2].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #3  Exercise #2
*Exercise Description: Counting up and down
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include <avr/io.h>
enum States {Start, Wait, PA0on, PA1on, Reset} state;
char tmp, count0, count1 = 0;

void Tick(){

	switch(state){ // Transitions
		case Start:
		state = Wait;
		break;
		
		case Wait:
		PORTB = tmp;
		if ((!(PINA & 0x01)) & (!(PINA & 0x02))){
			count0 = 0;
			count1 = 0;
			state = Wait;
		}
		else if ((PINA & 0x01)){
			if (!(PINA & 0x02)){
				count1 = 0;
				if (count0 == 0){
					count0 = 1;
					state = PA0on;
				}
				else if (count0 == 1){
					state = Wait;
			}
			else {
				state = Reset;
				}
			}
		}
		else{
			count0 = 0;
			if (count1 == 0){
				count1 = 1;
				state = PA1on;
			}
			else if (count1 == 1){
				state = Wait;
			}
		}
		break;
		
		case PA0on:
		state = Wait;
		break;
		
		case PA1on:
		state = Wait;
		break;
        
        case Reset:
		state = Wait;
		break;
		
		default:
		state = Start;
		break;
	} // Transitions

	switch(state) { //State actions
		case PA0on:
        if (tmp < 9){
         tmp++;
        }
        else if (tmp == 9){
        }
		break;
		
		case PA1on:
		if (tmp > 0){
         tmp--;
        }
        else if (tmp == 0){
        }
		break;
        
        case Reset:
        tmp = 0x00;
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
