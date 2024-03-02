#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include "main.h"

#define LCD_E 3
#define LCD_RS 2

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void set_cursor(int position);

void wait(int ms) {
	for (int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

void lcd_command(unsigned char data) {
	PORTC = data & 0xF0; // hoge nibble
	lcd_strobe_lcd_e();        // wait 1 ms

	PORTC = 0x04;          // stop (EN = 0)
	PORTC = (data & 0x0F) << 4; // lage nibble

	lcd_strobe_lcd_e(); // wait 1 ms
	PORTC = 0x00; // stop (EN=0 RS=0)
}

void lcd_writeChar(unsigned char data) {
	PORTC = data & 0xF0; // hoge nibble
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	PORTC = (data & 0x0F) << 4; // lage nibble
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

}

void lcd_strobe_lcd_e(void) {
	PORTC |= (1<<LCD_E);    // E high
	_delay_ms(1);            // nodig
	PORTC &= ~(1<<LCD_E);      // E low
	_delay_ms(1);            // nodig?
}

void init_4bits_mode(void) {
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;    // function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
	
	lcd_command(0x01); // clear the display
}

void display_text(char *str) {
	for (;*str; str++) {
		lcd_writeChar(*str);
	}
}

void set_cursor(int position){
	unsigned char p = 0x80 + position;
	lcd_command(p);
}

int main(void) {
	init_4bits_mode();
	display_text("Thijme");
	
	wait(1000);
	set_cursor(40);
	display_text("Ruben");
	while (1) {
		
	}
}
