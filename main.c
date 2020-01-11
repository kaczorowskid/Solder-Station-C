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
extern uint8_t menu_pos = 0;



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

		if(!menu_pos || menu_pos == 12 || menu_pos == 13) encoder_reset();
		else menu_pos += enc_get();


		menu_change(menu_pos);

		if(!menu_pos) start_display(321, 432, 0);

		if(!menu_pos) read_kbc(0, &menu_pos, 0);
		else if(menu_pos != 12) read_kbc(&menu_pos, 0, 1);
		else if(menu_pos == 12) read_kbc(0,0,0);

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

