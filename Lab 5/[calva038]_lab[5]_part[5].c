#include <avr/io.h>
#include "./lcd_io.h"
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
enum States {Start, Wait, PA0on, PA1on, Reset} state;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
char tmp = 0;
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
		if (button1 && button2){
			state = Reset;
		}
		else if (button1 && !(button2)) {
			state = PA0on;
		}
		else if (!(button1) && !(button2)) {
			state = Wait;
		}
		else if (!(button1) && (button2)) {
			state = PA1on;
		}
		break;
		
		case PA1on:
		if (button1 && button2){
			state = Reset;
		}
		else if (!(button1) && button2) {
			state = PA1on;
		}
		else if (!(button1) && !(button2)) {
			state = Wait;
		}
		else if (button1 && !(button2)) {
			state = PA0on;
		}
		break;
		
		case Reset:
		state = Wait;
		break;
		
		default:
		state = Start;
		break;
	} // Transitions

	switch(state) { //State actions
		case PA0on:
		if (tmp < 9){
			tmp++;
			LCD_ClearScreen();
			TimerSet(100);
			while (!TimerFlag);
			TimerFlag = 0;
			TimerSet(1000);
			LCD_WriteData(tmp + '0');
		}
		break;
		
		case PA1on:
		if (tmp > 0){
			tmp--;
			LCD_ClearScreen();
			TimerSet(100);
			while (!TimerFlag);
			TimerFlag = 0;
			TimerSet(1000);
			LCD_WriteData(tmp + '0');
		}
		break;
		
		case Reset:
		tmp = 0x00;
		LCD_ClearScreen();
		TimerSet(100);
		while (!TimerFlag);
		TimerFlag = 0;
		TimerSet(1000);
		LCD_WriteData(tmp + '0');
		break;
		
		default:
		break;
	} // State actions
}

int main(){
	DDRA = 0x00; PORTA = 0xFF;
	// Configure PORTA as input, initialize to 1s
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	// Configure PORTB as outputs, initialize to 0s
	TimerSet(1000);
	TimerOn();
	LCD_init();
	state = Start; // Indicates initial call
	LCD_WriteData(0 + '0');
	while(1) {
		button1 = ~PINA & 0x01;
		button2 = ~PINA & 0x02;
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}