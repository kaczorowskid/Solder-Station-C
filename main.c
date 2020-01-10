/*
 * main.c
 *
 *  Created on: 04.01.2020
 *      Author: Damian
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "LCD/lcd44780.h"
#include "ENC/enc.h"
#include "KEY/key.h"
#include "MENU/menu.h"
#include "ADC/adc.h"


uint16_t zm = 0;

volatile uint8_t timer, tim2, tim3;

uint8_t menu_pos = 0;



int main(void){
	lcd_init();

	encoder_port();
	encoder_reset();


	TCCR1B |= (1<<WGM12);
	TCCR1B |= (1<<CS12)|(1<<CS10);
	TIMSK |= (1<<OCIE1A);
	OCR1A = 200;

	adc_init();
	init_kbc();

	sei();

	while(1){
		encoder();

		if(!menu_pos) encoder_reset();
		else menu_pos += enc_get();


		menu_change(menu_pos);

		if(!menu_pos) start_display(321, 432, 0);

		read_kbc(&menu_pos, &menu_pos);

		lcd_locate(1,14);
		lcd_int(menu_pos);

	}
}



ISR(TIMER1_COMPA_vect){
	uint8_t x;
	x = timer;
	if(x) timer = --x;
	x = tim2;
	if(x) tim2 = --x;
	x = tim3;
	if(x) tim3 = --x;
}

