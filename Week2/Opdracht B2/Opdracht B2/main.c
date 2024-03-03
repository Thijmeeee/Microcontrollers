/*
 * Opdracht B2.c
 *
 * Created: 3-3-2024 11:48:03
 * Author : thijm
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x) (1 << (x))

int count = 0;

void wait(int ms){
	for (int i =0; i<ms; i++){
		_delay_ms(1); // library function (max 30ms at 8 MHz)
	}
}

ISR( INT1_vect){
	if (count >= 7){
		count = 0;
	}
	else count++;
	PORTE = BIT(count);
	wait(150);
}

ISR (INT2_vect){
	if (count <= 0){
		count = 7;
	}
	else count--;
	PORTE = BIT(count);
	wait(150);
}

int main (void){
	// INIT I/O
	DDRD = 0xF0; // PORTD(7:4) OUTPUT
	DDRE = 0xFF; // PORTD(3:0) INPUT

	// INIT Interrupt Hardware
	EICRA |= 0x2C; // INT1 falling edge, INT0 rising edge
	EIMSK |= 6; // Enable INT1 & INT2

	// enable global interrupt system
	sei();

	while (1){

	}
}
