#include <avr//io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define BIT(x)(1 << (x))

int main (void)
{
	DDRD = 0xFF;		//puts PORTD as output
	
	//sets an int array
	int LED_ARRAY[] = {0b11000011, 0b01100110, 0b00111100, 0b00011000};

	
	while (1)
	{
		//walks through array and turns on LEDS on PORTD
		for (int i = 0; i < sizeof(LED_ARRAY); i++)
		{
			PORTD = LED_ARRAY[i];		//turns on LEDS on portD with value off LED_ARRAY[i]
			_delay_ms(100);
		}
	}
	return 0;
}




