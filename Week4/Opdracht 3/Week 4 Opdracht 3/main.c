
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>



void setupADC(){
	//DDRF &= ~(1<<PF0);
	DDRF = 0x00;			//PORTF inputs for reading ADC
	DDRA = 0xFF;			//PORTA  outputs for displaying ADC value
	DDRB = 0xFF;			//PORTB  outputs for displaying ADC value
	
	//puts ADMUX settings, sets it for PORT3 and Left Adjust the result
	ADMUX = 0b01100011;
	
	//puts ADCSRA on single conversion with a 64 Division factor
	ADCSRA = 0b10000110;
}


int main(void)
{
	
	setupADC();
	
	while (1)
	{
		//Updates only when we press PD0;
		if(PIND & (1<<0)){
			// start ADC Conversion
			ADCSRA |= (1<<ADSC);
		}
		
		//Wait for converion to complete
		while (ADCSRA & (1<<ADSC));
		PORTB = ADCH;		//puts higher bits on PORTB
		
		_delay_ms(100);
	}
}



