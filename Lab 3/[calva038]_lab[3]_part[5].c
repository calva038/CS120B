/*[calva038]_lab[3]_part[5].c-[8/10/18]
*Name & E-mail: Christian Alvarado, calva038@ucr.edu
*CS Login: calva038
*Partner(s) Name & E-mail: N/A
*Lab Section: B22
*Assignment: Lab #3  Exercise #5
*Exercise Description: Digital deadbolt system
*
*I acknowledge all content contained herein, excluding template or example
*code, is my own original work.
*/

#include <avr/io.h>
enum States {Start, Wait, Xon, Yon, poundKey, Inside, Unlock} state;
char Lock, Xoff, Yoff, Poundoff, count = 0;
char code[4] = {'#', 'X', 'Y', 'X'};
char codeInput[4] = {'0','0','0','0'};
int i;

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
			Lock = 0;
			state = Inside;	
		}
		else if ((code[0] == codeInput[0]) & (code[1] == codeInput[1]) & (code[2] == codeInput[2]) & (code[3] == codeInput[3])){
            if (count == 0){
			if (Lock == 0){
				Lock = 1;
                count = 1;
                for (i=0; i < 4; i++){
                  codeInput[i] = 0;	
                }
				state = Unlock;
			}
			else if (Lock == 1){
				Lock = 0;
                count = 0;
                for (i=0; i < 4; i++){
                  codeInput[i] = 0;	
                }
				state = Inside;
			}
			}
            else{
            state = Wait;
                }
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
        count = 0;
		for (i=0; i < 4; i++){
			if (codeInput[i] == '0'){
				codeInput[i] = 'X';
				Xoff = 1;
				break;
			}
		}
        if (Xoff == 1){
            break;
        }
        else{
		for (i=0; i < 3; i++){
			codeInput[i] = codeInput[i+1];
		}
		codeInput[3] = 'X';
		Xoff = 1;
		break;
        }
		
		case Yon:
        count = 0;
		for (i=0; i < 4; i++){
			if (codeInput[i] == '0'){
				codeInput[i] = 'Y';
				Yoff = 1;
				break;
			}
		}
        if (Yoff == 1){
        break;
            }
        else{
		for (i=0; i < 3; i++){
			codeInput[i] = codeInput[i+1];
		}
		codeInput[3] = 'Y';
		Yoff = 1;
		break;
        }
		
		case poundKey:
        count = 0;
		for (i=0; i < 4; i++){
			if (codeInput[i] == '0'){
				codeInput[i] = '#';
				Poundoff = 1;
				break;
			}
		}
        if (Poundoff == 1){
        break;
            }
        else{
		for (i=0; i < 3; i++){
			codeInput[i] = codeInput[i+1];
		}
		codeInput[3] = '#';
		Poundoff = 1;
		break;
		}
        
		case Inside:
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
