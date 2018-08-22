#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
enum States {Start, LED1, LED2, LED3} state;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

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

	switch(state){ // Transitions
		case Start:
		state = LED1;
		break;
		
		case LED1:
		state = LED2;
		break;
		
		case LED2:
		state = LED3;
		break;
		
		case LED3:
		state = LED1;
		break;
		
		} // Transitions

	switch(state) { //State actions
		case LED1:
		PORTB = 0x01;
		break;
		
		case LED2:
		PORTB = 0x02;
		break;
		
		case LED3:
		PORTB = 0x04;
		break;
	} // State actions
}

void main(){
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	while(1){
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}