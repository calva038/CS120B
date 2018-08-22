#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
enum States {Start, Sound1, Sound2, Sound3, Wait} state;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char button1, button2, button3 = 0x00;
unsigned char tmp = 2;

void set_PWM (double frequency) {
	static double current_frequency;
	// Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) {
			TCCR3B &= 0x08; 
			}
		//stops timer/counter
		else {
			TCCR3B |= 0x03; 
		}
		//resumes/continues timer/counter
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) {
			OCR3A = 0xFFFF; 
		}
		// prevents OCR3A from underflowing, using prescaler 64
		// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) {
			OCR3A = 0x0000;
		}
		// set OCR3A based on desired frequency
		else
		{
			OCR3A = (short)(8000000 / (128 * frequency))-1; 
		}
		TCNT3 = 0;
		//resets counter 
		current_frequency = frequency;
		// Updates the current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	//WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

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
		if (button1 && !(button2) && !(button3)){
			PWM_on();
			state = Sound1;
			break;
		}
		else if (button2 && !(button1) && !(button3)){
			PWM_on();
			state = Sound2;
			break;
		}
		else if (button3 && !(button2) && !(button1)){
			PWM_on();
			state = Sound3;
			break;
		}
		else{
			state = Wait;
		}
		break;
		
		case Sound1:
		if (button1 && !(button2) && !(button3)){
			state = Sound1;
			break;
		}
		else
		state = Wait;
		break;
		
		case Sound2:
		if (button2 && !(button1) && !(button3)){
			state = Sound2;
			break;
		}
		else
		state = Wait;
		break;
		
		case Sound3:
		if (button3 && !(button2) && !(button1)){
			state = Sound3;
			break;
		}
		else
		state = Wait;
		break;
	} // Transitions

	switch(state) { //State actions
		case Wait:
		PWM_off();
		PORTC = 0x00;
		break;
		
		case Sound1:
		PORTC = 0x01;
		set_PWM (261.63);
		break;
		
		case Sound2:
		PORTC = 0x02;
		set_PWM (293.66);
		break;
		
		case Sound3:
		PORTC = 0x04;
		set_PWM (329.63);
		break;
	} // State actions
}

int main(){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRC = 0xFF;
	PORTC = 0x00;
	PWM_off();
	state = Start; // Indicates initial call
	while(1){
		Tick();
		button1 = ~PINA & 0x01;
		button2 = ~PINA & 0x02;
		button3 = ~PINA & 0x04;
	}
	return 0;
}