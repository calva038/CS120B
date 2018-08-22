#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
enum States {Start, LED1, LED2, LED3, LED4, LED5, LED6, LED7, ButtonPress, ButtonRelease} state;

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
		state = LED1;
		break;
		
		case LED1:
		if (!(button)){
			state = LED2;
		}
		else if ((button)){
			state = ButtonPress;
			break;
		}
		break;
		
		case LED2:
		if (!(button)){
			state = LED3;
		}
		else if ((button)){
			state = ButtonPress;
			break;
		}
		break;
		
		case LED3:
		if (!(button)){
			state = LED4;
		}
		else if ((button)){
			state = ButtonPress;
			break;
		}
		break;
		
		case LED4:
		if (!(button)){
			state = LED5;
		}
		else if ((button)){
			state = ButtonPress;
			break;
		}
		break;
		
		case LED5:
		if (!(button)){
			state = LED6;
		}
		else if ((button)){
			state = ButtonPress;
			break;
		}
		break;
		
		case LED6:
		if (!(button)){
			state = LED7;
		}
		else if ((button)){
			state = ButtonPress;
			break;
		}
		break;
		
		case LED7:
		if (!(button)){
			state = LED1;
		}
		else if ((button)){
			state = ButtonPress;
			break;
		}
		break;
		
		case ButtonPress:
		if ((button)){
			state = ButtonPress;
			break;
		}
		else
			state = ButtonRelease;
		break;
		
		case ButtonRelease:
		if ((!(button))){
			state = ButtonRelease;
			break;
		}
		else
			state = Start;
		break;
		
	} // Transitions

	switch(state) { //State actions
		case LED1:
		PORTB = 0x01;
		break;
		
		case LED2:
		PORTB = 0x03;
		break;
		
		case LED3:
		PORTB = 0x02;
		break;
		
		case LED4:
		PORTB = 0x06;
		break;
		
		case LED5:
		PORTB = 0x04;
		break;
		
		case LED6:
		PORTB = 0x05;
		break;
		
		case LED7:
		PORTB = 0x07;
		break;
		
		case ButtonPress:
		break;
		
		case ButtonRelease:
		break;
		
	} // State actions
}

void main(){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	while(1){
		Tick();
		button = ~PINA & 0x01;
		while (!TimerFlag);
		TimerFlag = 0;
	}
}