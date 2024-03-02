/*
 * Microcontrollers_Les1.c
 *
 * Created: 2-2-2024 10:54:43
 * Author : thijm
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define BIT(x)(1 << (x))

void setStateStart(){ // turn all the LEDS off
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
}

void setEndState(){ // turn all the LEDS on
	PORTA = 0xFF;
	PORTB = 0xFF;
	PORTC = 0xFF;
}


void setStateA(){ // turn portA LEDS on, rest off
	PORTA = 0xFF;
	PORTB = 0;
	PORTC = 0;
}

void setStateB(){ // turn portB LEDS on, rest off
	PORTA = 0;
	PORTB = 0xFF;
	PORTC = 0;
}

void setStateC(){ // turn portC LEDS on, rest off
	PORTA = 0;
	PORTB = 0;
	PORTC = 0xFF;
}

int main(void)
{
	DDRA = 0b11111111; // DDR is direction, A is the PORT --> OUTPUT
	DDRB = 0b11111111; // DDR is direction, B is the PORT --> OUTPUT
	DDRC = 0b11111111; // DDR is direction, C is the PORT --> OUTPUT
	
	PORTD = 0x01; // 
	
	int currentstate = 0;
	setStateStart();
	
    while (1) 
    {
		switch (currentstate){
			case 0:
				if (PIND & 0b01000000) // 6
				{
					setStateA();
					currentstate = 1;
					_delay_ms(500);
				}
				else if (PIND & 0b00100000){ // 5
					setStateB();
					currentstate = 2;
					_delay_ms(500);
				}
				break;
			case 1:
			    if (PIND & 0b10000000){ // 7
					setStateStart();
					currentstate = 0;
					_delay_ms(500);
				}
				else if (PIND & 0b00100000){ // 5
					setStateB();
					currentstate = 2;
					_delay_ms(500);
				}
				break;
			case 2:
				if (PIND & 0b10000000){ // 7
					setStateStart();
					currentstate = 0;
					_delay_ms(500);
				}
				else if (PIND & 0b01000000) // 6
				{
					setStateA();
					currentstate = 1;
					_delay_ms(500);
				}
				else if (PIND & 0b00100000){ // 5
					setStateC();
					currentstate = 3;
					_delay_ms(500);
				}
				break;
			case 3:
				if (PIND & 0b01000000 || PIND & 0b00100000){ // 5 and 6
					setEndState();
					currentstate = 4;
					_delay_ms(500);
				}
				else if (PIND & 0b10000000){ // 7
					setStateStart();
					currentstate = 0;
					_delay_ms(500);
				}
				break;
			case 4:
				if (PIND & 0b10000000){ // 7
					setStateStart();
					currentstate = 0;
					_delay_ms(500);
				}
				break;
		}
	}
	return 0;
}



