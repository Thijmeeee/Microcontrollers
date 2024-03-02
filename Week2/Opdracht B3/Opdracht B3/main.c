#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

#define BIT(x) (1 << (x))

const unsigned int Numbers[16] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F, // 9
	0x77, // A
	0x7C, // B
	0x39, // C
	0x5E, // D
	0x79, // E
	0x71  // F
};

void wait(int ms) {
	for (int i = 0; i < ms; i++) {
		_delay_ms(1); // library function (max 30 ms at 8MHz)
	}
}

void display(int digit) {
	if (0 <= digit && digit <= 15) {
		PORTB = Numbers[digit];
		wait(150);
		} else {
		PORTB = 0x79;
		wait(150);
	}
}

int main(void) {
	DDRB = 0xFF; // Set PORTD as output
	int count = 0;
	display(count);

	while (1) {
		if (PINA & BIT(0)){
			count++;
		}
		if (PINA & BIT(1)){
			count--;
		}
		if ((PINA & BIT(0) && PINA & BIT(1))){
			count = 0;
		}
		
		if (count > 15){
			display(16);
		}
		else if (count < 0){
			display(16);
		}
		else display(count);
		
	}

	return 1;
}
