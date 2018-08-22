#include <avr/io.h>

enum States {Start, Wait, PA0on, PA0off, PA1on, PA1off} state;
char tmp = 0;
short timer = 0;
unsigned char button = 0x00;
unsigned char stateNum = 0x00;

void Tick(){

	switch(state){ // Transitions
		case Start:
		state = PA0on;
		break;
		
		case Wait:
		if ((button) && (stateNum < 2)){
			timer = 0;
			state = PA1on;
			break;
		}
		else if ((button) && (stateNum > 1)){
			timer = 0;
			state = PA0on;
			break;
		}
		if (timer < 25000){
			timer++;
			state = Wait;
			break;
		}
		else{
		if (stateNum == 0){
			timer = 0;
			state = PA0on;
			break;
		}
		if (stateNum == 1){
			timer = 0;
			state = PA0off;
			break;
		}
		if (stateNum == 2){
			timer = 0;
			state = PA1on;
			break;
		}
		if (stateNum == 3){
			timer = 0;
			state = PA1off;
			break;
		}
	}
		break;
		
		case PA0on:
		if (!(button)){
			stateNum = 1;
			state = Wait;
			break;
		}
		else{
			stateNum = 2;
			state = Wait;
			break;
		}
		break;
		
		case PA0off:
		if (!(button)){
			stateNum = 0;
			state = Wait;
			break;
		}
		else{
			stateNum = 2;
			state = Wait;
			break;
		}
		break;
		
		case PA1on:
		if (!(button)){
			stateNum = 3;
			state = Wait;
			break;
		}
		else{
			stateNum = 0;
			state = Wait;
			break;
		}
		break;
		
		case PA1off:
		if (!(button)){
			stateNum = 2;
			state = Wait;
			break;
		}
		else{
			stateNum = 0;
			state = Wait;
			break;
		}
		break;
		
		default:
		state = Start;
		break;
	} // Transitions

	switch(state) { //State actions
		case PA0on:
		tmp = 0x5A;
		break;
		
		case PA0off:
		tmp = 0xA5;
		break;
		
		case PA1on:
		tmp = 0xAA;
		break;
		
		case PA1off:
		tmp = 0x55;
		break;
		
		default:
		break;
	} // State actions
}

int main(){
	DDRA = 0x00; PORTA = 0xFF;
	// Configure PORTA as input, initialize to 1s
	DDRC = 0xFF; PORTC = 0x00;
	// Configure PORTB as outputs, initialize to 0s
	state = Start; // Indicates initial call
	while(1) {
		button = ~PINA & 0x01;
		Tick();
	PORTC = tmp;}
	return 0;
}
