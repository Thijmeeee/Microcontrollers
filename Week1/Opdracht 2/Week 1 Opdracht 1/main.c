#include <avr/io.h>
#define F_CPU 9000000UL
#include <util/delay.h>

#define BIT(x) (1 << (x))

int main(void)
{
	DDRD = 0xFF; //puts PORTD as output
	
	while (1)
	{
		PORTD = BIT(6);		//turns on BIT 6  on PORTD
		_delay_ms(500);
		PORTD = BIT(7);		//turns on BIT 7  on PORTD
		_delay_ms(500);
	}
	return 0;
}

