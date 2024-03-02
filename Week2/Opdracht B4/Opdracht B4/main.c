#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

#define BIT(x) (1 << (x))

const unsigned int Numbers[8] = {
	0x08,
	0x04,
	0x40,
	0x20,
	0x01,
	0x02,
	0x40,
	0x10,
};


void wait(int ms) {
	for (int i = 0; i < ms; i++) {
		_delay_ms(1); // library function (max 30 ms at 8MHz)
	}
}

void display(int digit) {
		PORTB = Numbers[digit];
		wait(150);
}

int main(void) {
	DDRB = 0xFF;

	while (1) {
		for(int i = 0; i < 8; i++){
			display(i);
		}
	}

	return 1;
}
