#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
enum States1 {Start1, Wait1, PA0on, PA0onLong} state1;
enum States2 {Start2, Wait2, PA1on, PA1onLong} state2;
enum States3 {Start3, Combo, Reset} state3;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
char tmp, timer1, timer2, check1, check2 = 0;
unsigned char button1 = 0x00;
unsigned char button2 = 0x00;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void Tick1(){

	switch(state1){ // Transitions
		case Start1:
		state1 = Wait1;
		break;
		
		case Wait1:
		if (!(button1)){
			state1 = Wait1;
			break;
		}
		else if (button1){
			state1 = PA0on;
			break;
		}
		break;
		
		case PA0on:
		if (button1){
			if (timer1 == 3){
				state1 = PA0onLong;
				break;
			}
			else{
				state1 = PA0on;
				break;
			}
		}
		else if (!(button1)) {
			state1 = Wait1;
			break;
		}
		break;
		
		case PA0onLong:
		if (button1){
			state1 = PA0onLong;
			break;
		}
		else if (!(button1)) {
			state1 = Wait1;
			break;
		}
		break;
		
		default:
		state1 = Start1;
		break;
	} // Transitions
	
	switch(state1) { //State actions
		case Wait1:
		timer1 = 0;
		break;
		
		case PA0on:
		if (check1 == 9){
		if (tmp < 9){
			tmp++;
			timer1++;
			check1 = 0;
		}
		check1 = 0;
		}
		else{
			check1++;
		}
		break;
		
		case PA0onLong:
		if (check1 == 3){
		if (tmp < 9){
			tmp++;
		}
		check1 = 0;
		}
		else{
			check1++;
		}
		break;
		
		default:
		break;
	} // State actions
}

void Tick2(){
switch(state2){ // Transitions
	case Start2:
	state2 = Wait2;
	break;
	
	case Wait2:
	if (!(button2)){
		state2 = Wait2;
		break;
	}
	else if (button2){
		state2 = PA1on;
		break;
	}
	break;
	
	case PA1on:
	if (button2){
		if (timer2 == 3){
			state2 = PA1onLong;
			break;
		}
		else{
		state2 = PA1on;
		break;
		}
	}
	else if (!(button2)) {
		state2 = Wait2;
		break;
	}
	break;
	
	case PA1onLong:
	if (button2){
		state2 = PA1onLong;
		break;
	}
	else if (!(button2)) {
		state2 = Wait2;
		break;
	}
	break;
	
	default:
	state2 = Start2;
	break;
} // Transitions

switch(state2) { //State actions
	case Wait2:
	timer2 = 0;
	break;
	
	case PA1on:
	if (check2 == 9){
	if (tmp > 0){
		tmp--;
		timer2++;
	}
	check2 = 0;
	}
	else{
		check2++;
	}
	break;
	
	case PA1onLong:
	if (check2 == 3){
	if (tmp > 0){
		tmp--;
	}
	check2 = 0;
	}
	else{
		check2++;
	}
	break;
	
	default:
	break;
} // State actions
}

void Tick3(){
switch(state3){ // Transitions
	case Start3:
	state3 = Combo;
	break;
	
	case Combo:
	if (button1 && button2){
		state3 = Reset;
		break;
	}
	else
	state3 = Combo;
	break;
	
	case Reset:
	state3 = Combo;
	break;
}

switch(state3) { //State actions
	case Combo:
	PORTB = tmp;
	break;
	
	case Reset:
	tmp = 0;
	PORTB = tmp;
	break;
	
	default:
	break;
} // State actions
}

int main(){
	DDRA = 0x00; PORTA = 0xFF;
	// Configure PORTA as input, initialize to 1s
	DDRB = 0xFF; PORTB = 0x00;
	// Configure PORTB as outputs, initialize to 0s
	TimerSet(100);
	TimerOn();
	state1 = Start1; // Indicates initial call
	state2 = Start2; // Indicates initial call
	state3 = Start3; // Indicates initial call
	check1 = 9;
	check2 = 9;
	while(1) {
		button1 = ~PINA & 0x01;
		button2 = ~PINA & 0x02;
		Tick1();
		Tick2();
		Tick3();
		while (!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}