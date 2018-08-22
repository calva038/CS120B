#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
enum States {Start, SoundOn, SoundOff, Wait} state;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char button = 0x00;

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
		state = Wait;
		break;
		
		case Wait:
		if (!(button)){
			state = Wait;
		}
		else if ((button)){
			state = SoundOn;
			break;
		}
		break;
		
		case SoundOn:
		if (!(button)){
			state = Wait;
		}
		else if ((button)){
			state = SoundOff;
			break;
		}
		break;
		
		case SoundOff:
		if (!(button)){
			state = Wait;
		}
		else if ((button)){
			state = SoundOn;
			break;
		}
		break;
	} // Transitions

	switch(state) { //State actions
		case Wait:
		PORTB = 0x00;
		break;
		
		case SoundOn:
		PORTB = 0x10;
		break;
		
		case SoundOff:
		PORTB = 0x00;
		
		break;
	} // State actions
}

int main(){
	DDRA = 0x00; PORTA = 0xFF;
	// LCD data lines
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(2);
	TimerOn();
	state = Start; // Indicates initial call
	while(1){
		Tick();
		button = ~PINA & 0x04;
		while (!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}