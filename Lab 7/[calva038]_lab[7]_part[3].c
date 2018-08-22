#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
enum States {Start, Sound1, Wait} state;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char button = 0x00;
double freq[10] = {880.0, 523.25113, 587.32954, 659.25511, 698.45646, 783.99087, 440.0, 493.8833, 0};
double dur[40] = {406.250, 203.125, 203.125, 406.250, 203.125, 203.125, 406.250, 203.125, 203.125, 406.250, 203.125, 203.125, 609.375, 203.125, 406.250, 406.250, 406.250, 406.250, 203.125, 203.125, 203.125, 203.125, 609.375, 203.125, 406.250, 203.125, 203.125, 609.375, 203.125, 406.250, 203.125, 203.125, 406.250, 203.125, 203.125, 406.250, 406.250, 406.250, 406.250, 406.250};
char song[40] = {3, 7, 1, 2, 1, 7, 6, 6, 1, 3, 2, 1, 7, 1, 2, 3, 1, 6, 6, 6, 7, 1, 2, 4, 0, 5, 4, 3, 1, 3, 2, 1, 7, 7, 1, 2, 3, 1, 6, 6};

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
		if (button){
			state = Sound1;
			break;
		}
		else{
			state = Wait;
		}
		break;
		
		case Sound1:
		state = Wait;
		break;
	} // Transitions

	switch(state) { //State actions
		case Wait:
		break;
		
		case Sound1:
		PWM_on();
		for (int i = 0; i <48; i++){
			TimerSet(dur[i]);
			set_PWM (freq[song[i]]);
			while (!TimerFlag);
			TimerFlag = 0;
		}
		PWM_off();
		break;
	} // State actions
}

int main(){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	PWM_off();
	TimerSet(203.125);
	TimerOn();
	state = Start; // Indicates initial call
	while(1){
		button = ~PINA & 0x01;
		Tick();
	}
	return 0;
}