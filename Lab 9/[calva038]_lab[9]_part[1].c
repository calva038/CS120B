#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
enum States1 {Start1, LED11, LED21, LED31} state1;
enum States2 {Start2, LED12, LED22, LED32} state2;
enum States3 {Start3, Combine} state3;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
char tmp1, tmp2, combo = 0;

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

void Tick(){

	switch(state1){ // Transitions
		case Start1:
		state1 = LED11;
		break;
		
		case LED11:
		state1 = LED21;
		break;
		
		case LED21:
		state1 = LED31;
		break;
		
		case LED31:
		state1 = LED11;
		break;
	} // Transitions
	
	switch(state2){ // Transitions
		case Start2:
		state2 = LED32;
		break;
		
		case LED12:
		state2 = LED32;
		break;
		
		case LED32:
		state2 = LED12;
		break;
	} // Transitions
	
	switch(state3){ // Transitions
		case Start3:
		state3 = Combine;
		break;
		
		case Combine:
		state3 = Combine;
		break;
	} // Transitions

	switch(state1) { //State actions
		case LED11:
		tmp1 = 0x01;
		break;
		
		case LED21:
		tmp1 = 0x02;
		break;
		
		case LED31:
		tmp1 = 0x04;
		break;
	} // State actions
	
	switch(state2) { //State actions
		case LED12:
		tmp2 = 0x00;
		break;
		
		case LED32:
		tmp2 = 0x08;
		break;
	} // State actions
	
	switch(state3) { //State actions
		
		case Combine:
		combo = (tmp1 | tmp2);
		PORTB = combo;
		break;
	} // State actions
}

int main(){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	state1 = Start1; // Indicates initial call
	state2 = Start2; // Indicates initial call
	state3 = Start3; // Indicates initial call
	while(1){
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}