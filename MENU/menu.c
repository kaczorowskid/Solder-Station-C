/*
 * menu.c
 *
 *  Created on: 08.01.2020
 *      Author: Damian
 */


#include <avr/io.h>
#include <util/delay.h>
#include "menu.h"
//#include "../LCD/lcd44780.h"

//extern volatile uint8_t tim1;

const menu_t menu[] = {
		{"> Ustawienia PID", "Informacje      ", 0 },
		{"Ustawienia PID  ", "> Informacje    ", 0},
		{"> Wyjscie       ", "                ", 0}
};

const menu_t submenu[] ={
		{" KP  KI  KD  KT ", 0, test }, //" 08  22  10  02 "
		{"Jan Kowalski    ", "Warszawa 2020   ", 0},
};


void menu_change(uint8_t pos){

	uint8_t *first_line_pointner = (pos < 10) ? menu[pos - 1].first_line : submenu[pos - 12].first_line;
	uint8_t *second_line_pointner = (pos < 10) ? menu[pos - 1].second_line : submenu[pos - 12].second_line;


	lcd_locate(0,0);
	lcd_str(first_line_pointner);
	lcd_locate(1,0);
	lcd_str(second_line_pointner);

	if(pos > 10 && submenu[pos].callback) submenu[pos - 12].callback();
}

void start_display(uint16_t current_temp, uint16_t temp, uint8_t pwm){
	lcd_locate(0,0);
	lcd_big_int(current_temp);
	lcd_blink_int(temp, 0, 13, 1, 15);
}

void test(void){
//	lcd_cls();
//	lcd_blink_int(10, 1, 1, 1,  15);
	lcd_blink_int(10, 1, 1, 1, 15);
	lcd_blink_int(02, 1, 5, 0, 13);

//	_delay_ms(1);
}
