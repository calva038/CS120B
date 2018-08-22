#include <avr/io.h>

enum States {Start, Wait, PA0on, PA0off, PA1on, PA1off, Reset, Resetoff} state;
char tmp = 0;
unsigned char button1 = 0x00;
unsigned char button2 = 0x00;

void Tick(){

	switch(state){ // Transitions
		case Start:
		state = Wait;
		break;
		
		case Wait:
		if (!(button1) && !(button2)){
			state = Wait;
		}
		else if ((button1) && !(button2)){
			state = PA0on;
		}
		else if (!(button1) && (button2)){
			state = PA1on;
		}
		else if ((button1) && (button2)){
			state = Reset;
		}
		break;
		
		case PA0on:
		if (button2){
			state = Reset;
			}
		else
			state = PA0off;
		break;
		
		case PA0off:
		if (!(button1)){
			state = Wait;
		}
		else
		state = PA0off;
		break;
		
		case PA1on:
		if (button1){
			state = Reset;
		}
		else
		state = PA1off;
		break;
		
		case PA1off:
		if (!(button2)){
			state = Wait;
		}
		else
		state = PA1off;
		break;
		
		case Reset:
		state = Wait;
		break;
		
		case Resetoff:
		if (!(button1) && !(button2)){
			state = Wait;
		}
		else
			state = Resetoff;
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
		break;
		
		case PA1on:
		if (tmp > 0){
		tmp--;
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
	DDRA = 0x00; PORTA = 0xFF;
	// Configure PORTA as input, initialize to 1s
	DDRC = 0xFF; PORTC = 0x00;
	// Configure PORTB as outputs, initialize to 0s
	state = Start; // Indicates initial call
	while(1) { 
		button1 = ~PINA & 0x01;
		button2 = ~PINA & 0x02;
		Tick();
		PORTC = tmp;}
	return 0;
}
