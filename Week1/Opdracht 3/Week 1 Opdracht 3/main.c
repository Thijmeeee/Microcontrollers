#include <avr//io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define BIT(x)(1 << (x))

int main (void)
{
	DDRD = 0xFF;		//puts PORTD as output
	PORTC = 0x01;	//puts PORTC.0 as input
	
	while (1)
	{
		//when button C0 is pressed LED D7 starts flashing
		if (PINC & 0x01)
		{
			PORTD = BIT(7);			//turns LED D7 on
			_delay_ms(250);
			PORTD = 0b00000000;		//turns all LEDS on D off
			_delay_ms(250);
		}
		else
		{
			PORTD = 0b00000000;		//turns all LEDS on D off
		}
	}
	return 0;
}
