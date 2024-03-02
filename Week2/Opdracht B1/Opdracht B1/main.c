/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	ISR on PORTD demonstrattion  
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define BIT(x)(1 << (x))

int count = 0;

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT1_vect ) {
	if (count >= 7){
		count = 0;
	}
	else count++;
    PORTE = BIT(count);
	wait(150);
}

ISR( INT2_vect ) {
    if (count <= 0){
	    count = 7;
    }
    else count--;
    PORTE = BIT(count);	
	wait(150);
}

int main( void ) {
	// Init I/O
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input	
	DDRE = 0xFF;

	// Init Interrupt hardware
	EICRA |= 0x2C;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 6;			// Enable INT1 & INT2
	
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();				

	while (1) {
										
	}

	return 1;
}
