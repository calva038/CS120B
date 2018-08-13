/*[calva038]_lab[3]_part[3].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #3  Exercise #4
*Exercise Description: Digital deadbolt system
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include <avr/io.h>
enum States {Start, Wait, Xon, Yon, poundKey, Inside, Unlock} state;
char Lock, Xoff, Yoff, Poundoff, count0, count1 = 0;

void Tick(){

	switch(state){ // Transitions
		case Start:
		state = Wait;
		break;
		
		case Wait:
		if ((!(PINA & 0x01))){
			Xoff = 0;
		}
		if ((!(PINA & 0x02))){
			Yoff = 0;
		}
		if ((!(PINA & 0x04))){
			Poundoff = 0;
		}
		if ((PINA & 0x80)){
			state = Inside;	
		}
		if (PINA > 0x00){
		if ((PINA == 0x01)){
			if (Xoff == 0){
				state = Xon;
			}
			else if (Xoff == 1){
				state = Wait;
			}
		}
		else if ((PINA == 0x02)){
			if (Yoff == 0){
				state = Yon;
			}
			else if (Yoff == 1){
				state = Wait;
			}
		}
		else if ((PINA == 0x04)){
			if (Poundoff == 0){
				state = poundKey;
			}
			else if (Poundoff == 1){
				state = Wait;
			}
		}
		else{
			state = Wait;
		}
		}
		else if (PINA == 0x00){
		if ((count0 == 1) & (count1 == 1)){
			if (Lock == 0){
				Lock = 1;
				count0 = 0;
				count1 = 0;
				state = Unlock;
			}
			else if (Lock == 1){
				Lock = 0;
				state = Inside;
			}
		}
		else{
			state = Wait;
		}
		}
		
		break;
		
		case Xon:
		state = Wait;
		break;
		
		case Yon:
		state = Wait;
		break;
		
		case poundKey:
		state = Wait;
		break;
		
		case Inside:
		state = Wait;
		break;
		
		case Unlock:
		state = Wait;
		break;
		
		default:
		state = Start;
		break;
	} // Transitions

	switch(state) { //State actions
		case Xon:
		count0 = 0;
		Xoff = 1;
		break;
		
		case Yon:
		if ((count0 == 1) & (Poundoff == 1)){
			count1 = 0;
		}
		else if ((count0 == 1) & (Poundoff == 0)){
			count1 = 1;
		}
		Yoff = 1;
		break;
		
		case poundKey:
		count0 = 1;
		Poundoff = 1;
		break;
		
		case Inside:
		count0 = 0;
		count1 = 0;
		PORTB = 0x00;
		break;
		
		case Unlock:
		PORTB = 0x01;
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
