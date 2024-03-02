/*
 * Opdracht B2.c
 *
 * Created: 23-2-2024 11:37:04
 * Author : thijm
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define BIT(x) (1 << (x))

	
ISR(TIMER2_COMP_vect){
	PORTD ^= BIT(7);
	if (OCR2 == 15){
		OCR2 = 25;
	}
	else {
		OCR2 = 15;
	}
}


int main(void)
{
    TCCR2 = 0b00011100; // set CTC mode
	TCNT2 = 0x00;
	DDRD = BIT(7);
	TIMSK |= BIT(7);
	OCR2 = 15;
	sei();

    while (1) 
    {
		
    }
}

