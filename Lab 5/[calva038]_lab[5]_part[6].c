#include <avr/io.h>
#include "./lcd_io.h"
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
enum States {Start, LED1, LED2, LED3, ButtonPress, ButtonRelease, Victory} state;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
char tmp, output = 0;
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
		if (output >= 9){
			state = Victory;
			break;
		}
		if ((!(button))){
			state = ButtonRelease;
			break;
		}
		else
			state = Start;
		break;
		
		case Victory:
		break;
		
	} // Transitions

	switch(state) { //State actions
		case LED1:
		tmp = 0;
		PORTB = 0x01;
		break;
		
		case LED2:
		tmp = 1;
		PORTB = 0x02;
		break;
		
		case LED3:
		tmp = 0;
		PORTB = 0x04;
		
		break;
		
		case ButtonPress:
		if (tmp == 1){
			tmp = 0;
			output++;
		}
		break;
		
		case ButtonRelease:
		LCD_ClearScreen();
		TimerSet(100);
		while (!TimerFlag);
		TimerFlag = 0;
		TimerSet(300);
		LCD_WriteData(output + '0');
		break;
		
		case Victory:
		LCD_ClearScreen();
		TimerSet(100);
		while (!TimerFlag);
		TimerFlag = 0;
		LCD_DisplayString(1,"GAME ARE DONE");
		TimerSet(1000);
		while (!TimerFlag);
		TimerFlag = 0;
		LCD_DisplayString(1,"YOU IS WINNER");
		while (!TimerFlag);
		TimerFlag = 0;
		TimerSet(10000);
		break;
		
	} // State actions
}

int main(){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRC = 0xFF;
	PORTC = 0x00;
	// LCD data lines
	DDRD = 0xFF;
	PORTD = 0x00;
	TimerSet(300);
	TimerOn();
	LCD_init();
	state = Start; // Indicates initial call
	LCD_WriteData(0 + '0');
	while(1){
		Tick();
		button = ~PINA & 0x01;
		while (!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}