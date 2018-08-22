/*
 * [calva038]_lab[8]_part[1].c
 *
 * Created: 8/20/2018 9:25:38 AM
 * Author : calva
 */ 

#include <avr/io.h>

unsigned short ADCValue = 0x0000;
unsigned char ADCcharB = 0x00;
unsigned char ADCcharD = 0x00;

void ADC_init() 
{ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//the previous conversion completes.
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	ADC_init();
    /* Replace with your application code */
    while (1) 
    {
		ADCValue = ADC;
		if (ADCValue > 0x27)
			PORTB = 0x01;
		else
			PORTB = 0x00;
    }
}

