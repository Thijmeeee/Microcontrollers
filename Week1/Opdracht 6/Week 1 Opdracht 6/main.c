#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define BIT(x)(1<<(x))

//delays for "ms" milliseconds
void wait(int ms) {
	for (int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}


// switches frequence of light flashes when button C0 is pressed
int main (void)
{
	DDRD = 0xFF;	//Sets PORTD to output
	PORTC = 0x01;	//sets PORTC.0 to input
	int HZ_SPEED = 250;
	
	while (1)
	{
		// when button C0 is pressed HZ_SPEED switches
		if (PINC & 0x01)
		{
			if (HZ_SPEED == 150)
			{	
				HZ_SPEED = 900;
			}
			else if (HZ_SPEED == 900)
			{
				HZ_SPEED = 150;
			}
		}
		
		// turns LED D7 on and off and then wait HZ_speed
		PORTD = BIT(7);
		_delay_ms(100);
		PORTD = 0b00000000;
		
		wait(HZ_SPEED);
	}
}

