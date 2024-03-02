#include <avr//io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define BIT(x)(1 << (x))

int main (void)
{
	DDRD = 0xFF		//puts PORTD as output

	
	while (1)
	{
		//lets LED light walk over PORTD
		for (int x = 0; x < 8; x++)
		{
			PORTD = BIT(x);		//turns on light x on port D
			_delay_ms(50);
		}
	}
	return 0;
}


