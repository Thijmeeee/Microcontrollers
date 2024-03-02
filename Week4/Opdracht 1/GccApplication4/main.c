
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>



void setupADC(){
	//DDRF &= ~(1<<PF0);
	DDRF = 0x00;			//PORTF inputs for reading ADC
	DDRA = 0xFF;			//PORTA  outputs for displaying ADC value
	DDRB = 0xFF;			//PORTB  outputs for displaying ADC value
	
	//puts ADMUX settings, sets it for PORT0 and Left Adjust the result
	ADMUX = 0b01100000;
	
	//puts ADCSRA on free running with a 64 Division factor
	ADCSRA = 0b11100110;
}


int main(void)
{
	
	setupADC();
	
	while (1)
	{
		
		PORTA = ADCL;		//puts lower bits on PORTA
		PORTB = ADCH;		//puts higher bits on PORTB
		
		_delay_ms(100);
	}
}

